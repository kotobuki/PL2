#include <WaveHC.h>

// ボタンに接続したピンの番号（A0は14に対応する）
const int buttonPin = A0;

// SDカードのリーダ
SdReader cardReader;

// ボリューム（パーティション）
FatVolume volume;

// ルートディレクトリ
FatReader root;

// ファイルのプレーヤ（1 個のみ使用）
WaveHC waveFile;

// 前回のボタンの状態
int lastButtonState = LOW;

// 致命的なエラーをシリアルにレポートして動作を停止
void reportFatalError(const char *message) {
  Serial.print("ERROR: ");
  Serial.println(message);
  while(1);
}

void setup() {
  // ボタンを接続したピンのモードを入力にセット
  pinMode(buttonPin, INPUT);

  // シリアルモニタで動作を確認するためのシリアル通信を開始
  Serial.begin(9600);

  // カードリーダを初期化
  if (!cardReader.init()) {
    reportFatalError("Can't init the card");
  }

  // FATパーティションを検索
  int partition = 0;
  for (partition = 0; partition < 5; partition++) {
    if (volume.init(cardReader, partition)) {
      break;
    }
  }

  // もしFATパーティションが見つからなければエラーをレポート
  if (partition == 5) {
    reportFatalError("Can't find a valid FAT partition");
  }

  // ボリュームのルートディレクトリをオープン
  if (!root.openRoot(volume)) {
    reportFatalError("Can't open the root");
  }
}

void loop() {
  // 現在のボタンの状態を読み取る
  int buttonState = digitalRead(buttonPin);

  // 前回の状態がLOWで現在の状態がHIGHであればonPress()を実行
  if (lastButtonState == LOW && buttonState == HIGH) {
    onPress();
  }

  // 前回の状態として現在の状態をセット
  lastButtonState = buttonState;

  // 次のループ開始まで10ms待つ
  delay(10);
}

// ボタンが押されたら以下を実行
void onPress() {
  // 再生するファイル
  FatReader file;

  // ルートディレクトリにあるファイルを名前指定でオープン
  if (!file.open(root, "TEST.WAV")) {
    Serial.println("ERROR: Can't open the file to play");
  }

  // プレーヤにファイルをセット
  if (!waveFile.create(file)) {
    Serial.println("ERROR: Not a valid WAV file");
  }

  // 再生開始
  waveFile.play();

  // 再生が終了するまで待つ
  while (waveFile.isplaying) {
    // 再生中であれば10ms待って再度状態をチェックする
    delay(10);
  }

  // 再生用にオープンしたファイルをクローズ
  file.close();
}

