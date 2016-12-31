import processing.serial.*;
import cc.arduino.*;

// 加速度センサのx軸とy軸に接続したアナログピンの番号
final int xAxisPin = 0;
final int yAxisPin = 1;

// 加速度センサの前回の値と今回の値をミックスする比率
// 前回の値は使用せず今回の値のみを使用するのであれば1.0に設定
final float ratio = 0.5;

// Arduino
Arduino arduino;

// 前回のx軸とy軸の値（初期値は0〜1023の中央値）
float xAxisValueLast = 511;
float yAxisValueLast = 511;

void setup() {
  size(400, 400, P3D);
  frameRate(30);
  noStroke();
  colorMode(RGB, 1);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);
}

void draw() {
  background(0.5);

  pushMatrix();

  translate(width / 2, height / 2, -30);

  // x軸とy軸の値を読み取る
  float xAxisValue = arduino.analogRead(xAxisPin);
  float yAxisValue = arduino.analogRead(yAxisPin);

  // 前回の値と今回の値の割合を変えてスムージングする
  // 前回の値の割合を大きくすると、滑らかになる代わりに変化が遅くなり
  // 今回の値の割合を大きくすると、ノイズを拾いやすくなる代わりに変化が早くなる
  float xAxisValueSmoothed 
    = xAxisValue * ratio + xAxisValueLast * (1.0 - ratio);
  float yAxisValueSmoothed 
    = yAxisValue * ratio + yAxisValueLast * (1.0 - ratio);

  // 前回の値としてスムージングした値をセット
  xAxisValueLast = xAxisValueSmoothed;
  yAxisValueLast = yAxisValueSmoothed;

  // 読み取った値を-1から1までの範囲にスケーリングしてsinθの値とする
  float xAxisSinTheta 
    = map(xAxisValueSmoothed, 306, 716, -1, 1);
  float yAxisSinTheta 
    = map(yAxisValueSmoothed, 306, 716, -1, 1);

  // それぞれの値を-1から1までの範囲に制限する
  xAxisSinTheta = constrain(xAxisSinTheta, -1, 1);
  yAxisSinTheta = constrain(yAxisSinTheta, -1, 1);

  // マウスの代わりに加速度センサの値でコントロール
  rotateZ(asin(xAxisSinTheta));
  rotateX(-asin(yAxisSinTheta));

  scale(100);

  beginShape(QUADS);

  fill(0, 1, 1); 
  vertex(-1, 1, 1);
  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);

  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);

  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(0, 0, 0); 
  vertex(-1, -1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);

  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(0, 1, 1); 
  vertex(-1, 1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);
  fill(0, 0, 0); 
  vertex(-1, -1, -1);

  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(0, 1, 1); 
  vertex(-1, 1, 1);

  fill(0, 0, 0); 
  vertex(-1, -1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);

  endShape();
  popMatrix();
}