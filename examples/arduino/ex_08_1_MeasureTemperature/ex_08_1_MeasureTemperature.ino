#include <LiquidCrystal.h>

// センサに接続したアナログピンの番号
int sensorPin = 0;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCDの桁数と行数をセットする
  lcd.begin(16, 2);
}

void loop() {
  // LCDの表示をクリアする
  lcd.clear();

  // 温度センサの値を読み取る
  int value = analogRead(sensorPin);

  // 読み取った値を温度に変換する
  int temperature = map(value, 0, 205, 0, 100);

  // LCDに現在の温度を表示する
  lcd.print("Temperature: ");
  lcd.print(temperature);

  // 次のループ開始まで1 秒間待つ
  delay(1000);
}

