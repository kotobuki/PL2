// 参照
// https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino

// Bluefruitのライブラリ
#include "Adafruit_BLEGatt.h"
#include "Adafruit_BluefruitLE_SPI.h"

// Timer1のライブラリ
#include <TimerOne.h>

// Bluefruitに接続したCSピン、IRQピン、RSTピンの番号
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// GATT
Adafruit_BLEGatt gatt(ble);

// Heart Rate MeasurementのキャラクタリスティックID
uint8_t hrmMeasureCharId;

// Body Sensor LocationのキャラクタリスティックID
uint8_t hrmLocationCharId;

// Pulse Sensorに接続したアナログピンの番号
const int sensorPin = A0;

// LEDに接続したデジタルピンの番号
const int ledPin = 13;

// 割り込みルーチンと共有する変数には修飾キーワードvolatileが必要
// 過去10回分の心拍の時間間隔を平均して求めた心拍数を保持する変数
volatile int BPM;

// 心拍が検出されてBPMが更新された時に真になるブール値
// ユーザによるリセットが必要
volatile boolean quantifiedSelf = false;

void setup(void) {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // Bluefruitをスタート（詳細なデバッグ出力なし）
  ble.begin(false);

  // ファクトリーリセットを実行
  ble.factoryReset();
  Serial.println("Factory reset performed");

  // コマンドのエコーを無効にセット
  ble.echo(false);

  // Heart Rateサービス（UUID = 0x180D）を追加
  gatt.addService(0x180D);

  // Heart Rate Measurementキャラクタリスティックを追加
  // UUID、プロパティ、最小サイズ、最大サイズ、データタイプ
  hrmMeasureCharId = gatt.addCharacteristic(
                       0x2A37,
                       GATT_CHARS_PROPERTIES_READ |
                       GATT_CHARS_PROPERTIES_NOTIFY,
                       2, 3, BLE_DATATYPE_AUTO);

  // Body Sensor Locationキャラクタリスティックを追加
  // 値を0x03（Finger）にセット
  hrmLocationCharId = gatt.addCharacteristic(
                        0x2A38, GATT_CHARS_PROPERTIES_READ,
                        1, 3, BLE_DATATYPE_AUTO);
  gatt.setChar(hrmLocationCharId, 0x03);

  // Heart Rateサービスをアドバタイジングデータに追加
  // Nordicのアプリがサービスを発見するために必要
  uint8_t advertisingData[] = {
    0x02, 0x01, 0x06, 0x05, 0x02, 0x0d, 0x18, 0x0a, 0x18
  };
  ble.setAdvData(advertisingData, sizeof(advertisingData));

  // サービスに対して変更を行った場合にはBluefruit LEのリセットが必要
  ble.reset();

  // 割り込みをセットして2,000µs（2ms）ごとに心拍の測定を実行
  Timer1.initialize(2000);
  Timer1.attachInterrupt(measureHeartBeat);

  Serial.println("Waiting for connection");
}

void loop(void) {
  // 接続していなければ以下の処理はスキップ
  if (!ble.isConnected()) {
    return;
  }

  // もし心拍を計測できていたら
  if (quantifiedSelf) {
    // Heart Rateキャラクタリスティックの値をセット
    unsigned char heartRateData[2]
      = {0, (unsigned char)BPM};
    gatt.setChar(hrmMeasureCharId, heartRateData, 2);

    // 次回のためにQuantified Selfフラグをリセット
    quantifiedSelf = false;
  }

  // 次の通知までに1秒待つ
  delay(1000);
}

// 割り込み内で使用する変数
int IBI = 600;                   // 心拍の時間間隔の保持に使用
boolean Pulse = false;           // 心拍検出時のみ真になるブール値
int rate[10];                    // 過去10回のIBI値を保持する配列
unsigned long sampleCounter = 0; // パルスのタイミング判定に使用
unsigned long lastBeatTime = 0;  // IBIの計測に使用
int P = 512;                     // パルス波の山の検出に使用
int T = 512;                     // パルス波の谷の検出に使用
int thresh = 525;                // 心拍の瞬間を検出するのに使用
int amp = 100;                   // パルス波の振幅の保持に使用
boolean firstBeat = true;        // 配列rateに適切なシード値を
boolean secondBeat = false;      // 与えるのに使用

// 心拍を計測する割り込みルーチン
void measureHeartBeat() {
  int Signal = analogRead(sensorPin);   // センサの値を読み取る
  sampleCounter += 2;                   // ミリ秒単位で時間を記録
  int N = sampleCounter - lastBeatTime; // 前の拍からの時間を計算

  // 前回のIBIの3/5だけ待つことで干渉ノイズを回避しつつ
  if ((Signal < thresh) && (N > (IBI / 5) * 3)) {
    if (Signal < T) {
      T = Signal; // パルス波の最も低い値を記録する
    }
  }

  // 閾値条件を用いてノイズを回避しつつ
  if (Signal > thresh && Signal > P) {
    P = Signal; // パルス波の最も高い値を記録する
  }

  // いよいよ心拍を計測する
  // パルスがある時にはいつでもSignalの値は急上昇する
  if (N > 250) { // 高い周波数のノイズを回避する
    if ((Signal > thresh) && (Pulse == false)
        && (N > (IBI / 5) * 3)) {
      Pulse = true; // パルスがあると思われる時はPulseフラグをセット
      digitalWrite(ledPin, HIGH);         // 13番ピンのLEDを点灯
      IBI = sampleCounter - lastBeatTime; // 拍間の時間を計測
      lastBeatTime = sampleCounter; // 次のパルスのため時刻を記録

      if (secondBeat) {                // もし2番目の拍であれば
        secondBeat = false;            // secondBeatフラグをクリア
        for (int i = 0; i <= 9; i++) { // 正しいBPMをスタート時に
          rate[i] = IBI;               // 得られるよう現在までの合計
        }                              // をシード値として与える
      }

      if (firstBeat) {     // もし拍を検出したのが初めてであれば
        firstBeat = false; // firstBeatフラグをクリア
        secondBeat = true; // secondBeatフラグをセット
        return;            // 今回のIBI値は信頼できないので捨てる
      }

      // 過去10回分のIBI値の合計を記録し続ける
      word runningTotal = 0;         // 合計を記録する変数

      for (int i = 0; i <= 8; i++) { // 配列中のデータをシフトし
        rate[i] = rate[i + 1];       // 最も古いIBI値を捨て
        runningTotal += rate[i];     // 古い方から9個のIBI値を加算
      }

      rate[9] = IBI;              // 最新のIBI値をrate配列に追加し
      runningTotal += rate[9];    // runningTotalに加算し
      runningTotal /= 10;         // 過去10個のIBI値から平均を求め
      BPM = 60000 / runningTotal; // 1分あたりの拍数=BPMを求める
      quantifiedSelf = true;      // quantifiedSelfフラグをセット
      // quantifiedSelfフラグは割り込みルーチンの中ではクリアされない
    }
  }

  // もし値が下降していればその拍は終わりとみなし
  if (Signal < thresh && Pulse == true) {
    digitalWrite(ledPin, LOW); // 13番ピンのLEDを消灯
    Pulse = false;             // 次回のためにPulseフラグをリセット
    amp = P - T;               // パルス波の振幅を取得
    thresh = amp / 2 + T;      // 振幅の50%に閾値をセット
    P = thresh;                // 次回のために
    T = thresh;                // パルスの山と谷をリセット
  }

  if (N > 2500) {                 // 拍が無いまま2.5秒間経過したら
    thresh = 512;                 // 閾値をデフォルトに戻す
    P = 512;                      // Pをデフォルトに戻す
    T = 512;                      // Tをデフォルトに戻す
    lastBeatTime = sampleCounter; // lastBeatTimeを更新
    firstBeat = true;             // 再び心拍が戻ってきた時のために
    secondBeat = false;           // これらの変数をリセット
  }
}

