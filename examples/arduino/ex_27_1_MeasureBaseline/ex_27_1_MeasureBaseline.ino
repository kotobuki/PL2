// センサに接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したデジタルピンの番号
const int ledPin = 9;

// 動作状態を表す定数
const int INIT = 0;
const int BRIGHT = 1;
const int DARK = 2;

// 閾値
int threshold = 0;

// ヒステリシス
int hysteresis = 0;

// 前回の状態
int lastState = INIT;

void setup() {
  // LEDを接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // シリアル通信を開始
  Serial.begin(9600);

  // ベースラインを計測
  measureBaseline();
}

void loop() {
  // 現在の状態に前回の状態を代入
  int state = lastState;

  // センサの値を読み取る
  int sensorValue = analogRead(sensorPin);

  // センサの値に応じて現在の状態を決定
  if (sensorValue > (threshold + hysteresis)) {
    state = BRIGHT;
  }
  else if (sensorValue < (threshold - hysteresis)) {
    state = DARK;
  }

  // 前回の状態と今回の状態が異なれば対応する関数を呼び出す
  if ((lastState != BRIGHT) && (state == BRIGHT)) {
    onBrightenUp();
  }
  else if ((lastState != DARK) && (state == DARK)) {
    onDarkenUp();
  }

  // 前回の状態として今回の状態を代入
  lastState = state;

  // 次回のループ開始までに100ms 待つ
  delay(100);
}

// ベースラインを計測する
void measureBaseline() {
  // 読み取った値の合計と読み取った回数
  long total = 0;
  int count = 0;

  // シリアルにキャリブレーション開始をプリント
  Serial.println("Calibrating...");

  // 動作開始から5000ms以内の場合に以下を実行
  while (millis() < 5000) {
    // センサの値を読み取って加算
    int sensorValue = analogRead(sensorPin);
    total += sensorValue;
    count++;
    delay(1);
  }

  // シリアルにキャリブレーション終了をプリント
  Serial.println("Done !");
  Serial.println();

  // 合計と回数から平均を求めてシリアルにプリント
  int average = total / count;
  Serial.print("total = ");
  Serial.println(total);
  Serial.print("count = ");
  Serial.println(count);
  Serial.print("average = ");
  Serial.println(average);

  // 求めた平均から閾値とヒステリシスを決定
  threshold = int((float)average * 0.9);
  if (threshold > 511) {
    hysteresis = (1023 - threshold) / 10;
  }
  else {
    hysteresis = threshold / 10;
  }

  // シリアルに閾値とヒステリシスをプリント
  Serial.print("threshold = ");
  Serial.println(threshold);
  Serial.print("hysteresis = ");
  Serial.println(hysteresis);
}

// 明るくなったらLEDを消してシリアルに状態をプリント
void onBrightenUp() {
  digitalWrite(ledPin, LOW);
  Serial.println("Brighten up");
}

// 暗くなったらLEDを点けてシリアルに状態をプリント
void onDarkenUp() {
  digitalWrite(ledPin, HIGH);
  Serial.println("Darken up");
}

