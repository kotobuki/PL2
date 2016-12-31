#include "TemplateData.h"

// サンプリング間隔
const unsigned long samplingInterval = 5;

// 加速度センサの各軸に接続したアナログピンの番号
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

// タクトスイッチに接続したデジタルピンの番号
const int buttonPin = 2;

// データ長
const int sampleDataLength = 25;

// ジェスチャが見つからなかったことを示す定数
const int notFound = -1;

// キャプチャしたデータを収める配列
char sampleData[sampleDataLength][numAxises];

// キャプチャしたサンプル数のカウント
int sampleCount = 0;

// 前回ボタンが押されていたか否かを示すフラグ
boolean wasButtonPressed = false;

// キャプチャ中であるか否かを示すフラグ
boolean isCapturing = false;

// キャプチャを開始する
void beginCapture() {
  sampleCount = 0;
  isCapturing = true;
}

// キャプチャを終了する
void endCapture() {
  if (!isCapturing) {
    return;
  }
  isCapturing = false;
}

// サンプルを処理する
// 前半部分の処理はGestureRecorderと同じ
void processSample(int x, int y, int z) {
  const int samplesToAverage = 4;
  static int count = 0;
  static int totalX, totalY, totalZ = 0;
  totalX += x;
  totalY += y;
  totalZ += z;
  count++;
  if (count == samplesToAverage) {
    sampleData[sampleCount][0] 
    = quantizeAccelData(totalX / samplesToAverage);
    sampleData[sampleCount][1] 
    = quantizeAccelData(totalY / samplesToAverage);
    sampleData[sampleCount][2] 
    = quantizeAccelData(totalZ / samplesToAverage);
    sampleCount++;
    totalX = totalY = totalZ = 0;
    count = 0;
  }

  // キャプチャしたサンプル数が一定の数に達したら
  if (sampleCount > (sampleDataLength - 1)) {
    // キャプチャを終了し
    endCapture();

    // ジェスチャ認識を行った結果をシリアルにプリントする
    int gesture = detectGesture();
    Serial.print("Gesture: ");
    Serial.print(gesture);
    Serial.println();
  }
}

// ジェスチャ認識を行う
int detectGesture() {
  // 認識できたジェスチャの初期値をセット
  int gesture = notFound;

  // 最小の距離として1000をセット
  // これよりも短い距離のデータが見つからなければnotFoundのままになる
  unsigned int minimumDistance = 1000;

  // テンプレートデータの数だけ順次繰り返す
  for (int i = 0; i < numTemplates; i++) {
    // DTWを用いてキャプチャしたデータとテンプレートの距離を求める
    unsigned int distance = getDTWDistance(i);

    // 現在までに求めた最短の距離よりも短ければ
    if (distance < minimumDistance) {
      // 認識できたジェスチャとして現在のインデックスをセット
      gesture = i;
      minimumDistance = distance;
    }
  }

  // 認識できたジェスチャ（またはnotFound）を返す
  return gesture;
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

// DTWを用いてテンプレートとデータの間の距離を求める
unsigned int getDTWDistance(int templateIndex) {
  // DTWの計算に用いる配列（今回の場合は1352バイト）
  static unsigned int 
    DTW[sampleDataLength + 1][templateDataLength + 1];

  // 汎用のループカウンタ
  int i, j = 0;

  // サンプルとテンプレート用のループカウンタ
  int is, it = 0;

  // 距離を計算するのに用いる変数
  unsigned int d0, d1 = 0;

  // テーブルから読み出したサンプルとテンプレートの各軸の値
  char sx, sy, sz, tx, ty, tz = 0;

  // DTW用のテーブルを初期化する
  for (i = 1; i <= sampleDataLength; i++) {
    DTW[i][0] = 65535;
  }
  for (i = 1; i <= templateDataLength; i++) {
    DTW[0][i] = 65535;
  }
  DTW[0][0] = 0;

  // DTWの処理
  for (i = 1, is = 0; i <= sampleDataLength; i++, is++) {
    for (j = 1, it = 0; j <= templateDataLength; j++, it++) {
      // フラッシュメモリからテンプレートの各軸の値を読み出す
      tx = pgm_read_byte_near(
             &templateData[templateIndex][it][0]);
      ty = pgm_read_byte_near(
             &templateData[templateIndex][it][1]);
      tz = pgm_read_byte_near(
             &templateData[templateIndex][it][2]);

      // サンプルから各軸の値を読み出す
      sx = sampleData[is][0];
      sy = sampleData[is][1];
      sz = sampleData[is][2];

      // サンプルとテンプレートの点と点の間の距離を求める
      d0 = sqrt(sq(sx - tx) + sq(sy - ty) + sq(sz - tz));

      // 近傍する点で最も近いものとの距離を求める
      d1 = min(DTW[i - 1][j], min(DTW[i][j - 1], 
               DTW[i - 1][j - 1]));

      // DTWの距離としてテーブルに書き込む
      DTW[i][j] = d0 + d1;
    }
  }

  // 求めた距離を返す
  return DTW[sampleDataLength][templateDataLength];
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
  // シリアルを開始
  Serial.begin(9600);
}

void loop() {
  // 開始時刻を読み取る
  unsigned long start = millis();

  // ジェスチャボタンが押されているか否かを読み取る
  boolean isButtonPressed = (digitalRead(buttonPin) == HIGH);

  // 前回押されていなくて今回押されていたら
  if (!wasButtonPressed && isButtonPressed) {
    // シリアルにジェスチャ開始のメッセージをプリントして
    // アクションがあるまで待った後にキャプチャを開始
    Serial.println("Begin gesture");
    waitForAction();
    beginCapture();
  }

  // キャプチャ中であればサンプルを処理
  if (isCapturing) {
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    int z = analogRead(zPin);
    processSample(x, y, z);
  }

  // 前回ジェスチャボタンが押されていたか否かを示すフラグを更新
  wasButtonPressed = isButtonPressed;

  // 次のループ開始までにサンプリング間隔の残り時間だけ待機
  unsigned long elapsedTime = millis() - start;
  if (elapsedTime < samplingInterval) {
    delay(samplingInterval - elapsedTime);
  }
}

