// ボタンに接続したピンの番号
const int buttonPin = 8;

// ピエゾスピーカに接続したピンの番号
const int speakerPin = 11;

// 前回のボタンの状態
int lastButtonState = LOW;

void setup() {
  // ボタンを接続したピンのモードを入力に
  pinMode(buttonPin, INPUT);

  // スピーカを接続したピンのモードを出力に
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // ボタンの状態を読み取る
  int buttonState = digitalRead(buttonPin);

  // 前回がLOWで現在がHIGHであればonPress()を実行
  if (lastButtonState == LOW && buttonState == HIGH) {
    onPress();
  }

  // 前回のボタンの状態として現在の状態をセット
  lastButtonState = buttonState;

  // 次のループ開始まで10ms待つ
  delay(10);
}

// ボタンを押されたら以下を実行
void onPress() {
  // 以下を100回（0.1秒間）繰り返す
  for (int i = 0; i < 100; i++) {
    // HIGHとLOWを1msごとに繰り返すことで1000Hzの矩形波を生成
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(500);
  }
}

