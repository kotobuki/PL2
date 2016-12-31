import processing.serial.*;
import cc.arduino.*;
import processing.sound.*;

// タッチセンサに接続したピンの番号
final int sensorPin = 2;

// Arduino
Arduino arduino;

// サイン波のオシレータ
SinOsc sinOsc;

// エンベロープジェネレータ
Env env;

// 前回タッチしていたか否か
boolean wasTouched = true;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // センサに接続したピンのモードを入力にセット
  arduino.pinMode(sensorPin, Arduino.INPUT);

  // サイン波のオシレータを生成して周波数を1000Hzにセット
  sinOsc = new SinOsc(this);
  sinOsc.freq(1000);

  // エンベロープジェネレータを生成
  env = new Env(this);
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // センサの値を読み取る
  boolean isTouched 
    = (arduino.digitalRead(sensorPin) == Arduino.HIGH);

  // 前回タッチされていなくて今回タッチされたら
  if (!wasTouched && isTouched) {
    // サイン波のオシレータをトリガ
    sinOsc.play();

    // エンベロープをセットしてジェネレータをトリガ
    // パラメータはアタックタイム、サステインタイム、サステインレベル、ディケイタイム
    env.play(sinOsc, 0.001, 0.1, 1.0, 0.001);
  }

  // 前回の状態を表す変数を今回の値で更新
  wasTouched = isTouched;
}