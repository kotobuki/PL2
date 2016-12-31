#include <Firmata.h>

// ピエゾセンサに接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したデジタルピンの番号
const int ledPin = 13;

// 振動があったと判断するための閾値
const int threshold = 100;

// 前回レポートした時刻
unsigned long lastReport = 0;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // デジタル出力メッセージを受け取った際のコールバックをセット
  Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);

  // Firmataを57600bpsでスタート
  Firmata.begin(57600);
}

void loop() {
  // PC側からのメッセージを処理
  while (Firmata.available()) {
    Firmata.processInput();
  }

  // ピエゾセンサの値を読み取る
  int value = analogRead(sensorPin);

  // 現在の時刻を読み取る
  unsigned long now = millis();

  // 前回のレポートから10ms以上経過していて読み取った値が閾値以上であれば
  if (((now - lastReport) > 10) && (value >= threshold)) {
    // Firmataプロトコルを利用して文字列"K"を送信する
    Firmata.sendString("K");
    // 前回レポートした時刻として現在の時刻をセット
    lastReport = now;
  }
}

// デジタル出力メッセージに対するコールバック
void digitalWriteCallback(byte port, int value) {
  // ポート1（D8～ D15）に関するメッセージであれば以下を実行
  if (port == 1) {
    PORTB = (byte)value;
  }
}

