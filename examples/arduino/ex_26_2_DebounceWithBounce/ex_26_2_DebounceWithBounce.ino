#include <LiquidCrystal.h>
#include <Bounce2.h>

// ボタンに接続したピンの番号
const int buttonPin = 8;

// デバウンサ
Bounce debouncer = Bounce();

// ボタンが押されたカウント
int count = 0;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // ボタンに接続したピンのモードを入力にセット
  pinMode(buttonPin, INPUT);

  // デバウンサにピンとデバウンス時間をセット
  debouncer.attach(buttonPin);
  debouncer.interval(10);

  // LCDの桁数と行数をセット
  lcd.begin(16, 2);

  // カウントをLCDにプリント
  printCount();
}

void loop() {
  // デバウンサを更新
  debouncer.update();

  // LOWからHIGHに変化していれば
  if (debouncer.rose()) {
    onPress();
  }
}

void onPress() {
  // カウントを1だけ増やす
  count = count + 1;
  // LCDにカウントをプリント
  printCount();
}

void printCount() {
  // LCDの表示内容をクリアした後カウントをプリント
  lcd.clear();
  lcd.print("Count: ");
  lcd.print(count);
}

