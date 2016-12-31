// WS2812用のライブラリ
// https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>

// WS2812のピクセル数
const int numOfPixels = 16;

// WS2812の個数、データ端子に接続したピンの番号、モード
Adafruit_NeoPixel pixels 
  = Adafruit_NeoPixel(numOfPixels, 2, NEO_GRB + NEO_KHZ800);

// 各ピクセルの明度
float value[numOfPixels];

// 現在の番号
int currentNum = 0;

void setup() {
  // 各ピクセルの明度を初期化
  for (int pixelNum = 0; pixelNum < numOfPixels; pixelNum++) {
    value[pixelNum] = 0;
  }

  // WS2812をスタート
  pixels.begin();

  // 全体の輝度を設定（255で明るすぎれば小さな値にする）
  pixels.setBrightness(255);
}

void loop() {
  // 各ピクセルをアップデート
  for (int pixelNum = 0; pixelNum < numOfPixels; pixelNum++) {
    // もしピクセル番号が現在の番号と同じなら
    if (pixelNum == currentNum) {
      // ピクセルの明度を最大値にセット
      value[pixelNum] = 1;
    }
    // それ以外であれば
    else {
      // ピクセルの明度を減衰させる
      value[pixelNum] = value[pixelNum] * 0.7;
    }

    // HSV色空間で各ピクセルの色を指定してからRGB色空間に変換
    // Hue（色相）：全ピクセルで1周するように等分
    // Saturation（彩度）：最大値の1で固定
    // Value（明度）：ピクセル番号と現在の番号が同じ時に最大でその後減衰
    float hue = (float)pixelNum / (float)numOfPixels;
    int red, green, blue;
    hsv2rgb(hue, 1.0, value[pixelNum], red, green, blue);

    // ピクセルのRGB値をセット
    pixels.setPixelColor(pixelNum, red, green, blue);
  }

  // アップデートしたピクセルの値を送信
  pixels.show();

  // 現在の番号を更新（ピクセル数以上になったら0に折り返す）
  currentNum = (currentNum + 1) % numOfPixels;

  // 次のループ開始まで25ms待つ
  delay(25);
}

// HSV色空間からRGB色空間に変換
// 参照：www.hcn.zaq.ne.jp/no-ji/lib/ColorSpace.c
// www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1207331496
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

