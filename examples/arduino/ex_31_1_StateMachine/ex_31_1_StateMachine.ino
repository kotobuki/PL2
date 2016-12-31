#include <LED.h>
#include <Button.h>

// 状態を表す定数：待機中、再生中、一時停止中
const int WAITING = 0;
const int PLAYING = 1;
const int PAUSING = 2;

// 現在の状態
int state = WAITING;

// ボタンとLEDを初期化
Button playButton = Button(8, PULLDOWN);
Button stopButton = Button(9, PULLDOWN);
LED playLed = LED(13);

void setup() {
  // 何かセットアップが必要であればここに記述する
}

// 状態遷移表の内容を条件分岐として記述していく
void loop() {
  // 再生ボタンが押されたら以下を実行
  if (playButton.uniquePress()) {
    if (state == WAITING) {
      // 待機中であれば再生中に移行
      exitWaiting();
      enterPlaying();
      state = PLAYING;
    }
    else if (state == PLAYING) {
      // 再生中であれば一時停止中に移行
      exitPlaying();
      enterPausing();
      state = PAUSING;
    }
    else if (state == PAUSING) {
      // 一時停止中であれば再生中に移行
      exitPausing();
      enterPlaying();
      state = PLAYING;
    }
  }

  // 停止ボタンが押されたら以下を実行
  if (stopButton.uniquePress()) {
    if (state == WAITING) {
      // 待機中に停止ボタンを押しても何も起きない
    }
    else if (state == PLAYING) {
      // 再生中であれば待機中に移行
      exitPlaying();
      enterWaiting();
      state = WAITING;
    }
    else if (state == PAUSING) {
      // 一時停止中であれば待機中に移行
      exitPausing();
      enterWaiting();
      state = WAITING;
    }
  }

  // それぞれの状態に応じて必要なアップデート処理を行う
  if (state == WAITING) {
    updateWaiting();
  }
  else if (state == PLAYING) {
    updatePlaying();
  }
  else if (state == PAUSING) {
    updatePausing();
  }
}

// 他の状態から待機中に移行
void enterWaiting() {
  // 待機中に移行したらLEDを消灯
  playLed.off();
}

// 待機中に行うアップデート処理
void updateWaiting() {
  // アップデート処理をここに
}

// 待機中から他の状態に移行
void exitWaiting() {
  // 他の状態に移行する時に行う処理をここに
}

// 他の状態から再生中に移行
void enterPlaying() {
  // LEDを点灯
  playLed.on();
}

// 再生中に行うアップデート処理
void updatePlaying() {
  // アップデート処理をここに
}

// 再生中から他の状態に移行
void exitPlaying() {
  // 他の状態に移行する時に行う処理をここに
}

// 他の状態から一時停止中に移行
void enterPausing() {
  // 他の状態から移行した時に行う処理をここに
}

// 一時停止中に行うアップデート処理
void updatePausing() {
  // LEDを点滅
  playLed.blink(500);
}

// 一時停止中から他の状態に移行
void exitPausing() {
  // 他の状態に移行する時に行う処理をここに
}

