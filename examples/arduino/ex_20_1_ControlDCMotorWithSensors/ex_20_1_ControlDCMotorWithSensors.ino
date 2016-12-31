// モータドライバのIN1、IN2、PWMに接続したピンの番号
const int in1Pin = 9;
const int in2Pin = 10;
const int pwmPin = 11;

// 左右のセンサに接続したアナログピンの番号
const int leftSensorPin = 0;
const int rightSensorPin = 1;

// センサを遮ったと判断するための閾値
const int THRESHOLD = 300;

// DCモータの回転開始からのタイムアウト
const unsigned int TIMEOUT = 1000;

void setup() {
  // IN1、IN2、PWMに接続したピンのモードを出力にセット
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  // 動作確認用のシリアルを開始
  Serial.begin(9600);
}

void loop() {
  // 左端まで移動
  Serial.println("Left");
  left();

  // 1000ms待機
  delay(1000);

  // 右端まで移動
  Serial.println("Right");
  right();

  // 1000ms待機
  delay(1000);
}

// 順方向に回転
void forward(int value) {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(pwmPin, value);
}

// 逆方向に回転
void reverse(int value) {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(pwmPin, value);
}

// 回転を停止（ブレーキあり／なし）
void despin(boolean useBrake) {
  if (useBrake) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
    analogWrite(pwmPin, 255);
  }
  else {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(pwmPin, 0);
  }
}

// ラックギアを回転させて左端まで移動
void left() {
  // 順方向にゆっくり回転
  forward(80);

  // 現在の時刻を取得
  unsigned int start = millis();

  // 移動方向の反対側のセンサの値が閾値に到達するまで待つ
  while (analogRead(rightSensorPin) > THRESHOLD) {
    delay(1);

    // タイムアウトに達したら中止
    if ((millis() - start) > TIMEOUT) {
      break;
    }
  }

  // 回転を停止（ブレーキあり）
  despin(true);
}

// ラックギアを回転させて右端まで移動
void right() {
  // 逆方向にゆっくり回転
  reverse(80);

  // 現在の時刻を取得
  unsigned int start = millis();

  // 移動方向の反対側のセンサの値が閾値に到達するまで待つ
  while (analogRead(leftSensorPin) > THRESHOLD) {
    delay(1);

    // タイムアウトに達したら中止
    if ((millis() - start) > TIMEOUT) {
      break;
    }
  }
  // 回転を停止（ブレーキあり）
  despin(false);
}

