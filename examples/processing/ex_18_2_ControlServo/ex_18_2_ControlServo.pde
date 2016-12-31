import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// サーボに接続したデジタルピンの番号
final int servoPin = 9;

// Arduino
Arduino arduino;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // サーボに接続したピンのモードをSERVOにセット
  arduino.pinMode(servoPin, Arduino.SERVO);
}

void draw() {
  // センサの値を読み取る
  int sensorValue = arduino.analogRead(sensorPin);
  
  // アナログ入力の範囲（0〜1023）をサーボの範囲（0〜179）に合わせて変換し、
  // その値を四捨五入する
  int angle = round(map(sensorValue, 0, 1023, 0, 179));

  // 背景の明るさを角度の値に応じて変更
  background(angle);

  // サーボの角度をセンサの値に応じて変更
  arduino.servoWrite(servoPin, angle);
}