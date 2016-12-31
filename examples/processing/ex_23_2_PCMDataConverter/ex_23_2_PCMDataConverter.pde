// dataフォルダからPCMData.rawを読み込む
byte pcmData[] = loadBytes("PCMData.raw");

// ヘッダファイルの最初の定義部分を生成
String header = "";
header += "const int SOUNDDATA_LENGTH = " + pcmData.length;
header += ";\n\n";
header += "const unsigned char soundData[] PROGMEM = {\n";
header += " ";

// pcmData配列の中身を1 バイトごとにカンマで区切って追加
for (int i = 0; i < pcmData.length; i++) {
  header += pcmData[i] + ", ";
  // 16バイトごとに改行する
  if (i % 16 == 15) {
    header += "\n";
    header += " ";
  }
}

// ヘッダファイルの最後の部分を生成
header += "\n";
header += "};\n";

// 文字列headerをPCMData.hという名前で保存
saveBytes("PCMData.h", header.getBytes());

