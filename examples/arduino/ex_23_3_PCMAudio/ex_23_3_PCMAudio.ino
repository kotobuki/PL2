#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define SAMPLE_RATE 8000
#include "PCMData.h"

// ボタンに接続したピンの番号
const int buttonPin = 8;

// LEDに接続したピンの番号
const int ledPin = 13;

// スピーカに接続したピンの番号
const int speakerPin = 11;
volatile uint16_t sample;
byte lastSample;

// 前回のボタンの状態
int lastButtonState = LOW;

// タイマ割り込みでサウンドを再生
ISR (TIMER1_COMPA_vect) {
  if (sample >= SOUNDDATA_LENGTH) {
    if (sample == SOUNDDATA_LENGTH + lastSample) {
      stopPlayback();
    }
    else {
      OCR2A = SOUNDDATA_LENGTH + lastSample - sample;
    }
  }
  else {
    OCR2A = pgm_read_byte(&soundData[sample]);
  }
  ++sample;
}

// サウンド再生開始
void startPlayback() {
  digitalWrite(ledPin, HIGH);
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));
  TCCR2A |= _BV(WGM21) | _BV(WGM20);
  TCCR2B &= ~_BV(WGM22);
  TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
  TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
  TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  OCR2A = pgm_read_byte(&soundData[0]);
  cli();
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  OCR1A = F_CPU / SAMPLE_RATE;
  TIMSK1 |= _BV(OCIE1A);
  lastSample = pgm_read_byte(
  &soundData[SOUNDDATA_LENGTH - 1]);
  sample = 0;
  sei();
}

// サウンド再生停止
void stopPlayback() {
  TIMSK1 &= ~_BV(OCIE1A);
  TCCR1B &= ~_BV(CS10);
  TCCR2B &= ~_BV(CS10);
  digitalWrite(ledPin, LOW);
  digitalWrite(speakerPin, LOW);
}

void setup() {
  // 各ピンのモードをセット
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // ボタンの状態を読み取る
  int buttonState = digitalRead(buttonPin);

  // 前回がLOWで現在がHIGHであればサウンドを再生
  if (lastButtonState == LOW && buttonState == HIGH) {
    startPlayback();
  }

  // 前回のボタンの状態として現在の状態をセット
  lastButtonState = buttonState;

  // 次のループ開始まで10ms待つ
  delay(10);
}

