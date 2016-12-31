import processing.serial.*;
import cc.arduino.*;

// 各状態を表す定数
final int UNKNOWN = 0;
final int BRIGHT = 1;
final int DARK = 2;

// それぞれの状態に対応した文字列
final String[] stateName = { "UNKNOWN", "BRIGHT", "DARK" };

// 状態が変化してから確定するまでに待機する時間
final int timeToWait = 1000;

// 明るいと判断する閾（しきい）値
final int thresholdH = 700;

// 暗いと判断する閾（しきい）値
final int thresholdL = 300;

// センサに接続したアナログピンの番号
final int sensorPin = 0;

// LEDに接続したピンの番号
final int ledPin = 9;

// Arduino
Arduino arduino;

// 現在と次に移行する状態
int state = UNKNOWN;
int nextState = UNKNOWN;

// 最後に変化があった時刻
int lastChange = 0;

// 前回のセンサの状態
int lastSensorState = UNKNOWN;

void setup() {
  size(400, 400);

  // テキスト表示用のフォントを生成してセット
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // LEDに接続したピンのモードを出力にセット
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

void draw() {
  // 現在の時刻を取得する
  int now = millis();

  // センサから現在の明るさを読み取る
  int brightness = arduino.analogRead(sensorPin);

  // 現在のセンサの状態を表す変数の初期に前回のセンサの状態を代入
  int sensorState = lastSensorState;

  // 読み取った値と閾値を比較して現在のセンサの状態をセット
  if (brightness > thresholdH) {
    sensorState = BRIGHT;
  }
  else if (brightness < thresholdL) {
    sensorState = DARK;
  }

  // 前回のセンサの状態と現在のセンサの状態が異なれば
  if (lastSensorState != sensorState) {
    // BRIGHT以外からBRIGHTに変化したら
    if (sensorState == BRIGHT) {
      // 次に移行する状態をBRIGHTにセットして変化のあった時刻をリセット
      nextState = BRIGHT;
      lastChange = now;
    }
    // DARK以外からDARKに変化したら
    else if (sensorState == DARK) {
      // 次に移行する状態をDARKにセットして変化のあった時刻をリセット
      nextState = DARK;
      lastChange = now;
    }
  }

  // 前回のセンサの状態として今回の値をセット
  lastSensorState = sensorState;

  // 前回変化があった時刻からの経過時間を求める
  int elapsedTime = now - lastChange;

  // 現在の状態と次に移行する状態が異なり、
  // 変化してから一定の時間が経過していたら
  if ((state != nextState) && (elapsedTime > timeToWait)) {
    // 次の状態がBRIGHTであれば
    if (nextState == BRIGHT) {
      // LEDを消灯してBRIGHTに移行
      arduino.digitalWrite(ledPin, Arduino.LOW);
    }
    // 次の状態がDARKであれば
    else if (nextState == DARK) {
      // LEDを点灯してDARKに移行
      arduino.digitalWrite(ledPin, Arduino.HIGH);
    }
    // 現在の状態を更新
    state = nextState;
  }

  // 現在の明るさ、現在の状態、次に移行する状態、経過時間を表示
  background(0);
  text("Brightness: " + brightness, 10, 20);
  text("State: " + stateName[state], 10, 40);
  text("Next state: " + stateName[nextState], 10, 60);
  text("Elapsed time: " + elapsedTime, 10, 80);
}