// 最後にセンサの反応がなくなってからのタイムアウト時間
const unsigned long timeout = 15000;

// センサに接続したデジタルピンの番号
const int sensorPin = 2;

// LEDに接続したデジタルピンの番号
const int ledPin = 13;

// 前回アクティブだったか否か
boolean wasActive = false;

// 最後にセンサがアクティブだった時刻
unsigned long lastActive = 0;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // センサに接続したピンの値がHIGHであればアクティブと判断
  boolean isActive = (digitalRead(sensorPin) == HIGH);

  // 現在の時刻を読み取る
  unsigned long now = millis();

  // 現在非アクティブで、かつ最後にアクティブだった時刻から
  // タイムアウト時間が経過していたらLEDを消灯
  if (!isActive && (now - lastActive) > timeout) {
    digitalWrite(ledPin, LOW);
  }

  // 前回非アクティブで今回アクティブであればLEDを点灯
  if (!wasActive && isActive) {
    // LEDを点灯
    digitalWrite(ledPin, HIGH);
  }
  // 前回アクティブで今回非アクティブであれば
  else if (wasActive && !isActive) {
    // 最後にアクティブだった時刻として現在の時刻をセット
    lastActive = now;
  }

  // 前回の値として今回の値をセット
  wasActive = isActive;

  // 次のループ開始までに10ms待つ
  delay(10);
}

