import processing.serial.*;
import cc.arduino.*;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// バッファの長さ
final int bufferLength = 5;

// バッファの中央のインデックス
final int indexOfMiddle = bufferLength / 2;

// Arduino
Arduino arduino;

// センサから読み取った値を保持するためのバッファ
float[] buffer = new float[bufferLength];

// ソート用のバッファ
float[] sortBuffer = new float[bufferLength];

// バッファにデータを書き込むインデックス
int index = 0;

// 表示位置のカウンタ
int count = 0;

void setup() {
  size(400, 300);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // 背景を黒で塗りつぶす
  background(0);
}

void draw() {
  // これから描画する部分を黒で塗りつぶす
  stroke(0);
  line(count, 0, count, height - 1);

  // 3 つのグラフのx軸を描画する
  stroke(100);
  line(0, 99, width - 1, 99);
  line(0, 199, width - 1, 199);
  line(0, 299, width - 1, 299);

  // センサの値を読み取った値をバッファに書き込む
  buffer[index] = arduino.analogRead(sensorPin);

  // MeanフィルタとMedianフィルタをそれぞれ実行
  float smoothedByMean = smoothByMeanFilter();
  float smoothedByMedian = smoothByMedianFilter();

  // 元の値、Meanフィルタをかけた値、Medianフィルタをかけた値を表示
  stroke(255);
  point(count, map(buffer[index], 0, 1023, 99, 0));
  point(count, map(smoothedByMean, 0, 1023, 199, 100));
  point(count, map(smoothedByMedian, 0, 1023, 299, 200));

  // バッファの書き込み位置を示すカウンタをインクリメント
  index = (index + 1) % buffer.length;

  // 表示用のカウンタをインクリメント（画面の端まで来たら折り返す）
  count = (count + 1) % width;
}

// Meanフィルタ
float smoothByMeanFilter() {
  // バッファの値の合計を集計するための変数
  float sum = 0;

  // バッファの値の合計を集計
  for (int i = 0; i < buffer.length; i++) {
    sum += buffer[i];
  }

  // 平均をフィルタの出力結果として返す
  return (sum / buffer.length);
}

// Medianフィルタ
float smoothByMedianFilter() {
  // ソートに使用するバッファにデータをコピー
  for (int i = 0; i < sortBuffer.length; i++) {
    sortBuffer[i] = buffer[i];
  }

  // ソート
  sort(sortBuffer);

  // ソート結果の中央の値を出力結果として返す
  return sortBuffer[indexOfMiddle];
}