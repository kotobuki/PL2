#include <LiquidCrystal.h>

// タッチパネルのX1、Y2、X2、Y1に接続したピンの番号
// アナログピンをデジタルピンとして使用する場合、A0が14 番に対応する
const int x1Pin = 17; // A3に対応
const int y2Pin = 16; // A2に対応
const int x2Pin = 15; // A1に対応
const int y1Pin = 14; // A0に対応

// タッチパネルが押されていないと判断するための閾値
const int threshold = 20;

// デジタルピンの番号をアナログピンの番号に変換するマクロ
#define ANALOG_PIN_FOR(digitalPinNum) (digitalPinNum - 14)

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// タッチパネルのXとYをおさめる変数
int x, y = 0;

void setup() {
  // LCDの桁数と行数をセット
  lcd.begin(16, 2);
}

void loop() {
  // LCDの表示をクリア
  lcd.clear();

  // タッチパネルをスキャン
  scan();

  // x軸もy軸も閾値以下であればLCDにそれぞれOFFと表示
  if ((x < threshold) && (y < threshold)) {
    lcd.setCursor(0, 0);
    lcd.print("X: OFF");
    lcd.setCursor(0, 1);
    lcd.print("Y: OFF");
  }
  // 閾値よりも大きければ読み取った値をLCDにプリント
  else {
    lcd.setCursor(0, 0);
    lcd.print("X: ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print("Y: ");
    lcd.print(y);
  }

  // 次のループ開始までに100ms待つ
  delay(100);
}

void scan() {
  // X1を5Vに、X2をGNDにセット
  pinMode(x1Pin, OUTPUT);
  pinMode(x2Pin, OUTPUT);
  digitalWrite(x1Pin, HIGH);
  digitalWrite(x2Pin, LOW);

  // Y1とY2をアナログ入力にセット
  digitalWrite(y1Pin, LOW);
  digitalWrite(y2Pin, LOW);
  pinMode(y1Pin, INPUT);
  pinMode(y2Pin, INPUT);

  // 各ピンの設定が安定するまで待ってx軸の値を読み取る
  delay(1);
  x = analogRead(ANALOG_PIN_FOR(y2Pin));

  // Y1をGNDに、Y2を5Vにセット
  pinMode(y1Pin, OUTPUT);
  pinMode(y2Pin, OUTPUT);
  digitalWrite(y1Pin, LOW);
  digitalWrite(y2Pin, HIGH);

  // X1とX2をアナログ入力にセット
  digitalWrite(x1Pin, LOW);
  digitalWrite(x2Pin, LOW);
  pinMode(x1Pin, INPUT);
  pinMode(x2Pin, INPUT);

  // 各ピンの設定が安定するまで待ってy軸の値を読み取る
  delay(1);
  y = analogRead(ANALOG_PIN_FOR(x1Pin));
}
