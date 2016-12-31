// LEDに接続したピンの番号
int led = 9;

// LEDの明るさ
int brightness = 0;

// 毎回LEDをフェードさせる量
int fadeAmount = 5;

void setup() {
  // LEDに接続したピンを出力にセット
  pinMode(led, OUTPUT);
}

void loop() {
  // LEDに接続したピンにbrightnessの値をセット
  analogWrite(led, brightness);

  // 次回loopを実行する時のために明るさの値を変える
  brightness = brightness + fadeAmount;

  // フェードが端まで到達したらフェードの方向を反転する
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // 30ms待つ
  delay(30);
}
