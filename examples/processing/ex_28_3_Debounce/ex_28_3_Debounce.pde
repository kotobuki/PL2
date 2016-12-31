import processing.serial.*;
import cc.arduino.*;

// チャタリング除去を行う時間
final int debounceDelay = 50;

// ボタンに接続したピンの番号
final int buttonPin = 8;

// Arduino
Arduino arduino;

// 前回のボタンの状態
int lastButtonState = Arduino.LOW;

// 前回チャタリング除去を行った時間
int lastDebounceTime = 0;

// ボタンが押されたカウント
int count = 0;

void setup() {
  size(400, 400);

  // フレームレートを60Hz（1フレームあたり16.666ms）に設定
  frameRate(60);

  // テキスト表示で使用するフォントを生成して読み込む
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // ボタンに接続したピンのモードを入力にセット
  arduino.pinMode(buttonPin, Arduino.INPUT);
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // ボタンを接続したピンの状態を読み取る
  int buttonState = arduino.digitalRead(buttonPin);

  // 前回がLOWで今回がHIGHであれば以下を実行
  if (lastButtonState == Arduino.LOW 
    && buttonState == Arduino.HIGH) {
    // 現在の時刻
    int now = millis();

    // 前回デバウンスを行ってから一定時間が経過していれば
    if ((now - lastDebounceTime) > debounceDelay) {
      // カウントを1だけ増やす
      count = count + 1;
    }

    // 前回デバウンスを行った時間として現在の時刻をセット
    lastDebounceTime = now;
  }

  // 前回の状態として現在の状態をセット
  lastButtonState = buttonState;

  // 現在のカウントを表示する
  text("Count: " + count, 10, 20);
}