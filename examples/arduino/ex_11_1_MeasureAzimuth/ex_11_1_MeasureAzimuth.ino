// 参照：github.com/Seeed-Studio/Grove_3Axis_Digital_Compass
#include <Wire.h>

// HMC5883LのI2Cアドレス
// データシートに記載されているのは0x3C（write）および0x3D（read）だが、
// これは8bitで表現したアドレスであるため、7bitでの表現にしたものを
// アドレスとして扱う
const int i2cAddress = 0x3C >> 1;

// 現在地の磁気偏角（単位はラジアン）
// http://www.magnetic-declination.com/
// 以下は大垣での例
// OGAKI
// Latitude: 35° 21' 0" N
// Longitude: 136° 37' 0" E
// Magnetic declination: -7° 39'
const float declinationAngle = 7.39;

// RGB LED中の赤、緑、青に接続したピンの番号
const int redPin = 9;
const int greenPin = 11;
const int bluePin = 10;

// X軸とY軸、Z軸の値
float x = 0;
float y = 0;
float z = 0;

// X軸とY軸のオフセット
float xOffset = 0;
float yOffset = 0;

// キャリブレーション区間の最小値、最大値、カウンタ
int xMin = 4095;
int xMax = 0;
int yMin = 4095;
int yMax = 0;
int count = 0;

void setup() {
  // RGB LEDとボード上のLEDに接続したピンのモードを出力にセット
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // I2Cバスをスタート
  Wire.begin();

  // センサのモードを設定
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x02); // モード設定用レジスタ
  Wire.write(0x00); // 連続計測モード
  Wire.endTransmission();

  Wire.beginTransmission(i2cAddress);
  Wire.write(0x01); // モード設定用レジスタ
  Wire.write(0x20); // 連続計測モード
  Wire.endTransmission();

  // 読み取った方位角をシリアルモニタで確認するためシリアル通信をスタート
  Serial.begin(9600);

  // キャリブレーション
  // 0.1秒間隔で50回、合計5秒間の最大値と最小値を求める
  for (int i = 0; i < 50; i++) {
    // センサから3軸の値を読み取る
    readFromSensor();

    // 最大値と最小値を更新
    xMax = max(xMax, x);
    xMin = min(xMin, x);
    yMax = max(yMax, y);
    yMin = min(yMin, y);

    // カウンタが偶数の時は内蔵LEDを点灯、奇数の時は消灯
    if ((i % 2) == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

    delay(100);
  }

  // 5秒間の最大値と最小値からオフセットを求める
  xOffset = (xMax - xMin) / 2.0F;
  yOffset = (yMax - yMin) / 2.0F;
}

void loop() {
  // センサから3軸の値を読み取る
  readFromSensor();

  // X軸とY軸の値から方位角を計算
  float heading
    = atan2(y - yOffset, x - xOffset) * 180.0 / PI;

  // 磁気偏角を加算
  heading += declinationAngle;

  // 求めた方位角を0〜359の範囲に修正
  if (heading < 0) {
    heading += 360;
  } else if (heading > 359) {
    heading -= -360;
  }

  // 求めた方位角を四捨五入してシリアルにプリント
  Serial.println(round(heading));

  // 方位角からHue（色相）を決める
  // Saturation（彩度）とValue（明度）は1で固定
  float h = heading / 360;
  float s = 1, v = 1;
  int r, g, b;

  // HSV色空間からRGB色空間に変換
  hsv2rgb(h, s, v, r, g, b);

  // RGB LEDのそれぞれのLEDの輝度を更新
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  // 次のループ開始までに100ms待つ
  delay(100);
}

void readFromSensor() {
  // デジタルコンパスからデータを読み取る
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.beginTransmission(i2cAddress);
  Wire.requestFrom(i2cAddress, 6);

  // 6バイト分のデータが揃うまで待つ
  while (Wire.available() < 6);

  // 6バイト分のデータを読み取る
  uint8_t xMSB = Wire.read();
  uint8_t xLSB = Wire.read();
  uint8_t zMSB = Wire.read();
  uint8_t zLSB = Wire.read();
  uint8_t yMSB = Wire.read();
  uint8_t yLSB = Wire.read();

  // それぞれ下位8ビット、上位4ビット、合計12ビット分を加算
  x = (int16_t)(xLSB | ((int16_t)xMSB << 8));
  y = (int16_t)(yLSB | ((int16_t)yMSB << 8));
  z = (int16_t)(zLSB | ((int16_t)zMSB << 8));
}

// HSV色空間からRGB色空間に変換
// 参照：www.hcn.zaq.ne.jp/no-ji/lib/ColorSpace.c
// 　　　www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1207331496
void hsv2rgb(float h, float s, float v,
             int& r, int& g, int& b) {
  float phase, ofs, d1, d2, d3;

  if (s == 0) {
    r = floor(v * 255);
    g = floor(v * 255);
    b = floor(v * 255);
  }
  else {
    phase = (h - floor(h)) * 6;
    ofs = phase - floor(phase);
    d1 = v * (1 - s);
    d2 = v * (1 - s * ofs);
    d3 = v * (1 - s * (1 - ofs));
    switch ((int)phase) {
      case 0:
        r = floor(v * 255);
        g = floor(d3 * 255);
        b = floor(d1 * 255);
        break;
      case 1:
        r = floor(d2 * 255);
        g = floor(v * 255);
        b = floor(d1 * 255);
        break;
      case 2:
        r = floor(d1 * 255);
        g = floor(v * 255);
        b = floor(d3 * 255);
        break;
      case 3:
        r = floor(d1 * 255);
        g = floor(d2 * 255);
        b = floor(v * 255);
        break;
      case 4:
        r = floor(d3 * 255);
        g = floor(d1 * 255);
        b = floor(v * 255);
        break;
      case 5:
        r = floor(v * 255);
        g = floor(d1 * 255);
        b = floor(d2 * 255);
        break;
    }
  }
}

