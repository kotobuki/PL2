#include <LiquidCrystal.h>

// センサのANピンに接続したアナログピンの番号
const int sensorPin = 0;

// ライブラリを初期化
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCDの桁数と行数をセット
  lcd.begin(16, 2);
}

void loop() {
  // LCDの表示をクリア
  lcd.clear();

  // センサの値を読み取る
  int value = analogRead(sensorPin);

  // 読み取った値からインチ単位とセンチ単位の距離に変換する
  int rangeInInches = value / 2;
  int rangeInCentimeters 
    = round((float)rangeInInches * 2.54);

  // インチ単位とセンチ単位の距離をそれぞれ表示する
  lcd.setCursor(0, 0);
  lcd.print("Range: ");
  lcd.print(rangeInInches);
  lcd.print(" inch");
  lcd.setCursor(7, 1);
  lcd.print(rangeInCentimeters);
  lcd.print(" cm");

  // 次のループ開始までに100ms待つ
  delay(100);
}

