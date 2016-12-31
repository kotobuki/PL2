// バッファの長さ
const int BUFFER_LENGTH = 5;

// バッファの中央のインデックス
const int INDEX_OF_MIDDLE = BUFFER_LENGTH / 2;

// バッファ
int buffer[BUFFER_LENGTH];

// バッファにデータを書き込むインデックス
int index = 0;

// センサに接続したアナログピンの番号
const int sensorPin = 0;

void setup() {
  // 結果を出力するためのシリアルをスタート
  Serial.begin(9600);
}

void loop() {
  // センサの値を読み取る
  int raw = analogRead(sensorPin);

  // 読み取った値をバッファに書き込む
  buffer[index] = raw;

  // 次回バッファに書き込む位置を更新
  // バッファの最後まで来たら折り返す
  index = (index + 1) % BUFFER_LENGTH;

  // MeanフィルタとMedianフィルタでそれぞれスムージング
  int smoothedByMeanFilter = smoothByMeanFilter();
  int smoothedByMedianFilter = smoothByMedianFilter();

  // 結果をシリアルで出力
  Serial.print(raw);
  Serial.print("\t");
  Serial.print(smoothedByMeanFilter);
  Serial.print("\t");
  Serial.print(smoothedByMedianFilter);
  Serial.println();
  // 次のループ開始までに100ms待つ
  delay(100);
}

// Meanフィルタによるスムージング
int smoothByMeanFilter() {
  // バッファの値の合計を集計するための変数
  long sum = 0;

  // バッファの値の合計を集計
  for (int i = 0; i < BUFFER_LENGTH; i++) {
    sum += buffer[i];
  }

  // 平均をフィルタの出力結果として返す
  return (int)(sum / BUFFER_LENGTH);
}

// Medianフィルタによるスムージング
int smoothByMedianFilter() {
  // ソートに使用するバッファ
  static int sortBuffer[BUFFER_LENGTH];

  // ソートに使用するバッファにデータをコピー
  for (int i = 0; i < BUFFER_LENGTH; i++) {
    sortBuffer[i] = buffer[i];
  }

  // クイックソートで並び替える
  // 引数はバッファ、要素の数、要素のサイズ、比較用の関数
  qsort(sortBuffer, BUFFER_LENGTH, sizeof(int),
  comparisonFunction);

  // ソート結果の中央の値を出力結果として返す
  return sortBuffer[INDEX_OF_MIDDLE];
}

// クイックソートで使用する比較用の関数
int comparisonFunction(const void *a, const void *b) {
// void型からint型にキャストしてaからbを引いた値を返す
// a < bならマイナスの値、a > bならプラスの値、a == bなら0を返す
return *(int *)a - *(int *)b;
}

