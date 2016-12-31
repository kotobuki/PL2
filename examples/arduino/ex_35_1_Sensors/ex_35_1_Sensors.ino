#include "MaxSonar.h"

// 前後の測距センサ
MaxSonar sensorF = MaxSonar(A0, 12);
MaxSonar sensorR = MaxSonar(A1, 12);

// 1つめの測距センサのRXピンに接続したピンの番号
const int rxPin = A2;

void setup() {
  Serial.begin(9600);

  // 1つめの測距センサのRXピンに接続したピンのモードを出力にセット
  pinMode(rxPin, OUTPUT);
  digitalWrite(rxPin, LOW);
}

void loop() {
  // 1つめの測距センサのRXピンを1msだけHIGHにセットして計測を開始
  digitalWrite(rxPin, HIGH);
  delay(1);
  digitalWrite(rxPin, LOW);

  // 1つのセンサあたりの計測にかかる時間が49msなので2つ分だけ待つ
  delay(98);

  // 前後の測距センサの値を計測する
  sensorF.read();
  sensorR.read();

  // 前方の状態をシリアルにプリント
  if (sensorF.isClear() && sensorR.isClear()) {
    // もし前後の両方がクリアであれば、前後共クリア
    Serial.print("Clear (");
  } else if (!sensorF.isClear() && sensorR.isClear()) {
    // もし前だけがクリアであれば、前方はクリア
    Serial.print("Front is clear (");
  } else if (sensorF.isClear() && !sensorR.isClear()) {
    // もし後だけがクリアであれば、後方はクリア
    Serial.print("Rear is clear (");
  } else {
    // もし前後の両方ともクリアでなければ、塞がっている
    Serial.print("Not clear (");
  }

  // 前後のセンサで計測した距離をプリント
  Serial.print("F = ");
  Serial.print(sensorF.distance());
  Serial.print("\", R = ");
  Serial.print(sensorR.distance());
  Serial.println("\")");
}

