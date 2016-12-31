// サンプリング間隔。4 回ごとに平均を求めて1サンプルとするため、
// データのサンプリング周波数は50Hzになる
const unsigned long samplingInterval = 5;

// 加速度センサの各軸に接続したアナログピンの番号
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

// タクトスイッチに接続したデジタルピンの番号
const int buttonPin = 2;

// データ長
const byte sampleDataLength = 25;

// キャプチャしたデータ
char sampleData[sampleDataLength][3];

// キャプチャしたデータのカウンタ
int sampleCount = 0;

// キャプチャ中か否か
boolean isCapturing = false;

// 前回ボタンが押されていたか否か
boolean wasButtonPressed = false;

// キャプチャを開始
void beginCapture() {
  // カウンタをリセットしてキャプチャ中にフラグをセット
  sampleCount = 0;
  isCapturing = true;
}

// キャプチャを終了
void endCapture() {
  // キャプチャ中でなければ以下の処理を行わずにリターン
  if (!isCapturing) {
    return;
  }

  // キャプチャ中を示すフラグをリセット
  isCapturing = false;

  // キャプチャしたデータをタブ区切りでシリアルにプリント
  Serial.print("data\n");
  for (int i = 0; i < sampleDataLength; i++) {
    Serial.print(sampleData[i][0], DEC);
    Serial.print("\t");
    Serial.print(sampleData[i][1], DEC);
    Serial.print("\t");
    Serial.print(sampleData[i][2], DEC);
    Serial.print("\n");
  }
  Serial.print("\r\n");
}

// サンプルを処理
void processSample(int x, int y, int z) {
  // 平滑化処理を行うサンプル数
  const int samplesToAverage = 4;

  // 平滑化処理を行うためのループカウンタ
  static int count = 0;

  // 各軸の値の合計
  static int totalX, totalY, totalZ = 0;

  // 各軸の値の合計に新しい値を加算する
  totalX += x;
  totalY += y;
  totalZ += z;

  // 平滑化処理を行うためのループカウンタをインクリメント
  count++;

  // 平滑化処理を行うサンプル数に達したら
  if (count == samplesToAverage) {
    // 各軸の値を平滑化処理を行うサンプル数で割ったものを量子化する
    sampleData[sampleCount][0]
      = quantizeAccelData(totalX / samplesToAverage);
    sampleData[sampleCount][1]
      = quantizeAccelData(totalY / samplesToAverage);
    sampleData[sampleCount][2]
      = quantizeAccelData(totalZ / samplesToAverage);
    // キャプチャしたサンプル数をインクリメント
    sampleCount++;
    // 各軸の合計の値と平滑化処理のためのカウンタをリセット
    totalX = totalY = totalZ = 0;
    count = 0;
  }

  // キャプチャしたサンプル数が予定の数に達したらキャプチャを終了する
  if (sampleCount > (sampleDataLength - 1)) {
    endCapture();
  }
}

// 加速度センサの値を非線形に量子化する
byte quantizeAccelData(int accData) {
  // 重力加速度に対応した加速度センサの値を表す定数
  const int plus2G = 919;
  const int plus1G = 715;
  const int zeroG = 511;
  const int minus1G = 307;
  const int minus2G = 103;

  // 量子化した値
  byte quantized = 0;

  // 加速度センサの値に従って非線形に量子化する
  if (plus2G < accData) {
    // 2Gより大きければ16
    quantized = 16;
  }
  else if (plus1G < accData && accData <= plus2G) {
    // 1Gより大きく2G以下であれば11～15
    quantized = map(accData, plus1G + 1, plus2G, 11, 15);
  }
  else if (zeroG < accData && accData <= plus1G) {
    // 0Gより大きく1G以下であれば1～10
    quantized = map(accData, zeroG + 1, plus1G, 1, 10);
  }
  else if (minus1G <= accData && accData < zeroG) {
    // -1G以上で0Gより小さければ-10～ -1
    quantized = map(accData, minus1G, zeroG - 1, -10, -1);
  }
  else if (minus2G <= accData && accData < minus1G) {
    // -2G以上で-1Gより小さければ-15～ -11
    quantized = map(accData, minus2G + 1, minus1G, -15, -11);
  }
  else if (accData < minus2G) {
    // -2Gより小さければ-16
    quantized = -16;
  }

  // 量子化した値を返す
  return quantized;
}

// アクションがあるまで待つ
void waitForAction() {
  // 初期状態の各軸の値
  char initX = quantizeAccelData(analogRead(xPin));
  char initY = quantizeAccelData(analogRead(yPin));
  char initZ = quantizeAccelData(analogRead(zPin));

  // アクションがあるまで待機するカウント
  int count = 200;

  // アクションがあるか約200ms経過するまでの間、以下を実行
  while (--count > 0) {
    // 各軸の値を読み取る
    char x = quantizeAccelData(analogRead(xPin));
    char y = quantizeAccelData(analogRead(yPin));
    char z = quantizeAccelData(analogRead(zPin));

    // 初期値からの距離を求める
    unsigned int distance = 0;
    distance += abs(x - initX);
    distance += abs(y - initY);
    distance += abs(z - initZ);

    // 一定値以上変化したらリターン
    if (distance > 5) {
      return;
    }

    // 次のチェックまで1ms待つ
    delay(1);
  }
}

void setup() {
  // キャプチャしたデータをプリントするためのシリアルをスタート
  Serial.begin(9600);
}

void loop() {
  // 開始時刻を読み取る
  unsigned long start = millis();

  // ボタンが押されているかどうかを読み取る
  boolean isButtonPressed = (digitalRead(buttonPin) == HIGH);

  // 前回押されていなくて今回押されていたら
  if (!wasButtonPressed && isButtonPressed) {
    // アクションがあるまで待ってキャプチャを開始
    waitForAction();
    beginCapture();
  }

  // キャプチャ中であれば
  if (isCapturing) {
    // 加速度センサの各軸の値を読み取ってサンプルを処理する
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    int z = analogRead(zPin);
    processSample(x, y, z);
  }

  // 前回のキャプチャボタンの状態を更新
  wasButtonPressed = isButtonPressed;

  // 現在までの経過時間を読み取る
  unsigned long elapsedTime = millis() - start;

  // サンプリング間隔に達していなければ残り時間だけ待つ
  if (elapsedTime < samplingInterval) {
    delay(samplingInterval - elapsedTime);
  }
}

