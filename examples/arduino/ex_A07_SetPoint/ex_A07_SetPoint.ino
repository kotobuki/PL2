#include "SetPoint.h"

// 閾値
int threshold = 511;

// ヒステリシス
int hysteresis = 102;

// 光センサに接続したアナログピンの番号
int sensorPin = 0;

// LEDに接続したピンの番号
int ledPin = 13;

// SetPoint
SetPoint setPoint;

void setup() {
  // LEDに接続したピンのモードを出力にセット
  pinMode(ledPin, OUTPUT);

  // SetPointを初期化
  setPoint.begin(threshold, hysteresis);

  // 2 つのイベントに対してイベントハンドラをセット
  setPoint.attach(RISING_EDGE, onBrightenUp);
  setPoint.attach(FALLING_EDGE, onDarkenUp);
}

void loop() {
  // センサの値を読み取ってその値でSetPointを更新
  int value = analogRead(sensorPin);
  setPoint.update(value);

  // 次のループ開始までに100ms待つ
  delay(100);
}

// 明るくなったら
void onBrightenUp() {
  // LEDを消灯
  digitalWrite(ledPin, LOW);
}

// 暗くなったら
void onDarkenUp() {
  // LEDを点灯
  digitalWrite(ledPin, HIGH);
}

