// 独立したPWMピンを用いるTB6612FNGの場合にはtrueにする
// 独立したPWMピンを用いないTA7291Pの場合にはfalseにする
const boolean useSeparatePWMPin = true;

// モータドライバのIN1、IN2、PWMに接続したピンの番号
const int in1Pin = 9;
const int in2Pin = 10;
const int pwmPin = 11;

void setup() {
  // IN1、IN2、PWMの各ピンのモードを出力にセット
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  // 確認用のシリアル出力をスタート
  Serial.begin(9600);
}

void loop() {
  // 500ms間順方向に回転
  forward(255);
  Serial.println("Forward");
  delay(500);

  // 回転を停止（ブレーキあり）して1000ms待つ
  despin(true);
  Serial.println("Despin (with brake)");
  delay(1000);

  // 500ms間逆方向に回転
  reverse(255);
  Serial.println("Reverse");
  delay(500);

  // 回転を停止（ブレーキなし）して1000ms待つ
  despin(false);
  Serial.println("Despin (without brake)");
  delay(1000);
}

// 順方向に回転
void forward(int value) {
  if (useSeparatePWMPin) {
    // 独立したPWMピンを用いる場合
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(pwmPin, value);
  }
  else {
    // 独立したPWMピンを用いない場合
    analogWrite(in1Pin, value);
    analogWrite(in2Pin, 0);
  }
}

// 逆方向に回転
void reverse(int value) {
  if (useSeparatePWMPin) {
    // 独立したPWMピンを用いる場合
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(pwmPin, value);
  }
  else {
    // 独立したPWMピンを用いない場合
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, value);
  }
}

// 回転を停止
void despin(boolean useBrake) {
  if (useBrake) {
    // ブレーキを使用して停止
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
    if (useSeparatePWMPin) {
      analogWrite(pwmPin, 255);
    }
  }
  else {
    // ブレーキを使用しないで停止
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    if (useSeparatePWMPin) {
      analogWrite(pwmPin, 0);
    }
  }
}

