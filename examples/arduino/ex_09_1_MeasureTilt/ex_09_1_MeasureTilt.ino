// 傾きセンサに接続したピンの番号
const int sensorPin = 8;

// LEDに接続したピンの番号
const int ledPin = 13;

void setup() {
  // 傾きセンサに接続したピンのモードを入力に
  pinMode(sensorPin, INPUT);

  // LEDに接続したピンのモードを出力に
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // センサの状態を読み取る
  int sensorState = digitalRead(sensorPin);

  // 読み取った値をLEDにセット
  digitalWrite(ledPin, sensorState);

  // 次のループ開始までに10ms待つ
  delay(10);
}

