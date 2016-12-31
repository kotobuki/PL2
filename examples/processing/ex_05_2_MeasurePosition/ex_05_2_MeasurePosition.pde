import processing.serial.*;
import cc.arduino.*;

// SoftPotを押さえている状態の最小値
final int minimum = 100;

// SoftPotを押さえている状態の最大値
final int maximum = 1000;

// SoftPotから指が離れていると判断するための閾値
final int threshold = 50;

// SoftPotに接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 13;

// Arduino
Arduino arduino;

// 前回押されていたかどうかを保持する変数
boolean wasPressed = false;

void setup() {
  size(400, 400);

  // テキスト表示に使用するフォントを用意
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // 画面を初期化
  background(0);
  text("Position: OFF", 10, 20);
}

void draw() {
  // センサに接続したピンの値を読み取る
  float value = arduino.analogRead(sensorPin);

  // 現在押されているかどうかを示す変数に前回の状態を初期値として代入
  boolean isPressed = wasPressed;

  // 閾値と最小値を元に現在押されているかどうかを判定
  if (value < threshold) {
    // 値が閾値よりも小さければ押されていないと判断
    isPressed = false;
  }
  else if (value >= minimum) {
    // 値が最小値以上であれば押されていると判断
    isPressed = true;
  }

  // 最小値と最大値から現在押されている位置を求める
  // 今回使用したSoftPotの範囲は50mmであるためミリ単位に変換
  float position = map(value, minimum, maximum, 0, 50);

  // 前回押されていたかどうかと今回押されていたかどうかで変化を検出
  if (!wasPressed && isPressed) {
    // 前回押されていなくて今回押されていれば押された瞬間と判断
    onPress(round(position));
  }
  else if (wasPressed && !isPressed) {
    // 前回押されていて今回押されていなければ離された瞬間と判断
    onRelease();
  }
  else if (wasPressed && isPressed) {
    // 前回も今回も押されていればドラッグと判断
    onDrag(round(position));
  }

  // 次回のループ時に参照する前回の状態として現在の状態をセット
  wasPressed = isPressed;
}

// SoftPotを指で押さえたら以下を実行
void onPress(int position) {
  // LEDを点灯して表示を更新
  arduino.digitalWrite(ledPin, Arduino.HIGH);
  background(0);
  text("Position" + position + " mm", 10, 20);
}

// SoftPotから指が離れたら以下を実行
void onRelease() {
  // LEDを消灯して表示を更新
  arduino.digitalWrite(ledPin, Arduino.LOW);
  background(0);
  text("Position: OFF", 10, 20);
}

// SoftPot上でドラッグしたら以下を実行
void onDrag(int position) {
  // 表示を更新
  background(0);
  text("Position: " + position + " mm", 10, 20);
}