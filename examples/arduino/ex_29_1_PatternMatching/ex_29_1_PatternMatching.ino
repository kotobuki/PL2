// パターンの総数
const int numPatterns = 8;

// 指使いとパターンの対応表
// 下位ビット→上位ビットの順にスイッチ0 →スイッチ3
// 例：S0がオン、S1がオフ、S2がオン、S3がオンであればB1101
const int fingeringTable[numPatterns] = {
  B1111,
  B1101,
  B0111,
  B0101,
  B1100,
  B0100,
  B0010,
  B0000
};

// パターンが見つからなかった時を表す値
const int notFound = -1;

// パターンと周波数の対応
const int frequency[numPatterns] = {
  262, // C4
  294, // D4
  330, // E4
  349, // F4
  392, // G4
  440, // A4
  494, // B4
  523  // C5
};

// 各タクトスイッチに接続したピンの番号
const int button0Pin = 2;
const int button1Pin = 3;
const int button2Pin = 4;
const int button3Pin = 5;

// スピーカに接続したピンの番号
const int speakerPin = 8;

// 感圧センサに接続したアナログピンの番号
const int sensorPin = 0;

// 感圧センサが押されたと判断するための閾値（上下）
const int thresholdH = 200;
const int thresholdL = 100;

// 前回選択されていたパターン
int lastIndex = notFound;

// 前回感圧センサが押されていたか否か
boolean wasPressed = false;

void setup() {
}

void loop() {
  // センサの値を読み取る
  int value = analogRead(sensorPin);
  // 読み取った値と閾値を比較してセンサが押されているか否かを判断
  boolean isPressed = wasPressed;
  if (value > thresholdH) {
    isPressed = true;
  }
  else if (value < thresholdL) {
    isPressed = false;
  }
  // それぞれのタクトスイッチの状態を読み取る
  // 下位ビット→上位ビットの順にスイッチ0 →スイッチ3
  int buttonState;
  buttonState = digitalRead(button0Pin);
  buttonState += digitalRead(button1Pin) << 1;
  buttonState += digitalRead(button2Pin) << 2;
  buttonState += digitalRead(button3Pin) << 3;
  // 現在の組み合わせに対応するパターンを検索
  int index = findPattern(buttonState);
  // 感圧センサが押されたら
  if (!wasPressed && isPressed) {
    // パターンが見つかっていたら
    if (index != notFound) {
      // パターンに対応する音階で発音
      tone(speakerPin, frequency[index]);
    }
  }
  // 感圧センサが押されていない状態になったら
  else if (wasPressed && !isPressed) {
    // 発音を停止
    noTone(speakerPin);
  }
  // 感圧センサが押されたままであれば
  else if (wasPressed && isPressed) {
    // 前回とパターンが変化していたら
    if (lastIndex != index) {
      // 発音を停止する
      noTone(speakerPin);
      // もしパターンが見つかっていたら
      if (index != notFound) {
        // パターンに対応する音階で発音
        tone(speakerPin, frequency[index]);
      }
    }
  }
  // 前回押されていたか否かを表す変数を更新
  wasPressed = isPressed;
  // 前回のパターンを表す変数を更新
  lastIndex = index;
}

// 与えられたビットパターンに該当する指使いを検索
int findPattern(const int buttonState) {
  // パターンの数だけ以下を繰り返す
  for (int i = 0; i < numPatterns; i++) {
    // もし与えられたパターンと指使いのテーブルが一致したら
    if (fingeringTable[i] == buttonState) {
      // 現在のインデックスを返して関数を抜ける
      return i;
    }
  }
  // パターンが見つからなかったことを示す定数を返す
  return notFound;
}

