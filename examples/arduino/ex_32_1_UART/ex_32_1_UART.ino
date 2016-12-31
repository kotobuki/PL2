// Bluefruitのライブラリ
#include "Adafruit_BluefruitLE_SPI.h"

// Bluefruitに接続したCSピン、IRQピン、RSTピンの番号
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

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

  // Bluefruitをスタート
  ble.begin(false);

  // ファクトリーリセットを実行
  ble.factoryReset();
  Serial.println("Factory reset performed");

  // UARTの受信、接続、切断にコールバックをセット
  ble.setBleUartRxCallback(received);
  ble.setConnectCallback(connected);
  ble.setDisconnectCallback(disconnected);

  // Bluefruitをデータモードにセット
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop(void) {
  // イベントをスキャン
  ble.update();

  // ボタンに接続したピンの状態を読み取って押されているか否かを判断
  boolean isPressed = (digitalRead(buttonPin) == HIGH);

  // ボタンが押されたら
  if (!wasPressed && isPressed) {
    // BLEとシリアルにプリント
    ble.print("Pressed*");
    Serial.println("Pressed");
  }
  // ボタンが離されたら
  else if (wasPressed && !isPressed) {
    // BLEとシリアルにプリント
    ble.print("Released*");
    Serial.println("Released");
  }

  // 前回押されていたか否かを表すフラグを更新
  wasPressed = isPressed;
}

// 接続時に呼ばれるコールバック関数
void connected(void) {
  // 接続されたことをシリアルにプリント
  Serial.println("Connected");
}

// 切断時に呼ばれるコールバック関数
void disconnected(void) {
  // 切断されたことをシリアルにプリント
  Serial.println("Disconnected");
}

// 受信時に呼ばれるコールバック関数
void received(char data[], uint16_t length) {
  // 受け取ったメッセージを文字列に変換
  String message(data);
  Serial.print("Received: ");
  Serial.println(message);

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
      if (command.equals("On")) {
        digitalWrite(ledPin, HIGH);
      } else if (command.equals("Off")) {
        digitalWrite(ledPin, LOW);
      }

      // 次に処理する読み取り開始位置を更新
      from = index + 1;
    }
  }
}

