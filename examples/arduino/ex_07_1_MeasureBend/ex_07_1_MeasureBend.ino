#include <LiquidCrystal.h>

// 曲げセンサに接続したアナログピンの番号
const int sensorPin = 0;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCDの桁数と行数をセット
  lcd.begin(16, 2);
}

void loop() {
  // 曲げセンサの値を読み取る
  int value = analogRead(sensorPin);

  // LCDの表示内容をクリアして、読み取った値を表示
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Flex: ");
  lcd.print(value);

  // 次のループ開始まで100ms待つ
  delay(100);
}


