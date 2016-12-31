// WS2812用のライブラリ
// https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>

// WS2812のピクセル数
const int numOfPixels = 16;

// WS2812の個数、データ端子に接続したピンの番号、モード
Adafruit_NeoPixel pixels
  = Adafruit_NeoPixel(numOfPixels, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  // シリアル通信を開始
  Serial.begin(9600);

  // WS2812をスタート
  pixels.begin();

  // 全体の輝度を設定（255で明るすぎれば小さな値にする）
  pixels.setBrightness(255);
}

void loop() {
  // ここでは何もしない
}

// シリアルで受信した時に呼ばれる関数
void serialEvent() {
  // Hue（色相）、Saturation（彩度）、Brightness（明度）
  float hue = 0, saturation = 0, brightness = 0;

  // 文字列として受信した値の読み取り開始位置
  int from = 0;

  // 受け取った値のカウント
  int count = 0;

  // 最後の値に到達したことを示すフラグ
  boolean foundLastValue = false;

  // 改行に対応する文字コード10を受信するまで待つ
  String message = Serial.readStringUntil(10);

  // 最後の値に到達するまで以下を繰り返す
  while (!foundLastValue) {
    // 受信した文字列の中で「,」を探す
    int index = message.indexOf(",", from);

    // もし「,」が見つからなければ
    if (index < 0) {
      // 最後の文字列となるので、この値が3つめであれば明度としてセット
      String valueString = message.substring(from);
      count++;
      if (count == 3) {
        brightness = (float)valueString.toInt() / 100.0;
      }

      // 最後の値に到達したことを示すフラグをセット
      foundLastValue = true;
    }
    // もし「,」が見つかった場合には
    else {
      // 値の文字列を抜き出して
      String valueString = message.substring(from, index);
      from = index + 1;
      count++;

      // 1つめの値であれば色相としてセット
      if (count == 1) {
        hue = (float)valueString.toInt() / 360.0;
      }
      // 2つめの値であれば彩度としてセット
      else if (count == 2) {
        saturation = (float)valueString.toInt() / 100.0;
      }
    }
  }

  // もし3つの値を受信していれば
  if (count == 3) {
    // HSB色空間からRGB色空間に変換
    int red, green, blue;
    hsv2rgb(hue, saturation, brightness, red, green, blue);

    // 全てのピクセルのRGB値をセット
    for (int pixelNum = 0; pixelNum < numOfPixels; pixelNum++) {
      pixels.setPixelColor(pixelNum, red, green, blue);
    }

    // アップデートしたピクセルの値を送信
    pixels.show();
  }
}

// HSV色空間からRGB色空間に変換
// 参照：www.hcn.zaq.ne.jp/no-ji/lib/ColorSpace.c
// www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1207331496
void hsv2rgb(float h, float s, float v, int& r, int& g, int& b) {
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

