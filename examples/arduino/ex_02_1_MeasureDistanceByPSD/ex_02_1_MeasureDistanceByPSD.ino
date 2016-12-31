#include <LiquidCrystal.h>

// センサに接続したアナログピンの番号
const int sensorPin = 0;

// センサの測距範囲内に対象物がないと判断する閾値
const int threshold = 80;

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

  // LCDに表示
  lcd.setCursor(0, 0);
  lcd.print("Range: ");

  if (value > threshold) {
    // 読み取った値が閾値よりも大きければ距離に変換して表示
    int range = (6787 / (value - 3)) - 4;
    lcd.print(range);
    lcd.print(" cm");
  }
  else {
    // 読み取った値が閾値以下であれば「OFF」と表示
    lcd.print("OFF");
  }

  // 次のループ開始までに100ms待つ
  delay(100);
}

