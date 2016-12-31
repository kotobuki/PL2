import processing.serial.*;
import cc.arduino.*;

// 可変抵抗器に接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// Arduino
Arduino arduino;

// スケッチの動作開始時に1回だけ実行される
void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

// スケッチの実行を終了するまで繰り返し実行される
void draw() {
  // センサの値を読み取る
  int sensorValue = arduino.analogRead(sensorPin);

  // センサの値の範囲（0〜1023）をアナログ出力の範囲（0〜255）に変換した後
  // 四捨五入する
  int brightness = round(map(sensorValue, 0, 1023, 0, 255));

  // 背景の明るさをセンサの値に応じてセット
  background(brightness);

  // LEDの明るさをセンサの値に応じてセット
  arduino.analogWrite(ledPin, brightness);
}