// 測距センサのクラス
class MaxSonar {
  public:
    // pin: センサに接続したアナログピンの番号
    // threshold: 障害物有と判断する閾値（単位はインチ）
    MaxSonar(int pin, int threshold) {
      _pin = pin;
      _threshold = threshold;
      _distance = 0;
    }

    // 距離を読み取る
    void read() {
      int reading = analogRead(_pin);
      _distance = reading / 2;
    }

    // 距離（単位はインチ）
    int distance() {
      return _distance;
    }

    // 障害物が無いか否か
    boolean isClear() {
      if (_distance > _threshold) {
        return true;
      } else {
        return false;
      }
    }

  private:
    int _pin;
    int _distance;
    int _threshold;
};

