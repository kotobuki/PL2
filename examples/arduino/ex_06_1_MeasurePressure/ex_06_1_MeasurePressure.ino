// センサに接続したアナログピンの番号
int sensorPin = 0;

// LEDに接続したピンの番号
int ledPin = 9;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // センサの値を読み取る
  int value = analogRead(sensorPin);

  // 読み取った値からLEDの明るさを求めてLED の明るさを更新
  int intensity = map(value, 0, 1023, 0, 255);
  analogWrite(ledPin, intensity);

  // 次のループ開始までに10ms待つ
  delay(10);
}

