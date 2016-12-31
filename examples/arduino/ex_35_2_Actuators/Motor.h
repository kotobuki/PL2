// モータをコントロールするためのクラス
class Motor {
  public:
    // in1Pin: IN1に接続したピンの番号
    // in2Pin: IN2に接続したピンの番号
    Motor(int in1Pin, int in2Pin) {
      _in1Pin = in1Pin;
      _in2Pin = in2Pin;
      pinMode(_in1Pin, OUTPUT);
      pinMode(_in2Pin, OUTPUT);
    }

    // 順方向に回転
    void forward(int value) {
      analogWrite(_in1Pin, value);
      analogWrite(_in2Pin, 0);
    }

    // 逆方向に回転
    void reverse(int value) {
      analogWrite(_in1Pin, 0);
      analogWrite(_in2Pin, value);
    }

    // 回転を停止（ブレーキあり／なし）
    void despin(boolean withBrake) {
      if (withBrake) {
        // ブレーキを使用して停止
        digitalWrite(_in1Pin, HIGH);
        digitalWrite(_in2Pin, HIGH);
      }
      else {
        // ブレーキを使用しないで停止
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, LOW);
      }
    }

  private:
    int _in1Pin;
    int _in2Pin;
};

