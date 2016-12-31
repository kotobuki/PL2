import processing.serial.*;

// ラインフィードのキャラクターコード
final int LF = 10;

// シリアルポート
Serial serialPort;

// 方位角
int heading = 0;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  serialPort 
    = new Serial(this, "/dev/cu.usbmodem1234", 9600);

  // シリアルポートからすでに受信しているデータがあればクリア
  serialPort.clear();

  // LFを受け取った時にserialEventが呼ばれるようにセット
  serialPort.bufferUntil(LF);

  // 以降の描画をすべてスムーズにする
  smooth();
}

void draw() {
  // 背景を白で塗りつぶす
  background(255);

  // 描画の中心をウィンドウの中央に移動
  translate(width / 2, height / 2);

  // 現在の描画マトリクスを保存した後
  // コンパスの方位にあわせて回転
  pushMatrix();
  rotate(radians(heading));

  // コンパスの針を描画するためのパラメータをセット
  stroke(0);
  fill(0);
  strokeWeight(1);

  // コンパスの針を描画
  beginShape();
  vertex(0, -100);
  vertex(20, 20);
  vertex(0, 0);
  vertex(-20, 20);
  vertex(0, -100);
  endShape(CLOSE);

  // 描画マトリクスを元に戻す
  popMatrix();

  // コンパスの周囲の円を描画
  noFill();
  strokeWeight(2);
  ellipse(0, 0, 200, 200);
}

// Serial.bufferUntil()でセットした文字を受け取ると呼ばれる
void serialEvent(Serial port) {
  // シリアルポートから受信済みのメッセージを読み出す
  String message = port.readString();

  // メッセージが空であれば以下の処理を行わずにリターン
  if (message == null) {
    return;
  }

  // 受け取った文字列を整数値として解析する
  int value = Integer.parseInt(trim(message));

  // 整数値として解析した値が範囲外であれば以下の処理を行わずにリターン  
  if ((value < 0) || (360 < value)) {
    return;
  }

  // 受け取った値で方位角を更新
  heading = value;
}