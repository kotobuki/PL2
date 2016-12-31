import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// センサの測距範囲内に対象物がないと判断する閾値
final float threshold = 80;

// Arduino
Arduino arduino;

void setup() {
  size(400, 400);

  // 距離の表示に使用するフォントを生成
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

  // センサの値を読み取る
  int value = arduino.analogRead(sensorPin);

  if (value > threshold) {
    // 読み取った値が閾値よりも大きければ距離に変換して表示
    int range = round((6787 / (value - 3)) - 4);
    text("Range: " + range + " cm", 10, 20);
  }
  else {
    // 読み取った値が閾値以下であれば「OFF」と表示
    text("Range: OFF", 10, 20);
  }
}