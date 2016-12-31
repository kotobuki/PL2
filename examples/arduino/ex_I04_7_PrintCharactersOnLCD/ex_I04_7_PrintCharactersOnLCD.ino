// ［スケッチ］→［ライブラリをインクルード］で［LiquidCrystal］を
// 選択すると自動的に挿入される
#include <LiquidCrystal.h>

// ライブラリを初期化
// 引数は順にLCDのRS、E、DB4、DB5、DB6、DB7に接続したピンの番号
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCDの桁数と行数をセット
  lcd.begin(16, 2);

  // メッセージをLCDにプリント
  lcd.print("Hello, world!");
}

void loop() {
  // カーソルを0 桁目、1 行目にセット
  lcd.setCursor(0, 1);

  // スケッチの動作開始からの経過時間を秒単位で表示
  lcd.print(millis() / 1000);
}

