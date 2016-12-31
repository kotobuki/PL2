#include <Firmata.h>

// モータドライバのIN1、IN2、PWMに接続したピンの番号
const int in1Pin = 9;
const int in2Pin = 10;
const int pwmPin = 11;

// 左右のセンサに接続したアナログピンの番号
const int leftSensorPin = 0;
const int rightSensorPin = 1;

// センサを遮ったと判断するための閾値
const int THRESHOLD = 300;

// DCモータの回転開始からのタイムアウト
const unsigned int TIMEOUT = 1000;

void setup() {
  // IN1、IN2、PWMに接続したピンのモードを出力にセット
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  // Stringメッセージに対するコールバックをセット
  Firmata.attach(STRING_DATA, stringCallback);

  Firmata.begin(57600);
}

void loop() {
  // 受け取ったメッセージを順次処理する
  while (Firmata.available()) {
    Firmata.processInput();
  }
}

// 順方向に回転
void forward(int value) {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(pwmPin, value);
}

// 逆方向に回転
void reverse(int value) {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(pwmPin, value);
}

// 回転を停止（ブレーキあり／なし）
void despin(boolean useBrake = true) {
  if (useBrake) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
  }
  else {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(pwmPin, 255);
  }
}

// ラックギアを回転させて左端まで移動
void left() {
  // 順方向にゆっくり回転
  forward(80);

  // 現在の時刻を取得
  unsigned int start = millis();

  // 移動方向の反対側のセンサの値が閾値に到達するまで待つ
  while (analogRead(rightSensorPin) > THRESHOLD) {
    delay(1);

    // タイムアウトに達したら中止
    if ((millis() - start) > TIMEOUT) {
      break;
    }
  }

  // 回転を停止（ブレーキあり）
  despin(true);
}

// ラックギアを回転させて右端まで移動
void right() {
  // 逆方向にゆっくり回転
  reverse(80);

  // 現在の時刻を取得
  unsigned int start = millis();

  // 移動方向の反対側のセンサの値が閾値に到達するまで待つ
  while (analogRead(leftSensorPin) > THRESHOLD) {
    delay(1);

    // タイムアウトに達したら中止
    if ((millis() - start) > TIMEOUT) {
      break;
    }
  }
  // 回転を停止（ブレーキあり）
  despin(false);
}

// Stringメッセージを受け取ったら以下が実行される
void stringCallback(char message[]) {
  // 受け取ったメッセージの最初の1 文字で判断
  switch (message[0]) {
  case 'L':
    Firmata.sendString("Left");
    left();
    break;
  case 'R':
    Firmata.sendString("Right");
    right();
    break;
  }
}

