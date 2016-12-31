#include <Firmata.h>

// タッチパネルのX1、Y2、X2、Y1に接続したピンの番号
const int x1Pin = 17; // A3
const int y2Pin = 16; // A2
const int x2Pin = 15; // A1
const int y1Pin = 14; // A0

// タッチパネルが押されていないと判断するための閾値
const int threshold = 10;

// パネルをタッチした状態でのXとY の最小値と最大値
const int xMin = 50;
const int xMax = 800;
const int yMin = 100;
const int yMax = 750;

// デジタルピンの番号をアナログピンの番号に変換するマクロ
#define ANALOG_PIN_FOR(digitalPinNum) (digitalPinNum - 14)

// タッチパネルのXとYをおさめる変数
int x, y = 0;

void setup() {
  // Firmataを開始
  Firmata.begin(57600);
}

void loop() {
  // PC側からメッセージが届いていれば処理
  while (Firmata.available()) {
    Firmata.processInput();
  }

  // タッチパネルをスキャン
  scan();

  // XとY の値を0から1023までにノーマライズしてA0とA1としてレポート
  Firmata.sendAnalog(0, map(x, xMin, xMax, 0, 1023));
  Firmata.sendAnalog(1, map(y, yMin, yMax, 0, 1023));

  // x 軸もy 軸も閾値以下であれば
  if ((x < threshold) && (y < threshold)) {
    // A2の値として0をレポート
    Firmata.sendAnalog(2, 0);
  }
  // 閾値よりも大きければ
  else {
    // A2の値として1023をレポート
    Firmata.sendAnalog(2, 1023);
  }

  // A3からA7までの値をレポート
  for (int analogPin = 3; analogPin < TOTAL_ANALOG_PINS;
       analogPin++) {
    Firmata.sendAnalog(analogPin, 0);
  }

  // 次のループ開始までに20ms待つ
  delay(20);
}

void scan() {
  // X1を5Vに、X2をGNDにセット
  pinMode(x1Pin, OUTPUT);
  pinMode(x2Pin, OUTPUT);
  digitalWrite(x1Pin, HIGH);
  digitalWrite(x2Pin, LOW);

  // Y1とY2をアナログ入力にセット
  digitalWrite(y1Pin, LOW);
  digitalWrite(y2Pin, LOW);
  pinMode(y1Pin, INPUT);
  pinMode(y2Pin, INPUT);

  // 各ピンの設定が安定するまで待ってx軸の値を読み取る
  delay(1);
  x = analogRead(ANALOG_PIN_FOR(y2Pin));

  // Y1をGNDに、Y2を5Vにセット
  pinMode(y1Pin, OUTPUT);
  pinMode(y2Pin, OUTPUT);
  digitalWrite(y1Pin, LOW);
  digitalWrite(y2Pin, HIGH);

  // X1とX2をアナログ入力にセット
  digitalWrite(x1Pin, LOW);
  digitalWrite(x2Pin, LOW);
  pinMode(x1Pin, INPUT);
  pinMode(x2Pin, INPUT);

  // 各ピンの設定が安定するまで待ってy軸の値を読み取る
  delay(1);
  y = analogRead(ANALOG_PIN_FOR(x1Pin));
}

