#include <LiquidCrystal.h>

// SoftPotを押さえている状態の最小値
const int minimum = 100;

// SoftPotを押さえている状態の最大値
const int maximum = 1000;

// SoftPotを離していると判断するための閾値
const int threshold = 50;

// SoftPotに接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したピンの番号
const int ledPin = 13;

// 前回押されていたかどうかを保持する変数
boolean wasPressed = false;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // LCDの桁数と行数をセット
  lcd.begin(16, 2);
}

void loop() {
  // LCDの表示をクリア
  lcd.clear();

  // SoftPotの値を読み取る
  int value = analogRead(sensorPin);

  // LCDに読み取った値を表示
  lcd.setCursor(0, 0);
  lcd.print("SoftPot: ");
  lcd.print(value);

  // 現在押されているかどうかのフラグ
  boolean isPressed = wasPressed;

  // 閾値と最小値から現在押されているかどうかを判定
  if (value < threshold) {
    isPressed = false;
  }
  else if (value >= minimum) {
    isPressed = true;
  }

  // 最小値と最大値から現在押されている位置を求める
  // 今回使用したSoftPotの範囲は50mmであるためミリ単位に変換
  int position = map(value, minimum, maximum, 0, 50);

  // 前回押されていたかどうかと今回押されていたかどうかで変化を検出
  // 前回押されていなくて今回押されていたら
  if (!wasPressed && isPressed) {
    onPress(position);
  }
  // 前回押されていて今回押されていなければ
  else if (wasPressed && !isPressed) {
    onRelease();
  }
  // 前回に引き続き今回も押されていたら
  else if (wasPressed && isPressed) {
    onDrag(position);
  }

  // 次回のループ時に使用する値として現在の状態をセット
  wasPressed = isPressed;

  // 次のループ開始までに10ms待つ
  delay(10);
}

// SoftPotを押されたら以下を実行
void onPress(int position) {
  // LEDを点灯
  digitalWrite(ledPin, HIGH);

  // LCDに現在の位置を表示
  lcd.setCursor(0, 1);
  lcd.print("Position: ");
  lcd.print(position);
  lcd.print(" mm");
}

// SoftPotから離されたら以下を実行
void onRelease() {
  // LEDを消灯
  digitalWrite(ledPin, LOW);

  // LCDに現在の状態を表示
  lcd.setCursor(0, 1);
  lcd.print("Position: OFF");
}

// SoftPot上でドラッグしたら以下を実行
void onDrag(int position) {
  // LCDに現在の位置を表示
  lcd.setCursor(0, 1);
  lcd.print("Position: ");
  lcd.print(position);
  lcd.print(" mm");
}

