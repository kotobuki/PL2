// Meanフィルタ用バッファの長さ
const int bufferLength = 5;

// センサが振られたと判断するための閾値
const int threshold = 80;

// 加速度センサのx 軸に接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したピンの番号
const int ledPin = 9;

// Meanフィルタ用バッファ
int buffer[bufferLength];

// バッファにデータを書き込むインデックス
int index = 0;

// LEDの輝度
float intensity = 0;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // Meanフィルタ用バッファを0～1023の中央値で初期化
  for (int i = 0; i < bufferLength; i++) {
    buffer[i] = 511;
  }
}

void loop() {
  // センサの値を読み取る
  int raw = analogRead(sensorPin);

  // スムージング
  int smoothed = processSample(raw);

  // センサの値とスムージングした値の差を求める
  int diff = abs(raw - smoothed);

  // 差が閾値よりも大きければ
  if (diff > threshold) {
    // LEDの輝度を最大にする
    intensity = 255;
  }
  // そうでなければ
  else {
    // LEDの輝度に一定値をかけて減衰させる
    intensity = intensity * 0.9;
  }

  // LEDの輝度をセット
  analogWrite(ledPin, round(intensity));

  // 次のループ開始までに5ms待つ
  delay(5);
}

// Running Meanフィルタによるスムージング
int processSample(int raw) {
  // 読み取った値をバッファに書き込む
  buffer[index] = raw;

  // 書き込んだ次に書き込む位置を更新
  // バッファの最後まで来たら折り返す
  index = (index + 1) % bufferLength;

  // バッファの値の合計を集計するための変数
  long sum = 0;

  // バッファの値の合計を集計
  for (int i = 0; i < bufferLength; i++) {
    sum += buffer[i];
  }

  // 平均をフィルタの出力結果として返す
  return (int)(sum / bufferLength);
}

