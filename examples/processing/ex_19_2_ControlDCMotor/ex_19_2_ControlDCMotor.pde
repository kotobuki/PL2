import processing.serial.*;
import cc.arduino.*;

// 独立したPWMピンを用いないTA7291Pの場合にはfalseにする
final boolean useSeparatePWMPin = true;

// IN1、IN2、PWMに接続したピンの番号
final int in1Pin = 9;
final int in2Pin = 10;
final int pwmPin = 11;

// Arduino
Arduino arduino;

// 最後に状態を変更した時刻
int lastChange = 0;

// 現在の状態
int state = -1;

void setup() {
  size(400, 400);

  // テキスト表示で使用するフォントを生成
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // IN1、IN2、PWMに接続したピンのモードを出力にセット
  arduino.pinMode(in1Pin, Arduino.OUTPUT);
  arduino.pinMode(in2Pin, Arduino.OUTPUT);
  arduino.pinMode(pwmPin, Arduino.OUTPUT);
}

void draw() {
  // 現在の時刻を取得
  int now = millis();

  // 前回状態を変更してから500ms経過していたら以下を実行
  if ((now - lastChange) > 500) {
    // 状態を次に進める（0から3 の間で繰り返す）
    state = (state + 1) % 4;

    // 状態に応じて以下を実行
    switch (state) {
    case 0: // 順方向に回転
      forward(255);
      background(0);
      text("Forward", 10, 20);
      break;
    case 1: // 回転を停止（ブレーキあり）
      despin(true);
      background(0);
      text("Despin (with brake)", 10, 20);
      break;
    case 2: // 逆方向に回転
      reverse(255);
      background(0);
      text("Reverse", 10, 20);
      break;
    case 3: // 回転を停止（ブレーキなし）
      despin(false);
      background(0);
      text("Despin (without brake)", 10, 20);
      break;
    }

    // 前回状態を変更した時刻を更新
    lastChange = now;
  }
}

// escキーを押して実行を停止した時に以下を実行
void stop() {
  // 回転を停止（ブレーキなし）
  despin(false);

  // 元々の終了処理を行う
  super.stop();
}

// 順方向に回転
void forward(int value) {
  if (useSeparatePWMPin) {
    // 独立したPWMピンを用いる場合
    arduino.digitalWrite(in1Pin, Arduino.HIGH);
    arduino.digitalWrite(in2Pin, Arduino.LOW);
    arduino.analogWrite(pwmPin, value);
  } else {
    // 独立したPWMピンを用いない場合
    arduino.analogWrite(in1Pin, value);
    arduino.digitalWrite(in2Pin, Arduino.LOW);
  }
}

// 逆方向に回転
void reverse(int value) {
  if (useSeparatePWMPin) {
    // 独立したPWMピンを用いる場合
    arduino.digitalWrite(in1Pin, Arduino.LOW);
    arduino.digitalWrite(in2Pin, Arduino.HIGH);
    arduino.analogWrite(pwmPin, value);
  } else {
    // 独立したPWMピンを用いない場合
    arduino.digitalWrite(in1Pin, Arduino.LOW);
    arduino.analogWrite(in2Pin, value);
  }
}

// 回転を停止
void despin(boolean useBrake) {
  if (useBrake) {
    // ブレーキあり
    arduino.digitalWrite(in1Pin, Arduino.HIGH);
    arduino.digitalWrite(in2Pin, Arduino.HIGH);
    arduino.digitalWrite(pwmPin, Arduino.HIGH);
  } else {
    // ブレーキなし
    arduino.digitalWrite(in1Pin, Arduino.LOW);
    arduino.digitalWrite(in2Pin, Arduino.LOW);
    arduino.digitalWrite(pwmPin, Arduino.LOW);
  }
}