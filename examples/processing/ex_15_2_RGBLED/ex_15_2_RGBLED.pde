import processing.serial.*;
import cc.arduino.*;

// LEDのドライブ方法に関する定数
final int COMMON_KATHODE = 0;
final int COMMON_ANODE = 1;

// R、G、BそれぞれのLEDに接続したデジタルピンの番号
final int rLEDPin = 9;
final int gLEDPin = 10;
final int bLEDPin = 11;

// R、G、Bそれぞれをコントロールする可変抵抗器に接続したアナログピンの番号
final int rPotPin = 0;
final int gPotPin = 1;
final int bPotPin = 2;

// Arduino
Arduino arduino;

// LEDのドライブモード。アノードコモンの場合にはここをCOMMON_ANODEに変更する
int driveMode = COMMON_KATHODE;

void setup() {
  size(200, 200);

  // テキスト表示用のフォントを生成してセット
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(rLEDPin, Arduino.OUTPUT);
  arduino.pinMode(gLEDPin, Arduino.OUTPUT);
  arduino.pinMode(bLEDPin, Arduino.OUTPUT);
}

void draw() {
  // 3つの可変抵抗器の値を読み取る
  int rPotPinValue = arduino.analogRead(rPotPin);
  int gPotPinValue = arduino.analogRead(gPotPin);
  int bPotPinValue = arduino.analogRead(bPotPin);

  // カソードコモンであれば可変抵抗器の値をそのまま出力にセット
  if (driveMode == COMMON_KATHODE) {
    arduino.analogWrite(
      rLEDPin, round(map(rPotPinValue, 0, 1023, 0, 255)));
    arduino.analogWrite(
      gLEDPin, round(map(gPotPinValue, 0, 1023, 0, 255)));
    arduino.analogWrite(
      bLEDPin, round(map(bPotPinValue, 0, 1023, 0, 255)));
  }
  // アノードコモンであれば可変抵抗器の値を反転させて出力にセット
  else {
    arduino.analogWrite(
      rLEDPin, round(map(rPotPinValue, 0, 1023, 255, 0)));
    arduino.analogWrite(
      gLEDPin, round(map(gPotPinValue, 0, 1023, 255, 0)));
    arduino.analogWrite(
      bLEDPin, round(map(bPotPinValue, 0, 1023, 255, 0)));
  }

  // 背景を黒で塗りつぶしてR、G、Bそれぞれの値を表示
  background(0);
  text("A0 (R): " + rPotPinValue, 10, 20);
  text("A1 (G): " + gPotPinValue, 10, 40);
  text("A2 (B): " + bPotPinValue, 10, 60);
}