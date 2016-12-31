#include <Wire.h>

// Bluefruitのライブラリ
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BLEMIDI.h"

// MPR121のライブラリ
#include "Adafruit_MPR121.h"

// Bluefruitに接続したCSピン、IRQピン、RSTピンの番号
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// MIDI over BLE
Adafruit_BLEMIDI midi(ble);

// MPR121
Adafruit_MPR121 cap = Adafruit_MPR121();

// 前回のタッチ状態
uint16_t lastTouchStatus = 0;

void setup(void) {
  // 動作確認用のシリアル通信を開始
  Serial.begin(115200);

  // Bluefruitをスタート（詳細なデバッグ出力なし）
  ble.begin(false);

  // ファクトリーリセットを実行
  ble.factoryReset();
  Serial.println("Factory reset performed");

  // MIDI over BLEをスタート
  midi.begin();

  // MPR121をスタート（デフォルトのアドレスは0x5A）
  cap.begin(0x5A);
}

void loop(void) {
  // 現在のタッチ状態を取得する
  uint16_t touchStatus = cap.touched();

  // 12個の電極についてそれぞれ前回と今回の状態を比較
  for (int i = 0; i < 12; i++) {
    // もし前回タッチされていなくて今回タッチされていたら
    if (!bitRead(lastTouchStatus, i)
        && bitRead(touchStatus, i)) {
      // 対応するNote Onを送信
      midi.send(0x90, 60 + i, 127);

      // 確認用にシリアルにもプリント
      Serial.print("Note On: ");
      Serial.println(i);
    }
    // もし前回タッチされていて今回タッチされていなかったら
    if (bitRead(lastTouchStatus, i)
        && !bitRead(touchStatus, i)) {
      // 対応するNote Offを送信
      midi.send(0x80, 60 + i, 0);

      // 確認用にシリアルにもプリント
      Serial.print("Note Off: ");
      Serial.println(i);
    }
  }

  // 前回のタッチ状態として今回のタッチ状態をセット
  lastTouchStatus = touchStatus;

  // 次回のループ開始までに10ミリ秒待つ
  delay(10);
}

