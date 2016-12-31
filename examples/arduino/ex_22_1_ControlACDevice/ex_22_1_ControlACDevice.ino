// SSRに接続したピンの番号
int ssrPin = 9;

void setup() {
  // SSRに接続したピンのモードを出力にセット
  pinMode(ssrPin, OUTPUT);
}

void loop() {
  // 1秒ごとにオンとオフを繰り返す
  digitalWrite(ssrPin, HIGH);
  delay(1000);
  digitalWrite(ssrPin, LOW);
  delay(1000);
}

