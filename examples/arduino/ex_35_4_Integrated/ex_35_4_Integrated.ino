#include <FiniteStateMachine.h>
#include "Adafruit_BluefruitLE_SPI.h"

#include "MaxSonar.h"
#include "Motor.h"

// Bluefruitに接続したCSピン、IRQピン、RSTピンの番号
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// 前と後、合計2つのMaxSonarセンサ
MaxSonar sensorF = MaxSonar(A0, 12);
MaxSonar sensorR = MaxSonar(A1, 12);

// 1つめの測距センサのRXピンに接続したピンの番号
const int rxPin = A2;

// 右側と左側、合計2つのモータ
Motor motorR = Motor(11, 10);
Motor motorL = Motor(6, 5);

// それぞれの状態に移行した時、状態にいる間、他の状態に移行する際に
// 実行する関数のプロトタイプ宣言
void enterWaiting();
void updateWaiting();
void enterRunning();
void updateRunning();

// それぞれの状態を定義
// 引数はその状態に入ったとき、アップデートのとき、抜けたときに実行する関数
// 必要ない部分にはNULLを指定する
State WAITING = State(enterWaiting, updateWaiting, NULL);
State RUNNING = State(enterRunning, updateRunning, NULL);

// Finite State Machine、初期状態はWAITING
FSM stateMachine = FSM(WAITING);

// BLEからトリガされたかどうかを示すフラグ
boolean triggered = false;

// BLEからトリガされた時刻
unsigned long triggeredTime = 0;

// 走行中の状態にいるタイムリミット（15秒間）
const unsigned long timeLimitForRunning = 15000;

void setup() {
  // 1つめの測距センサのRXピンに接続したピンのモードを出力にセット
  pinMode(rxPin, OUTPUT);
  digitalWrite(rxPin, LOW);

  // Bluefruitをスタート
  ble.begin(false);

  // ファクトリーリセットを実行
  ble.factoryReset();

  // UARTの受信、接続、切断にコールバックをセット
  ble.setBleUartRxCallback(received);

  // Bluefruitをデータモードにセット
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop() {
  // 1. BLEに関するイベントの処理
  // BLEのイベントをスキャン
  ble.update();

  // もしBLEからトリガをされていたら
  if (triggered) {
    if (stateMachine.isInState(WAITING)) {
      // 待機中であれば走行中に移行
      stateMachine.transitionTo(RUNNING);
    }

    // BLEからトリガされたことを示すフラグをリセット
    triggered = false;
  }

  // 2. 経過時間に関するイベントの処理
  if (stateMachine.isInState(RUNNING)) {
    if ((millis() - triggeredTime) > timeLimitForRunning) {
      // トリガされてからの時間がタイムリミットを超えたら待機中に移行
      stateMachine.transitionTo(WAITING);
    }
  }

  // 1つめの測距センサのRXピンを1msだけHIGHにセットして計測を開始
  digitalWrite(rxPin, HIGH);
  delay(1);
  digitalWrite(rxPin, LOW);

  // 1つのセンサあたりの計測にかかる時間が49msなので2つ分だけ待つ
  delay(98);

  // 前後の測距センサの値を計測する
  sensorF.read();
  sensorR.read();

  // それぞれの状態に応じてアップデート
  stateMachine.update();
}

// BLEからのデータ受信時に呼ばれるコールバック関数
void received(char data[], uint16_t length) {
  // 受け取ったメッセージを文字列に変換
  String message(data);

  // 文字列として受信した値の読み取り開始位置
  int from = 0;

  // メッセージの処理が終了したことを示すフラグ
  boolean noMoreEvent = false;

  // メッセージの処理が終了するまで以下を繰り返す
  while (!noMoreEvent) {
    // 受信した文字列の中で「*」を探す
    int index = message.indexOf("*", from);

    // もし見つからなければ
    if (index < 0) {
      // 処理が終了したと判断してフラグをセット
      noMoreEvent = true;
    }
    // もし見つかったら
    else {
      // 部分文字列をコマンドとして取り出し
      String command = message.substring(from, index);

      // コマンドに応じて処理
      if (command.equals("Run")) {
        triggered = true;
        triggeredTime = millis();
      }

      // 次に処理する読み取り開始位置を更新
      from = index + 1;
    }
  }
}

// 他の状態から待機中に移行する時
void enterWaiting() {
  // BLEに状態をプリント
  ble.println("WAITING");

  // 回転を停止（ブレーキなし）
  motorR.despin(false);
  motorL.despin(false);
}

// 待機中
void updateWaiting() {
  if (!sensorF.isClear()) {
    // 前方に障害物があれば後退
    motorR.reverse(200);
    motorL.reverse(200);
  } else if (!sensorR.isClear()) {
    // 後方に障害物があれば前進
    motorR.forward(200);
    motorL.forward(200);
  } else {
    // それ以外であれば停止
    motorR.despin(false);
    motorL.despin(false);
  }
}

// 他の状態から走行中に移行する時
void enterRunning() {
  // BLEに状態をプリント
  ble.println("RUNNING");
}

// 走行中
void updateRunning() {
  if (sensorF.isClear()) {
    // 前方に障害物がなければ前進
    motorR.forward(255);
    motorL.forward(255);
  } else {
    // そうでなければゆっくり右旋回
    motorR.reverse(150);
    motorL.forward(150);
  }
}

