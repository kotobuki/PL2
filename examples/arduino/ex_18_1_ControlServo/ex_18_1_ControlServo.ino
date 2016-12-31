#include <Servo.h>

// 可変抵抗器に接続したアナログピンの番号
const int potentiometerPin = 0;

// サーボ
Servo servo;

void setup() {
  // サーボを使用するピンとしてデジタルピンの9 番をセット
  servo.attach(9);
}

void loop() {
  // 可変抵抗器の値を読み取る
  int value = analogRead(potentiometerPin);

  // 読み取った値を0から179までにスケーリング
  int angle = map(value, 0, 1023, 0, 179);

  // サーボの角度をセット
  servo.write(angle);

  // サーボが指定した角度まで動く間待つ
  delay(15);
}

