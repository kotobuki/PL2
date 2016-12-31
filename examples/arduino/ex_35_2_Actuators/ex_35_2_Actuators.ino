#include "Motor.h"

// 右側と左側、合計2つのモータ
Motor motorR = Motor(11, 10);
Motor motorL = Motor(6, 5);

void setup() {
  // 確認用のシリアル出力をスタート
  Serial.begin(9600);
}

void loop() {
  // 500ms間前進
  motorR.forward(255);
  motorL.forward(255);
  Serial.println("Forward");
  delay(500);

  // 回転を停止（ブレーキあり）して2000ms待つ
  motorR.despin(true);
  motorL.despin(true);
  Serial.println("Despin (with brake)");
  delay(2000);

  // 500ms間後退
  motorR.reverse(255);
  motorL.reverse(255);
  Serial.println("Reverse");
  delay(500);

  // 回転を停止（ブレーキなし）して2000ms待つ
  motorR.despin(false);
  motorL.despin(false);
  Serial.println("Despin (without brake)");
  delay(2000);

  // 500ms間右旋回
  motorR.reverse(255);
  motorL.forward(255);
  Serial.println("Clockwise turning");
  delay(500);

  // 回転を停止（ブレーキあり）して2000ms待つ
  motorR.despin(true);
  motorL.despin(true);
  delay(2000);

  // 500ms間左旋回
  motorR.forward(255);
  motorL.reverse(255);
  Serial.println("Counter-clockwise turning");
  delay(500);

  // 回転を停止（ブレーキあり）して2000ms待つ
  motorR.despin(true);
  motorL.despin(true);
  delay(2000);
}

