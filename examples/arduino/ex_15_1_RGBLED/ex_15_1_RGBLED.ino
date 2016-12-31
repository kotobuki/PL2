// LEDのドライブ方法に関する定数
const int commonKathode = 0;
const int commonAnode = 1;

// R、G、BそれぞれのLEDに接続したピンの番号
const int rLEDPin = 9;
const int gLEDPin = 10;
const int bLEDPin = 11;

// R、G、Bそれぞれをコントロールする可変抵抗器に接続したアナログピンの番号
const int rPotPin = 0;
const int gPotPin = 1;
const int bPotPin = 2;

// LEDのドライブモード：アノードコモンの場合にはここをcommonAnodeに変更する
int driveMode = commonKathode;

void setup() {
  // R、G、BそれぞれのLEDに接続したピンのモードを出力にセット
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
}

void loop() {
  // R、G、Bそれぞれをコントロールする可変抵抗器の値を読み取る
  int rPotValue = analogRead(rPotPin);
  int gPotValue = analogRead(gPotPin);
  int bPotValue = analogRead(bPotPin);

  // ドライブモードがカソードコモンであれば
  // 0～1023までの入力を0～255にスケーリング
  if (driveMode == commonKathode) {
    analogWrite(rLEDPin, map(rPotValue, 0, 1023, 0, 255));
    analogWrite(gLEDPin, map(gPotValue, 0, 1023, 0, 255));
    analogWrite(bLEDPin, map(bPotValue, 0, 1023, 0, 255));
  }
  // ドライブモードがアノードコモンであれば
  // 0～1023までの入力を255～0にスケーリング
  else if (driveMode == commonAnode) {
    analogWrite(rLEDPin, map(rPotValue, 0, 1023, 255, 0));
    analogWrite(gLEDPin, map(gPotValue, 0, 1023, 255, 0));
    analogWrite(bLEDPin, map(bPotValue, 0, 1023, 255, 0));
  }
}

