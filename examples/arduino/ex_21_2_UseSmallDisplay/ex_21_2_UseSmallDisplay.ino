// SPIを扱うためのライブラリ
#include <SPI.h>

// スクリーンを扱うためのライブラリ
#include <TFT.h>

// ボタンに接続したピンの番号
const int buttonPin = 2;

// スクリーン
TFT screen = TFT(10, 9, 8);

// 前回ボタンが押されていたか否か
boolean wasPressed = true;

void setup() {
  // ボタンに接続したピンのモードをプルアップ付き入力にセット
  pinMode(buttonPin, INPUT_PULLUP);
  
  // スクリーンをスタート
  screen.begin();

  // スクリーンの背景色を黒にセット
  screen.background(0, 0, 0);

  // 描画色を白にセット
  screen.stroke(255, 255, 255);
  screen.fill(255, 255, 255);

  // 矩形を描画（左上のxとy、右下のxとy）
  screen.rect(0, 0, 87, 17);

  // 描画色を赤にセット
  screen.stroke(255, 0, 0);

  // 赤い枠を描画
  screen.rect(0, 0, 87, 17);

  // 文字サイズを1に指定して文字列を描画
  screen.setTextSize(1);
  screen.text("Make:", 5, 5);

  // 描画色をシアンにセットして文字列を描画
  screen.stroke(0, 174, 239);
  screen.text("PROJECTS", 35, 5);

  // 文字サイズを2に指定して文字列を描画
  screen.setTextSize(2);
  screen.text("Prototyping\nLab", 0, 20);

  // スケッチの動作開始からの経過時間のラベルとなる文字列を描画
  screen.stroke(255, 255, 255);
  screen.setTextSize(1);
  screen.text("Time:", 0, 120);
}

void loop() {
  // 現在ボタンが押されているか否かをチェック
  // プルアップなので押された時がLOW
  boolean isPressed = (digitalRead(buttonPin) == LOW);

  // 前回ボタンが押されていなくて今回押されていれば
  if (!wasPressed && isPressed) {
    // マゼンタで円を描画
    screen.stroke(236, 0, 140);
    screen.fill(236, 0, 140);
    screen.circle(80, 80, 20);
  }
  // 前回ボタンが押されていて今回押されていなければ
  else if (wasPressed && !isPressed) {
    // グレーで円を描画
    screen.stroke(100, 100, 100);
    screen.fill(100, 100, 100);
    screen.circle(80, 80, 20);
  }

  // 前回のボタンの状態として今回の状態をセット
  wasPressed = isPressed;

  // 時刻の文字列を表示する部分だけを黒で塗りつぶす
  screen.stroke(0, 0, 0);
  screen.fill(0, 0, 0);
  screen.rect(30, 120, 90, 127);

  // 時刻を文字列として描画
  screen.stroke(255, 255, 255);
  screen.setTextSize(1);
  screen.text(String(millis(), DEC).c_str(), 30, 120);

  // 次のループ開始までに100ms待つ
  delay(100);
}

