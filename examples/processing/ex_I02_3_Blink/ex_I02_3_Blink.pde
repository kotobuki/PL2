import processing.serial.*;
import cc.arduino.*;

// LEDに接続したピンの番号
final int ledPin = 13;

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

  // ウィンドウの背景を黒で塗りつぶす
  background(0);
}

// スケッチの実行を終了するまで繰り返し実行される
void draw() {
  // ここでは何もしない
}

// マウスのボタンが押されたら
void mousePressed() {
  // LEDを点灯
  arduino.digitalWrite(ledPin, Arduino.HIGH);

  // ウィンドウの背景を白で塗りつぶす
  background(255);
}

// マウスのボタンが離されたら
void mouseReleased() {
  // LEDを消灯
  arduino.digitalWrite(ledPin, Arduino.LOW);

  // ウィンドウの背景を黒で塗りつぶす
  background(0);
}