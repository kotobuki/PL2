// Bluefruitのライブラリ
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BLEEddystone.h"

// Bluefruitに接続したCSピン、IRQピン、RSTピンの番号
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// Eddystone
Adafruit_BLEEddystone eddyBeacon(ble);

// ボタンに接続したピンの番号
const int buttonPin = 2;

// LEDに接続したピンの番号
const int ledPin = 13;

// 前回ボタンが押されていたか否か
boolean wasPressed = false;

void setup(void) {
  // ボタンに接続したピンのモードを入力にセット
  pinMode(buttonPin, INPUT);

  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // 動作確認用のシリアル通信を開始
  Serial.begin(115200);

  // Bluefruitをスタート（詳細なデバッグ出力なし）
  ble.begin(false);

  // ファクトリーリセットを実行
  ble.factoryReset();
  Serial.println("Factory reset performed");

  // Eddystoneビーコンサービスを有効にする
  eddyBeacon.begin(true);

  // URLをセットする
  eddyBeacon.setURL("http://www.adafruit.com/");
}

void loop(void) {
  // ボタンに接続したピンの状態を読み取って押されているか否かを判断
  boolean isPressed = (digitalRead(buttonPin) == HIGH);

  // ボタンが押されたら
  if (!wasPressed && isPressed) {
    // LEDを点灯
    digitalWrite(ledPin, HIGH);

    // 配信を開始
    eddyBeacon.startBroadcast();
    Serial.println("Broadcasting");
  }
  // ボタンが離されたら
  else if (wasPressed && !isPressed) {
    // LEDを消灯
    digitalWrite(ledPin, LOW);

    // 配信を停止
    eddyBeacon.stopBroadcast();
    Serial.println("Stopped broadcasting");
  }

  // 前回押されていたか否かを表すフラグを更新
  wasPressed = isPressed;

  // 次回のループ開始までに1秒待つ
  delay(1000);
}

