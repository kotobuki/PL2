// 振動モータに接続したデジタルピンの番号
const int motorPin = 9;

void setup() {
  // 振動モータに接続したピンのモードを出力にセット
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // モータをオン
  digitalWrite(motorPin, HIGH);

  // 500ms待つ
  delay(500);

  // モータをオフ
  digitalWrite(motorPin, LOW);

  // 次のループ開始まで1500ms待つ
  delay(1500);
}

