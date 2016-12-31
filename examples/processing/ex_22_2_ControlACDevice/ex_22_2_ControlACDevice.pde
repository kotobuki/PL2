import processing.serial.*;
import cc.arduino.*;

// SSRに接続したピンの番号
final int ssrPin = 9;

// Arduino
Arduino arduino;

// 最後に状態を変更した時刻
int lastChange = 0;

// 現在の状態
int state = 0;

void setup() {
  size(200, 200);

  // テキスト表示用のフォントを生成してセット
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // SSRに接続したピンのモードを出力にセット
  arduino.pinMode(ssrPin, Arduino.OUTPUT);

  // 背景を黒で塗りつぶす
  background(0);
}

void draw() {
  // 現在の時刻を取得
  int now = millis();

  // 前回状態を変更してから1000ms経過していたら以下を実行
  if ((now - lastChange) > 1000) {
    if (state == 0) {
      // もし現在の状態が0であればSSRをオンにして現在の状態を1に
      arduino.digitalWrite(ssrPin, Arduino.HIGH);
      background(0);
      text("ON", 10, 20);
      state = 1;
    } else {
      // もし現在の状態が1であればSSRをオフにして現在の状態を0に
      arduino.digitalWrite(ssrPin, Arduino.LOW);
      background(0);
      text("OFF", 10, 20);
      state = 0;
    }

    // 前回状態を変更した時刻を更新
    lastChange = now;
  }
}