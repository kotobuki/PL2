// 閾値（値は環境に応じて修正）
const int threshold = 511;

// ヒステリシス（値は環境に応じて修正）
const int hysteresis = 102;

// 光センサに接続したアナログピンの番号
const int sensorPin = 0;

// LEDに接続したデジタルピンの番号
const int ledPin = 9;

// 前回の状態
boolean wasBright = true;

void setup() {
  // LEDに接続したピンのモードを出力に設定
  pinMode(ledPin, OUTPUT);

  // LEDを消灯
  digitalWrite(ledPin, LOW);

  // シリアルモニタでセンサの値を確認するための通信を開始
  Serial.begin(9600);
}

void loop() {
  // 現在の明るさ
  int brightness = analogRead(sensorPin);

  // 現在の明るさをシリアルにプリント
  Serial.println(brightness);

  // 現在の状態（初期値には前回の値を代入）
  boolean isBright = wasBright;
  if (brightness > (threshold + hysteresis)) {
    // 現在の明るさが閾値＋ヒステリシスよりも大きければ明るいと判断
    isBright = true;
  }
  else if (brightness < (threshold - hysteresis)) {
    // 現在の明るさが閾値ーヒステリシスよりも小さければ暗いと判断
    isBright = false;
  }
  else {
    // 上記に該当しない場合は前回の状態をそのまま引き継ぐ
  }
  if (!wasBright && isBright) {
    // 暗い状態から明るい状態に変化したら
    onBrightenUp();
  }
  else if (wasBright && !isBright) {
    // 明るい状態から暗い状態に変化したら
    onDarkenUp();
  }

  // 前回の値として今回の値をセット
  wasBright = isBright;

  // 10ms後に次のループを実行
  delay(10);
}

// 明るくなったらLEDを消灯
void onBrightenUp() {
  digitalWrite(ledPin, LOW);
}

// 暗くなったらLEDを点灯
void onDarkenUp() {
  digitalWrite(ledPin, HIGH);
}

