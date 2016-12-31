#include <LiquidCrystal.h>

// 加速度センサのx軸に接続したアナログピンの番号
const int xAxisPin = 0;

// 加速度センサのy軸に接続したアナログピンの番号
const int yAxisPin = 1;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCDの桁数と行数をセット
  lcd.begin(16, 2);

  // シリアル通信を開始
  Serial.begin(9600);
}

void loop() {
  // x軸とy軸の値を読み取る
  int xAxisValue = analogRead(xAxisPin);
  int yAxisValue = analogRead(yAxisPin);

  // 読み取った値を-1から1までの範囲にスケーリングしてsinθの値とする
  float xAxisSinTheta
    = mapInFloat(xAxisValue, 306, 716, -1, 1);
  float yAxisSinTheta
    = mapInFloat(yAxisValue, 306, 716, -1, 1);

  // それぞれの値を-1から1までの範囲に制限する
  xAxisSinTheta = constrain(xAxisSinTheta, -1, 1);
  yAxisSinTheta = constrain(yAxisSinTheta, -1, 1);

  // 逆サインを求めた結果（単位はラジアン）を度に変換
  int xAxisTilt = floor(asin(xAxisSinTheta) * 180 / PI);
  int yAxisTilt = floor(asin(yAxisSinTheta) * 180 / PI);

  // LCDの表示をクリアしてそれぞれの軸のラベルをプリント
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("x:    y:");

  // それぞれの軸の値をLCDにプリント
  lcd.setCursor(0, 1);
  lcd.print(xAxisTilt);
  lcd.setCursor(6, 1);
  lcd.print(yAxisTilt);

  // それぞれの軸の値をシリアルにプリント
  Serial.print("x: ");
  Serial.print(xAxisTilt);
  Serial.print(", y: ");
  Serial.print(yAxisTilt);
  Serial.println();

  // 次のループ開始までに100ms待つ
  delay(100);
}

// 標準で用意されているmapは引数と戻り値の型がlongである
// 今回は-1から1までにスケーリングする必要があるためfloatで同じ計算をする
float mapInFloat(float x, float iMin, float iMax,
                 float oMin, float oMax) {
  return (x - iMin) * (oMax - oMin) / (iMax - iMin) + oMin;
}

