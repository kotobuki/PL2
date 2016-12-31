// setupはアップロードやリセット、電源投入の後、最初に1度だけ実行される
void setup() {
  // ボード上のLEDに接続したピンのモードをOUTPUT（出力）にセット
  pinMode(LED_BUILTIN, OUTPUT);
}

// loopはArduinoボードの電源がオンであるかぎり、繰り返し実行される
void loop() {
  // LEDに接続したピンの値をHIGHにセットしてLEDを点灯
  digitalWrite(LED_BUILTIN, HIGH);
  // 1000ms（1s）待つ
  delay(1000);
  // LEDに接続したピンの値をLOWにセットしてLEDを消灯
  digitalWrite(LED_BUILTIN, LOW);
  // 1000ms（1s）待つ
  delay(1000);
}
