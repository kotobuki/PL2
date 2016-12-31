#include <LED.h>
#include <Button.h>

// イベントハンドラのプロトタイプ宣言
typedef void (*EVENT_HANDLER)();

// 再生及び停止ボタンを押したとき、および更新のイベントハンドラ
EVENT_HANDLER playButtonEventHandler;
EVENT_HANDLER stopButtonEventHandler;
EVENT_HANDLER updateEventHandler;

// ボタンとLEDを初期化
Button playButton = Button(8, PULLDOWN);
Button stopButton = Button(9, PULLDOWN);
LED playLed = LED(13);

void setup() {
  // 待機状態に入る
  enterWaiting();
}

void loop() {
  // 再生ボタンが押されたら
  if (playButton.uniquePress()) {
    // イベントハンドラがNULLでなければ
    if (playButtonEventHandler != NULL) {
      // 関数ポインタplayButtonEventHandlerの示す関数を呼び出す
      (*playButtonEventHandler)();
    }
  }

  // 停止ボタンが押されたら
  if (stopButton.uniquePress()) {
    // イベントハンドラがNULLでなければ
    if (stopButtonEventHandler != NULL) {
      // 関数ポインタstopButtonEventHandlerの示す関数を呼び出す
      (*stopButtonEventHandler)();
    }
  }

  // 各状態におけるアップデート処理
  if (updateEventHandler) {
    // イベントハンドラがNULLでなければ
    if (stopButtonEventHandler != NULL) {
      // 関数ポインタupdateEventHandlerの示す関数を呼び出す
      (*updateEventHandler)();
    }
  }
}

void enterWaiting() {
  // イベントハンドラをセット
  // 待機中に停止ボタンを押しても何も起きない
  playButtonEventHandler = enterPlaying;
  stopButtonEventHandler = NULL;
  updateEventHandler = updateWaiting;

  // 再生中を示すLEDを消灯
  playLed.off();
}

// 待機中のアップデート処理
void updateWaiting() {
  // 待機中に行う処理があればここに
}

void enterPlaying() {
  // イベントハンドラをセット
  playButtonEventHandler = enterPausing;
  stopButtonEventHandler = enterWaiting;
  updateEventHandler = updatePlaying;

  // 再生中を示すLEDを点灯
  playLed.on();
}

// 再生中のアップデート処理
void updatePlaying() {
  // 再生中に行う処理があればここに
}

// 一時停止状態に移行した時に呼ばれる
void enterPausing() {
  // イベントハンドラをセット
  playButtonEventHandler = enterPlaying;
  stopButtonEventHandler = enterWaiting;
  updateEventHandler = updatePausing;
}

// 一時停止中のアップデート処理
void updatePausing() {
  // LEDを点滅
  playLed.blink(500);
}

