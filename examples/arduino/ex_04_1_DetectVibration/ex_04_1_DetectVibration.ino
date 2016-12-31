// ピエゾ素子に接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したデジタルピンの番号
const int ledPin = 13;

// 振動と判断する閾値
const int threshold = 100;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // ピエゾ素子に接続したアナログピンの値を読み取る
  int value = analogRead(sensorPin);

  // 読み取った値が閾値以上であれば以下を実行
  if (value >= threshold) {
    // LEDを点灯させ、200ms 待って消灯
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}

