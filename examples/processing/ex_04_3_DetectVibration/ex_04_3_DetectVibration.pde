import processing.serial.*;

// ラインフィードのASCIIコード
final int LF = 10;

// シリアルポート
Serial serialPort;

// 明るさ
float brightness = 0;

void setup() {
  size(400, 200);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  serialPort 
    = new Serial(this, "/dev/cu.usbmodem1234", 9600);

  // シリアルポートからすでに受信しているデータがあればクリア
  serialPort.clear();

  // LFを受け取った時にserialEventが呼ばれるようにセット
  serialPort.bufferUntil(LF);
}

void draw() {
  // 現在の明るさで背景を塗りつぶす
  background(brightness);

  // 明るさを一定の割合で減衰させる
  brightness = brightness * 0.9;
}

// Serial.bufferUntil()でセットした文字を受け取ると呼ばれる
void serialEvent(Serial port) {
  // シリアルポートから受信済みのメッセージを読み出す
  String message = port.readString();

  // メッセージが空であれば以下の処理を行わずにリターン
  if (message == null) {
    return;
  }

  // メッセージが文字列"T"＋CR＋LFであれば
  if (message.equals("T\r\n")) {
    // 明るさを最大にセット
    brightness = 255;
  }
}