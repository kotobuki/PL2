import processing.serial.*;
import cc.arduino.*;
import beads.*;

// オカリナの穴の代わりのスイッチの状態とデジタル入力の状態の対応
final int OPENED = 0;
final int CLOSED = 1;

// 指使いとパターンの対応表
final int[][] fingeringTable = {
  { CLOSED, CLOSED, CLOSED, CLOSED }, 
  { CLOSED, OPENED, CLOSED, CLOSED }, 
  { CLOSED, CLOSED, CLOSED, OPENED }, 
  { CLOSED, OPENED, CLOSED, OPENED }, 
  { OPENED, OPENED, CLOSED, CLOSED }, 
  { OPENED, OPENED, CLOSED, OPENED }, 
  { OPENED, CLOSED, OPENED, OPENED }, 
  { OPENED, OPENED, OPENED, OPENED }
};

// パターンが見つからなかった時を表す値
final int NOT_FOUND = -1;

// パターンと周波数の対応
final float[] frequency = {
  261.6, // C4
  293.7, // D4
  329.6, // E4
  349.2, // F4
  392.0, // G4
  440.0, // A4
  493.9, // B4
  523.3  // C5
};

// パターンに対応した音名
final String[] noteName = {
  "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5"
};

// タクトスイッチに接続したピンの番号を納める配列
final int[] buttonPins = {2, 3, 4, 5};

// 感圧センサに接続したアナログピンの番号
final int sensorPin = 0;

// Arduino
Arduino arduino;

// タクトスイッチごとの現在の状態を収める配列
int[] buttonState = {
  OPENED, OPENED, OPENED, OPENED
};

// Beadsを使用したプロジェクトでオーディオを使用するためのコア
AudioContext ac;

// 周波数と振幅のコントローラ
Envelope freqController;
Envelope gainController;

void setup() {
  size(400, 400);

  // テキスト表示に使用するフォントを生成
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // タクトスイッチに接続したピンのモードを入力にセット
  for (int i = 0; i < buttonPins.length; i++) {
    arduino.pinMode(buttonPins[i], Arduino.INPUT);
  }

  // オーディオを使用するためのコア
  ac = new AudioContext();

  // 周波数を振幅のコントローラに初期値をセット
  freqController = new Envelope(ac, 0.0);
  gainController = new Envelope(ac, 0.0);

  // サイン波を生成するオブジェクトを生成
  WavePlayer wp 
    = new WavePlayer(ac, freqController, Buffer.SINE);

  // 出力に関するオブジェクトを生成してコアにセットし、スタート
  Gain g = new Gain(ac, 1, gainController);
  g.addInput(wp);
  ac.out.addInput(g);
  ac.start();
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // タクトスイッチの状態を読み取る
  for (int i = 0; i < buttonPins.length; i++) {
    if (arduino.digitalRead(buttonPins[i]) == Arduino.LOW) {
      buttonState[i] = OPENED;
    } else {
      buttonState[i] = CLOSED;
    }
  }

  // 現在のスイッチの状態に対応したパターンを検索
  int index = findPattern(buttonState);

  // 検索した結果を表示
  if (index != NOT_FOUND) {
    text("Index: " + noteName[index], 10, 20);
  } else {
    text("Index: Not found", 10, 20);
  }

  // パターンが見つかったら
  if (index != NOT_FOUND) {
    // パターンに対応した周波数まで20msで変化するようセット
    freqController.clear();
    freqController.addSegment(frequency[index], 20);
  }

  // 感圧センサの状態を読み取る
  int pressure = arduino.analogRead(sensorPin);

  // 読み取った値に応じた音量まで10msで変化するようセット
  gainController.clear();
  gainController.addSegment(
    map(pressure, 0, 1023, 0, 1), 10);
}

// パターンを検索
int findPattern(int state[]) {
  // 指使いのテーブルと与えられたパターンを順次比較
  for (int i = 0; i < fingeringTable.length; i++) {
    // 一致するパターンが見つかったら
    if (java.util.Arrays.equals(state, fingeringTable[i])) {
      // 現在のインデックスを返す
      return i;
    }
  }

  // 最後まで見つからなかったらNOT_FOUNDを返す
  return NOT_FOUND;
}