import processing.serial.*;
import cc.arduino.*;

// バッファの長さ
final int bufferLength = 8;

// センサが振られたと判断するための閾値
final int threshold = 80;

// 加速度センサのx軸に接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// Arduino
Arduino arduino;

// バッファ
float[] buffer = new float[bufferLength];

// バッファにデータを書き込むインデックス
int index = 0;

// グラフを表示するためのカウンタ
int count = 0;

void setup() {
  size(400, 200);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(ledPin, Arduino.OUTPUT);

  // 背景を黒で塗りつぶす
  background(0);
}

void draw() {
  // 今回プロットするエリアを黒で塗りつぶす
  stroke(0);
  line(count, 0, count, height - 1);

  // グラフのx軸を描画
  stroke(100);
  line(0, 99, width - 1, 99);
  line(0, 199, width - 1, 199);

  // センサの値を読み取る
  float raw = arduino.analogRead(sensorPin);

  // Meanフィルタでスムージングする
  float smoothed = processSample(raw);

  // 元の値との差を求める
  float diff = abs(raw - smoothed);

  // 元の値を上のグラフにプロット
  stroke(100);
  point(count, map(raw, 0, 1023, 99, 0));

  // スムージングした値を上のグラフにプロット
  stroke(255);
  point(count, map(smoothed, 0, 1023, 99, 0));

  // もし差が閾値よりも大きければ
  if (diff > threshold) {
    // LEDを点灯し描画色を赤に設定
    arduino.digitalWrite(ledPin, Arduino.HIGH);
    stroke(255, 0, 0);
  } else {
    // そうでなければ
    // LEDを消灯し描画色を緑に設定
    arduino.digitalWrite(ledPin, Arduino.LOW);
    stroke(0, 255, 0);
  }

  // 差を下のグラフにプロット
  point(count, map(diff, 0, 1023, 199, 100));

  // グラフ表示用のカウンタを更新
  count = (count + 1) % width;
}

// Meanフィルタ
float processSample(float raw) {
  // バッファに新しいサンプルを書き込んでインデックスを更新
  buffer[index] = raw;
  index = (index + 1) % buffer.length;

  // バッファの値の合計を集計するための変数
  float sum = 0;

  // バッファの値の合計を集計
  for (int i = 0; i < buffer.length; i++) {
    sum += buffer[i];
  }

  // 平均をフィルタの出力結果として返す
  return (sum / buffer.length);
}