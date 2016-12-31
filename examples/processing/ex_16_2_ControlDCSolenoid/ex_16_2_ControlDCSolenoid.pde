import processing.serial.*;
import cc.arduino.*;

// ソレノイドに通電する時間
final int powerOnDuration = 40;

// センサに接続したピンの番号
final int sensorPin = 0;

// ソレノイドに接続したピンの番号
final int solenoidPin = 9;

// Arduino
Arduino arduino;

// メトロノームを担当するスレッド
MetronomeThread metronome;

// 前回のテンポ
int lastTempo = 0;

void setup() {
  size(400, 400);

  // テキスト表示用のフォントを生成してセット
  PFont font = createFont("Monospaced", 18);
  textFont(font);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  arduino = new Arduino(this, "/dev/cu.usbmodem1234", 57600);

  // ソレノイドに接続したピンのモードを出力にセット
  arduino.pinMode(solenoidPin, Arduino.OUTPUT);

  // メトロノームを担当するスレッドを生成してスタート
  metronome = new MetronomeThread(120);
  metronome.start();
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // センサの値を読み取る
  float sensorReading = arduino.analogRead(sensorPin);

  // 読み取った値を元にテンポをセット（小数点以下は四捨五入）
  int tempo = round(map(sensorReading, 0, 1023, 40, 208));

  // 前回のテンポをセットしてから一定の変化があった時に更新する
  if (abs(tempo - lastTempo) > 2) {
    metronome.setTempo(tempo);
    lastTempo = tempo;
  }

  // 求めたテンポをテキストで表示
  text("Tempo: " + tempo, 10, 20);
}

// escキーを押してスケッチを終了する際に呼ばれる
public void stop() {
  // もしメトロノームスレッドが有効であれば終了を要求
  if (metronome != null) {
    metronome.quitRequested = true;
  }

  // 元々用意されている終了処理を行う
  super.stop();
}

// メトロノームのスレッド
class MetronomeThread extends Thread {
  // 終了が要求されているか否か
  boolean quitRequested = false;

  // ソレノイドをコントロールする間隔
  float interval = 500;

  // コンストラクタ
  MetronomeThread(float defaultTempo) {
    setTempo(defaultTempo);
  }

  // テンポをセットするメソッド
  void setTempo(float newTempo) {
    // 指定されたテンポから間隔を求める
    interval = 1000 / (newTempo / 60);
  }

  // スレッドで実行される処理
  void run() {
    try {
      // 終了が要求されない限り以下を繰り返し実行
      while (!quitRequested) {
        // 現在の時刻を取得
        int now = millis();

        // ソレノイドを駆動
        arduino.digitalWrite(solenoidPin, Arduino.HIGH);
        Thread.sleep(powerOnDuration);
        arduino.digitalWrite(solenoidPin, Arduino.LOW);

        // スリープする時間を求める
        long delay = (long)(interval - (millis() - now));

        // 次の処理を開始するまでスリープする
        Thread.sleep(delay);
      }
    }
    // 例外が発生した時には以下を実行
    catch(InterruptedException e) {
      println("Interrupted Exception occurred");
    }
  }
}