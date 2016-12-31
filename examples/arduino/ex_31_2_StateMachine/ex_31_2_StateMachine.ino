#include <LED.h>
#include <Button.h>
#include <FiniteStateMachine.h>

// それぞれの状態に移行した時、状態にいる間、他の状態に移行する際に
// 実行する関数のプロトタイプ宣言
void enterWaiting();
void updateWaiting();
void exitWaiting();
void enterPlaying();
void updatePlaying();
void exitPlaying();
void enterPausing();
void updatePausing();
void exitPausing();

// それぞれの状態を定義
// 引数はその状態に入ったとき、アップデートのとき、抜けたときに実行する関数
State WAITING = State(enterWaiting, updateWaiting,
                      exitWaiting);
State PLAYING = State(enterPlaying, updatePlaying,
                      exitPlaying);
State PAUSING = State(enterPausing, updatePausing,
                      exitPausing);

// Finite State Machine、初期状態はWAITING
FSM stateMachine = FSM(WAITING);

// ボタンとLEDを初期化
Button playButton = Button(8, PULLDOWN);
Button stopButton = Button(9, PULLDOWN);
LED playLed = LED(13);

void setup() {
  // 何かセットアップが必要であればここに記述する
}

void loop() {
  // 再生ボタンが押されたら以下を実行
  if (playButton.uniquePress()) {
    if (stateMachine.isInState(WAITING)) {
      // 待機中であれば再生中に移行
      stateMachine.transitionTo(PLAYING);
    }
    else if (stateMachine.isInState(PLAYING)) {
      // 再生中であれば一時停止中に移行
      stateMachine.transitionTo(PAUSING);
    }
    else if (stateMachine.isInState(PAUSING)) {
      // 一時停止中であれば再生中に移行
      stateMachine.transitionTo(PLAYING);
    }
  }

  // 停止ボタンが押されたら以下を実行
  if (stopButton.uniquePress()) {
    if (stateMachine.isInState(WAITING)) {
      // 待機中に停止ボタンを押しても何も起きない
    }
    else if (stateMachine.isInState(PLAYING)) {
      // 再生中であれば待機中に移行
      stateMachine.transitionTo(WAITING);
    }
    else if (stateMachine.isInState(PAUSING)) {
      // 一時停止中であれば待機中に移行
      stateMachine.transitionTo(WAITING);
    }
  }

  // それぞれの状態に応じてアップデート
  stateMachine.update();
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

