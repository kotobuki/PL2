import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// Arduino
Arduino arduino;

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
  // センサの値を読み取る
  int sensorValue = arduino.analogRead(sensorPin);

  // センサの値の範囲（0〜1023）をアナログ出力の範囲（0〜255）に合わせて
  // 変換した後、四捨五入する
  int brightness = round(map(sensorValue, 0, 1023, 0, 255));

  // 背景の明るさをセンサの値に応じて変更
  background(brightness);

  // LEDの明るさをセンサの値に応じて変更
  arduino.analogWrite(ledPin, brightness);
}