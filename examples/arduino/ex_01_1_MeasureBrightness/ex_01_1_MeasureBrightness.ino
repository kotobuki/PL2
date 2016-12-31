#include <LiquidCrystal.h>

// CdSセルに接続したピンの番号
const int sensorPin = 0;

// LEDに接続したピンの番号
const int ledPin = 9;

// LCDオブジェクト
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // LCDの桁数と行数をセット
  lcd.begin(16, 2);
}

void loop() {
  // 明るさを読み取る
  int brightness = analogRead(sensorPin);

  // LCDの表示をクリアしてから読み取った明るさを表示
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("CdS: ");
  lcd.print(brightness);

  // センサの値（0～1023）をLEDの輝度（255～0）に変換
  int intensity = map(brightness, 0, 1023, 255, 0);

  // LEDの輝度を表示
  lcd.setCursor(0, 1);
  lcd.print("LED: ");
  lcd.print(intensity);

  // LEDに接続したピンに輝度の値をセット
  analogWrite(ledPin, intensity);

  // 次回の処理まで100ms待つ
  delay(100);
}

