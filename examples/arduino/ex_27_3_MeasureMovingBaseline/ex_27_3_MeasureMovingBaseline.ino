// センサに接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したデジタルピンの番号
const int ledPin = 9;

// 状態を表す定数
const int INIT = 0;
const int BRIGHT = 1;
const int DARK = 2;

// ベースラインをアップデートする間隔
const unsigned long UPDATE_INTERVAL = 3000;

// タイムアウトまでの時間
const unsigned long TIMEOUT_DURATION = 10000;

// 閾値
int threshold = 0;

// ヒステリシス
int hysteresis = 0;

// 前回の状態
int lastState = INIT;

// 平均値を計算するためのカウンタ
int count = 0;

// 平均値を計算するための合計
long total = 0;

// 前回キャリブレーションを行った時刻
unsigned long lastCalibration = 0;

// 前回暗くなった時刻
unsigned long lastFallingEdge = 0;

void setup() {
  // LEDを接続したデジタルピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // 動作状態をArduino IDEのシリアルモニタで確認するための通信を開始
  Serial.begin(9600);
}

void loop() {
  // 現在の状態として前回の状態をセット
  int state = lastState;

  // センサの値を読み取る
  int sensorValue = analogRead(sensorPin);

  // 現在の時刻を読み取る
  unsigned long now = millis();

  // 合計とカウンタを更新
  total += sensorValue;
  count++;

  // センサの値に応じて現在の状態を求める
  if (sensorValue > (threshold + hysteresis)) {
    state = BRIGHT;
  }
  else if (sensorValue < (threshold - hysteresis)) {
    state = DARK;
  }

  // 状態の変化に応じて以下を実行
  if ((lastState != BRIGHT) && (state == BRIGHT)) {
    // 明るくなったらonBrightenUp関数を呼び
    onBrightenUp();

    // 合計とカウンタをリセットして再度計測開始
    total = sensorValue;
    count = 1;
    lastCalibration = now;
  }
  else if ((lastState != DARK) && (state == DARK)) {
    // 暗くなったら時刻を更新してonDarkenUp関数を呼ぶ
    lastFallingEdge = now;
    onDarkenUp();
  }

  // 明るい状態で前回のキャリブレーションから一定時間が経過したら
  if ((state == BRIGHT)
      && ((now - lastCalibration) > UPDATE_INTERVAL)) {

    // キャリブレーションを実行して合計とカウンタをリセットして計測開始
    calibrate();
    total = sensorValue;
    count = 1;
    lastCalibration = now;
  }

  // 暗い状態でタイムアウトに設定した時間を超えたら
  if ((state == DARK)
      && ((now - lastFallingEdge) > TIMEOUT_DURATION)) {
    // timeout関数を呼びタイムアウト処理を実行
    timeout();
  }

  // 前回の状態として今回の値をセット
  lastState = state;

  // 次のループ開始までに100ms待つ
  delay(100);
}

// キャリブレーション処理
void calibrate() {
  // カウントが0だと0 除算エラーが発生するためここでチェック
  if (count < 1) {
    return;
  }

  // 合計とカウンタから平均値を求めてシリアルにプリント
  int average = total / count;
  Serial.print("average = ");
  Serial.println(average);

  // 平均値から閾値とヒステリシスを求める
  threshold = int((float)average * 0.9);
  if (threshold > 511) {
    hysteresis = (1023 - threshold) / 10;
  }
  else {
    hysteresis = threshold / 10;
  }
  Serial.print("threshold = ");
  Serial.println(threshold);
  Serial.print("hysteresis = ");
  Serial.println(hysteresis);
}

// タイムアウト処理
void timeout() {
  // 閾値とヒステリシスを0にリセットする
  threshold = 0;
  hysteresis = 0;
  Serial.println("Timeout!");
}

// 明るくなったら以下を実行
void onBrightenUp() {
  // LEDを消灯
  digitalWrite(ledPin, LOW);
  Serial.println("Brighten up");
}

// 暗くなったら以下を実行
void onDarkenUp() {
  // LEDを点灯
  digitalWrite(ledPin, HIGH);
  Serial.println("Darken up");
}

