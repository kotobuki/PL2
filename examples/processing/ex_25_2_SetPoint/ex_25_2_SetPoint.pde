import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// 閾値
final int threshold = 511;

// ヒステリシス
final int hysteresis = 102;

// Arduino
Arduino arduino;

// 前回の状態
boolean wasBright = true;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // 現在の明るさを読み取る
  int brightness = arduino.analogRead(sensorPin);

  // 現在の状態（初期値には前回の値を代入）
  boolean isBright = wasBright;
  if (brightness > (threshold + hysteresis)) {
    // 現在の明るさが閾値＋ヒステリシスよりも大きければ明るいと判断
    isBright = true;
  } else if (brightness < (threshold - hysteresis)) {
    // 現在の明るさが閾値ーヒステリシスよりも小さければ暗いと判断
    isBright = false;
  } else {
    // 上記に該当しない場合は前回の状態をそのまま引き継ぐ
  }
  if (!wasBright && isBright) {
    // 暗い状態から明るい状態に変化したら
    onBrightenUp();
  } else if (wasBright && !isBright) {
    // 明るい状態から暗い状態に変化したら
    onDarkenUp();
  }

  // 全回の値として今回の値をセット
  wasBright = isBright;
}

// 明るくなったらLEDを消灯
void onBrightenUp() {
  arduino.digitalWrite(ledPin, Arduino.LOW);
}

// 暗くなったらLEDを点灯
void onDarkenUp() {
  arduino.digitalWrite(ledPin, Arduino.HIGH);
}