import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// Arduino
Arduino arduino;

// 温度
float temperature = 0;

void setup() {
  size(400, 400);

  // テキストフォントを生成してセット
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);
}

void draw() {
  // 背景を黒く塗りつぶす
  background(0);

  // 温度センサの値を読み取る
  int value = arduino.analogRead(sensorPin);

  // 読み取った値を温度に変換してテキストで表示
  int temperature = round(map(value, 0, 205, 0, 100));  
  text("Temperature: " + temperature, 20, 20);
}