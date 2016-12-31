// 各状態を表す定数
const int unknown = 0;
const int bright = 1;
const int dark = 2;

// 状態が変化してから確定するまでに待機する時間
const int timeToWait = 1000;

// 明るいと判断する閾（しきい）値
const int thresholdH = 700;

// 暗いと判断する閾（しきい）値
const int thresholdL = 300;

// センサに接続したピンの番号
const int sensorPin = 0;

// LEDに接続したピンの番号
const int ledPin = 9;

// 現在の状態
int state = unknown;

// 次に移行する状態
int nextState = unknown;

// 最後にセンサの状態が変化した時刻
unsigned long lastChange = 0;

// 前回のセンサの状態
int lastSensorState = unknown;

void setup() {
  // LEDを接続したピンのモードを出力にセットしてLEDを消灯
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // 現在の時刻を取得する
  unsigned long now = millis();

  // センサから現在の明るさを読み取る
  int brightness = analogRead(sensorPin);

  // 現在のセンサの状態を表す変数の初期に前回のセンサの状態を代入
  int sensorState = lastSensorState;

  // 読み取った値と閾値を比較して現在のセンサの状態をセット
  if (brightness > thresholdH) {
    sensorState = bright;
  }
  else if (brightness < thresholdL) {
    sensorState = dark;
  }

  // 前回のセンサの状態と現在のセンサの状態が異なれば
  if (lastSensorState != sensorState) {
    // bright以外からbrightに変化したら
    if (sensorState == bright) {
      // 次に移行する状態をbrightにセットして変化のあった時刻をリセット
      nextState = bright;
      lastChange = now;
    }
    // dark以外からdarkに変化したら
    else if (sensorState == dark) {
      // 次に移行する状態をdarkにセットして変化のあった時刻をリセット
      nextState = dark;
      lastChange = now;
    }
  }

  // 前回のセンサの状態として今回の値をセット
  lastSensorState = sensorState;

  // 現在の状態と次に移行する状態が異なり
  // かつセンサの状態が変化してから一定時間が経過していたら
  if (state != nextState
    && ((now - lastChange) > timeToWait)) {
    // 次に移行する状態がbrightであれば
    if (nextState == bright) {
      // LEDを消灯
      digitalWrite(ledPin, LOW);
    }
    // 次に移行する状態がdarkであれば
    else if (nextState == dark) {
      // LEDを点灯
      digitalWrite(ledPin, HIGH);
    }

    // 現在の状態を更新
    state = nextState;
  }

  // 次のループ開始までに100ms待つ
  delay(100);
}

