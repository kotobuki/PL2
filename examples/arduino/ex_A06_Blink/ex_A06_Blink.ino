// グローバルな定数としてledPinを宣言
const int ledPin = 12;

void setup() {
  // ここでのledPinは12
  pinMode(ledPin, OUTPUT);

  // 10回点滅を繰返す（この間もledPinは12のまま）
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}

void loop() {
  // ローカルな変数としてledPinを宣言
  int ledPin = 11;

  // ここでのledPinは11
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

