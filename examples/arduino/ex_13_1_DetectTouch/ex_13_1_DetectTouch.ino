#include <CapacitiveSensor.h>

// スピーカに接続したピンの番号
const int speakerPin = 8;

// LEDに接続したピンの番号
const int ledPin = 13;

// タッチされたと判断する閾値（上下2 段階）
const long thresholdH = 100;
const long thresholdL = 50;

// 静電容量センサ
// 引数はセンサとして使用する送信側と受信側のピンの番号
CapacitiveSensor capSensor = CapacitiveSensor(2, 3);

// 前回タッチされていたか否か
boolean wasTouched = false;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // 静電容量センサをキャリブレーション
  capSensor.reset_CS_AutoCal();

  // モニタ用のシリアルを開始
  Serial.begin(9600);
}

void loop() {
  // 現在タッチされているかどうかを示すフラグを前回の値で初期化
  boolean isTouched = wasTouched;

  // 静電容量を計測
  long capacitance = capSensor.capacitiveSensor(10);

  // 計測した静電容量をシリアルにプリント
  Serial.print("Capacitance: ");
  Serial.print(capacitance);
  Serial.println();

  // 計測した値が上側の閾値より大きければタッチしていると判断
  if (capacitance > thresholdH) {
    isTouched = true;
  }
  // 計測した値が下側の閾値より大きければタッチしていないと判断
  else if (capacitance < thresholdL) {
    isTouched = false;
  }

  // 前回タッチしていなくて今回タッチしたら
  if (!wasTouched && isTouched) {
    // LEDを点灯してスピーカでクリック音を再生
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 1000, 20);
  }
  // 前回タッチしていて今回タッチしていなければ
  else if (wasTouched && !isTouched) {
    // LEDを消灯
    digitalWrite(ledPin, LOW);
  }

  // 前回タッチしていたか否かを表すフラグを更新
  wasTouched = isTouched;

  // 次回のループ開始までに50ms待つ
  delay(50);
}

