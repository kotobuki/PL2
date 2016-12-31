// ソレノイドに接続したデジタルピンの番号
const int solenoidPin = 9;

// 可変抵抗器に接続したアナログピンの番号
const int sensorPin = 0;

// ソレノイドに通電する時間
const unsigned long powerOnDuration = 20;

void setup() {
  // ソレノイドに接続したピンのモードを出力にセット
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  // センサの値を読み取る
  int sensorReading = analogRead(sensorPin);

  // 読み取った値を40～208BPMまでのテンポに変換
  int tempo = map(sensorReading, 0, 1023, 40, 208);

  // テンポからms単位での間隔を求める
  // ここで60000の後にulを付けているのはunsigned longであることを
  // 示すため。Arduino言語ではデフォルトがintになるため、何も付けないと
  // intで表現できる範囲を超えてしまい、計算結果が異常な値になってしまう。
  // 本来の計算式は1000 / (tempo / 60)であるが、ここでは一度で計算
  // できるように約分したものを計算式としている
  unsigned long interval = 60000ul / tempo;

  // powerOnDurationの間だけソレノイドに通電する
  digitalWrite(solenoidPin, HIGH);
  delay(powerOnDuration);
  digitalWrite(solenoidPin, LOW);

  // テンポから求めた間隔から通電した時間を除いた時間だけ待つ
  delay(interval - powerOnDuration);
}

