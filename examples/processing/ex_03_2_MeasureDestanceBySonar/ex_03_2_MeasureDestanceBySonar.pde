import processing.serial.*;
import cc.arduino.*;

// センサのANピンに接続したアナログピンの番号
final int sensorPin = 0;

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
  float value = arduino.analogRead(sensorPin);

  // 読み取った値をインチ単位とセンチ単位に変換
  float rangeInInches = value / 2;
  float rangeInCentimeters = rangeInInches * 2.54;

  // 小数点以下を四捨五入して距離をそれぞれの単位で表示
  text("Range: " + round(rangeInInches) + " inch", 10, 20);
  text("       " + round(rangeInCentimeters) + " cm", 
       10, 50);
}