#include <FiniteStateMachine.h>

#include "Motor.h"

// 右側と左側、合計2つのモータ
Motor motorR = Motor(11, 10);
Motor motorL = Motor(6, 5);

// それぞれの状態に移行した時、状態にいる間、他の状態に移行する際に
// 実行する関数のプロトタイプ宣言
void enterWaiting();
void enterRunning();

// それぞれの状態を定義
// 引数はその状態に入ったとき、アップデートのとき、抜けたときに実行する関数
// 必要ない部分にはNULLを指定する
State WAITING = State(enterWaiting, NULL, NULL);
State RUNNING = State(enterRunning, NULL, NULL);

// Finite State Machine、初期状態はWAITING
FSM stateMachine = FSM(WAITING);

void setup() {
  // 何かセットアップが必要であればここに記述する
}

void loop() {
  unsigned long now = millis();

  // 同じ状態で2秒間が経過したら
  if (stateMachine.timeInCurrentState() > 2000) {
    if (stateMachine.isInState(WAITING)) {
      // 待機中であれば走行中に移行
      stateMachine.transitionTo(RUNNING);
    }
    else if (stateMachine.isInState(RUNNING)) {
      // 走行中であれば待機中に移行
      stateMachine.transitionTo(WAITING);
    }
  }

  // それぞれの状態に応じてアップデート
  stateMachine.update();
}

// 他の状態から待機中に移行する時
void enterWaiting() {
  // 回転を停止（ブレーキなし）
  motorR.despin(false);
  motorL.despin(false);
}

// 他の状態から走行中に移行する時
void enterRunning() {
  // 前進
  motorR.forward(255);
  motorL.forward(255);
}

