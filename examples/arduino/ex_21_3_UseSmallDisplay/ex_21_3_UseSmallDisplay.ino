// SPIを扱うためのライブラリ
#include <SPI.h>

// SDカードを扱うためのライブラリ
#include <SD.h>

// スクリーンを扱うためのライブラリ
#include <TFT.h>

// スクリーン
TFT screen = TFT(10, 9, 8);

// イメージ
PImage picture;

void setup() {
  // スクリーンをスタート
  screen.begin();

  // スクリーンの背景色を黒にセット
  screen.background(0, 0, 0);

  // デバッグ用にシリアル通信を開始
  Serial.begin(9600);

  // SD CS
  SD.begin(4);

  // SDカードから画像ファイルを読み込む
  picture = screen.loadImage("sample.bmp");

  // 読み込みに成功していたら
  if (picture.isValid()) {
    // スクリーンに描画する
    screen.image(picture, 0, 0);
  }
}

void loop() {
  // ここでは何もしない
}

