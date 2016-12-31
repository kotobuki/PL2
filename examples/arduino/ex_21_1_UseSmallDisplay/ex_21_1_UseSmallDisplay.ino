// SPIを扱うためのライブラリ
#include <SPI.h>

// スクリーンを扱うためのライブラリ
#include <TFT.h>

// スクリーン
TFT screen = TFT(10, 9, 8);

void setup() {
  // スクリーンをスタート
  screen.begin();

  // スクリーンの背景色を黒にセット
  screen.background(0, 0, 0);

  // 描画色を白にセット
  screen.stroke(255, 255, 255);

  // 文字サイズを1にセット
  screen.setTextSize(1);

  // 文字列をスクリーン左上に描画
  screen.text("Hello, world!", 0, 0);
}

void loop() {
  // loopでは特に何も処理を行わない
}

