// ピエゾセンサに接続したアナログピンの番号
const int sensorPin = 0;

// 振動があったと判断するための閾値
const int threshold = 100;

// 前回レポートした時刻
unsigned long lastReport = 0;

void setup() {
  // シリアル通信を開始
  Serial.begin(9600);
}

void loop() {
  // ピエゾセンサの値を読み取る
  int value = analogRead(sensorPin);

  // 現在の時刻を読み取る
  unsigned long now = millis();

  // 前回のレポートから10ms以上経過していて読み取った値が閾値以上であれば
  if (((now - lastReport) > 10) && (value >= threshold)) {
    // 文字列"T"を送信する（CRとLFが自動的に追加される）
    Serial.println("T");

    // 前回レポートした時刻として現在の時刻をセット
    lastReport = now;
  }
}

