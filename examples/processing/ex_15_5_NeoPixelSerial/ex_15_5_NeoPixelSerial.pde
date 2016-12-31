import processing.serial.*;

// 色相のステップ数
final int stepsOfHue = 24;

// 彩度のステップ数
final int stepsOfSaturation = 10;

// シリアルポート
Serial serialPort;

void setup() {
  size(400, 400);

  // Arduino IDEで選択したシリアルポートの名前に変更
  // Windowsの例：COM3
  // MacOSの例：/dev/cu.usbmodem1234
  serialPort 
    = new Serial(this, "/dev/cu.usbmodem1234", 9600);

  // カラーモードをHSBにセット
  colorMode(HSB, 360, 100, 100);

  // 描画モードをセット
  noStroke();
  smooth();
}

void draw() {
  // 背景を黒で塗りつぶす
  background(0);

  // 色相環を描画する
  for (int i = 0; i < stepsOfHue; i++) {
    // 360度をステップ数で分割して色相を決定
    float hue = ((float)i / (float)stepsOfHue) * 360;

    for (int j = 0; j < stepsOfSaturation; j++) {
      // 100をステップ数で分割して彩度を決定
      float satulation 
        = (1 - ((float)j / (float)stepsOfSaturation)) * 100;

      // 決定した色相と彩度で描画色をセット（明度は100で固定）
      float start = TWO_PI * ((float)i / (float)stepsOfHue);
      float stop 
        = TWO_PI * ((float)(i + 1) / (float)stepsOfHue);
      fill(hue, satulation, 100);

      // 彩度のステップに応じて円弧の直径を決定し、円弧を描画
      float diameter 
        = (1 - ((float)j / (float)stepsOfSaturation)) * 380 + 20;
      arc(200, 200, diameter, diameter, start, stop, PIE);
    }
  }

  // 中心に彩度0の円を描画
  fill(0, 0, 100);
  arc(200, 200, 20, 20, 0, TWO_PI, PIE);
}

// マウスポインタの位置が変化したら
void mouseMoved() {
  // マウスポインタの位置の色を読み取る
  color c = get(mouseX, mouseY);

  // Hue（色相）、Saturation（彩度）、Brightness（明度）の順に
  // シリアルにプリント
  serialPort.write(round(hue(c)) + ",");
  serialPort.write(round(saturation(c)) + ",");
  serialPort.write(round(brightness(c)) + "\n");
}