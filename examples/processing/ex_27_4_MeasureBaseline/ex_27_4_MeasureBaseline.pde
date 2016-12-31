import processing.serial.*;
import cc.arduino.*;

// 動作状態を表す定数
final int CALIBRATING = 0;
final int RUNNING = 1;

// 環境の状態を表す定数
final int INIT = 0;
final int BRIGHT = 1;
final int DARK = 2;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// Arduino
Arduino arduino;

// Arduinoの準備ができて動作を開始した時刻
int start = 0;

// 現在の動作状態
int operatingState = CALIBRATING;

// キャリブレーション区間におけるサンプルの合計と回数
int total = 0;
int count = 0;

// 閾値とヒステリシス
int threshold = 0;
int hysteresis = 0;

// 前回の環境の状態
int lastCondition = INIT;

void setup() {
  size(400, 400);

  // 表示に使用するフォントを準備
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(ledPin, Arduino.OUTPUT);

  // Arduinoの準備ができて動作を開始した時刻をセット
  start = millis();
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // 現在の状態がキャリブレーション中であれば
  if (operatingState == CALIBRATING) {
    // キャリブレーション中であることを表示
    text("Calibrating", 10, 20);

    // 動作開始から5000msが経過するまでは以下を実行
    if ((millis() - start) < 5000) {
      // センサの値を読み取って加算
      int sensorValue = arduino.analogRead(sensorPin);
      total += sensorValue;
      count++;
    } else {
      // センサの平均値を求める
      float average = total / count;
      println("average: " + average);

      // 平均値から閾値とヒステリシスを決定
      threshold = round(average * 0.9);
      hysteresis = 0;
      if (threshold > 511) {
        hysteresis = round((1023 - threshold) * 0.1);
      } else {
        hysteresis = round(threshold * 0.1);
      }
      println("threshold: " + threshold);
      println("hysteresis: " + hysteresis);

      // 現在の状態を通常動作中に移行
      operatingState = RUNNING;
    }
  }
  // 現在の状態が通常動作中であれば
  else {
    // 現在の状態に前回の状態を代入
    int condition = lastCondition;

    // センサの値を読み取る
    int sensorValue = arduino.analogRead(sensorPin);

    // センサの値に応じて現在の状態を決定
    if (sensorValue > (threshold + hysteresis)) {
      condition = BRIGHT;
    } else if (sensorValue < (threshold - hysteresis)) {
      condition = DARK;
    }

    // 前回の状態と今回の状態が異なれば対応する関数を呼び出す
    if ((lastCondition != BRIGHT) && (condition == BRIGHT)) {
      onBrightenUp();
    } else if ((lastCondition != DARK) 
               && (condition == DARK)) {
      onDarkenUp();
    }

    // 前回の状態として今回の状態を代入
    lastCondition = condition;

    // 通常動作中であることとセンサの値を表示
    text("Running", 10, 20);
    text("Sensor: " + sensorValue, 10, 40);
  }
}

// 明るくなったらLEDを消してシリアルに状態をプリント
void onBrightenUp() {
  arduino.digitalWrite(ledPin, Arduino.LOW);
  println("Brighten up");
}

// 暗くなったらLEDを点けてシリアルに状態をプリント
void onDarkenUp() {
  arduino.digitalWrite(ledPin, Arduino.HIGH);
  println("Darken up");
}