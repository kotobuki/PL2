import processing.serial.*;
import cc.arduino.*;

// 曲げセンサに接続したアナログピンの番号
final int sensorPin = 0;

// Arduino
Arduino arduino;

void setup() {
  size(400, 400);

  // テキスト表示で使用するフォントを生成して読み込む
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // センサの値を読み取ってテキストで表示
  text("value : " + arduino.analogRead(sensorPin), 10, 20);
}