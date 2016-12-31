import processing.serial.*;
import cc.arduino.*;

// X、Y、タッチの有無を表すピン
final int xPin = 0;
final int yPin = 1;
final int touchPin = 2;

// 前回タッチされていたか否か
boolean wasTouched = false;

// 前回のXとYの値
float lastX = 0;
float lastY = 0;

// Arduino
Arduino arduino;

void setup() {
  size(640, 480);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // 背景を黒で塗りつぶして線の描画色を白にセット
  background(0);
  stroke(255);
}

void draw() {
  // touchPinの値から現在タッチされている否かを読み取る
  boolean isTouched = (arduino.analogRead(touchPin) == 1023);

  // 現在のXとYの値を読み取り、ウィンドウのサイズに合わせて変換
  float x 
    = map(arduino.analogRead(xPin), 0, 1023, 0, width - 1);
  float y 
    = map(arduino.analogRead(yPin), 0, 1023, 0, height - 1);

  // もし前回に引き続きタッチされていれば
  if (wasTouched && isTouched) {
    // 前回の位置から直線を描画する
    line(lastX, lastY, x, y);
  }

  // 前回の値として現在の値をセット
  wasTouched = isTouched;
  lastX = x;
  lastY = y;
}