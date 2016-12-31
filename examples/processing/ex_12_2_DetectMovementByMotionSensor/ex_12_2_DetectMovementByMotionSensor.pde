import processing.serial.*;
import cc.arduino.*;

// 最後にセンサの反応がなくなってからのタイムアウト時間
final int timeout = 15000;

// センサに接続したピンの番号
final int sensorPin = 2;

// LEDに接続したピンの番号
final int ledPin = 13;

// Arduino
Arduino arduino;

// センサが前回アクティブだったか否か
boolean wasActive = false;

// 最後にセンサがアクティブだった時刻
int lastActive = 0;

void setup() {
  size(400, 400);

  // 状態と経過時間を表示するために使用するフォントを生成
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // センサおよびLEDに接続したピンのモードをセット  
  arduino.pinMode(sensorPin, Arduino.INPUT);
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

void draw() {
  // センサに接続したピンの値を読み取り、現在アクティブか否かを判断
  boolean isActive = false;
  if (arduino.digitalRead(sensorPin) == Arduino.HIGH) {
    isActive = true;
  }

  // 現在の時刻を読み取る
  int now = millis();

  // 現在非アクティブで、かつ最後にアクティブだった時刻から
  // タイムアウト時間が経過していたらLEDを消灯
  if (!isActive && (now - lastActive) > timeout) {
    arduino.digitalWrite(ledPin, Arduino.LOW);
  }

  // 前回非アクティブで今回アクティブであればLEDを点灯
  if (!wasActive && isActive) {
    // LEDを点灯
    arduino.digitalWrite(ledPin, Arduino.HIGH);
  }
  // 前回アクティブで今回非アクティブであれば
  else if (wasActive && !isActive) {
    // 最後にアクティブだった時刻として現在の時刻をセット
    lastActive = now;
  }

  // 前回の値として今回の値をセット
  wasActive = isActive;

  // 現在の状態と経過時間を表示
  background(0);
  text("State: " + (isActive ? "Active" : "Inactive"), 
    10, 20);
  text("Elapsed time: " + (now - lastActive), 10, 50);
}