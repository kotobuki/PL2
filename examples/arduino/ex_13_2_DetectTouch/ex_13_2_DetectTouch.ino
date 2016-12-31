// センサに接続したピンの番号
const int sensorPin = 2;

// スピーカに接続したピンの番号
const int speakerPin = 8;

// LEDに接続したピンの番号
const int ledPin = 13;

// 前回タッチされていたか否か
boolean wasTouched = false;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // センサに接続したピンの状態を読み取ってタッチされているか否かを判断
  boolean isTouched = (digitalRead(sensorPin) == HIGH);

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

