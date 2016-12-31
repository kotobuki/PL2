import processing.serial.*;
import cc.arduino.*;

// モータに接続したピンの番号
final int motorPin = 9;

// Arduino
Arduino arduino;

// 前回トリガした時刻
int lastTrigger = 0;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // モータに接続したピンのモードを出力にセット
  arduino.pinMode(motorPin, Arduino.OUTPUT);
}

void draw() {
  background(100);

  // 現在の時刻を取得
  int now = millis();

  // 前回トリガしてから2000ms経過していたら以下を実行
  if ((now - lastTrigger) > 2000) {
    // モータを200msだけ駆動
    arduino.digitalWrite(motorPin, Arduino.HIGH);
    delay(200);
    arduino.digitalWrite(motorPin, Arduino.LOW);
    lastTrigger = now;
  }
}