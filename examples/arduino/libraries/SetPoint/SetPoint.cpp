// ライブラリのヘッダファイルをインクルードする
#include "SetPoint.h"

// コンストラクタ
SetPoint::SetPoint() {
  // 非公開メンバ変数を初期化する
  _threshold = 0;
  _hysteresis = 0;
  _lastState = -1;
  _risingEdgeEventHandler = NULL;
  _fallingEdgeEventHandler = NULL;
}

// 閾値とヒステリシスを与えて初期化
void SetPoint::begin(int threshold, int hysteresis) {
  // 引数をメンバ変数に代入
  _threshold = threshold;
  _hysteresis = hysteresis;
}

// イベントハンドラをセット
void SetPoint::attach(int command,
                      eventHandlerFunction eventHandler) {
  // コマンドに応じてメンバ変数に代入
  switch (command) {
    case RISING_EDGE:
      _risingEdgeEventHandler = eventHandler;
      break;
    case FALLING_EDGE:
      _fallingEdgeEventHandler = eventHandler;
      break;
  }
}

// 新しい値を与えて更新
void SetPoint::update(int value) {
  // 今回の状態を表す変数を宣言して前回の状態で初期化
  int state = _lastState;

  // 新しい値が閾値からヒステリシスを引いた値よりも小さければ
  if (value < (_threshold - _hysteresis)) {
    // 現在の状態をLOWにセット
    state = LOW;
  }
  // 新しい値が閾値にヒステリシスを加えた値よりも大きければ
  else if (value > (_threshold + _hysteresis)) {
    // 現在の状態をHIGHにセット
    state = HIGH;
  }

  // 前回がHIGH以外で今回がHIGHであれば
  if ((_lastState != HIGH) && (state != HIGH)) {
    // 立ち上がりイベントのイベントハンドラがNULLでなければ呼ぶ
    if (_risingEdgeEventHandler != NULL) {
      (*_risingEdgeEventHandler)();
    }
  }
  // 前回がLOW以外で今回がLOWであれば
  else if ((_lastState != LOW) && (state == LOW)) {
    // 立ち下がりイベントのイベントハンドラがNULLでなければ呼ぶ
    if (_fallingEdgeEventHandler != NULL) {
      (*_fallingEdgeEventHandler)();
    }
  }

  // 前回の状態を示す変数を今回の値で更新
  _lastState = state;
}

