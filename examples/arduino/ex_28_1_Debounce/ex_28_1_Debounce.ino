#include <LiquidCrystal.h>

// ボタンに接続したピンの番号
const int buttonPin = 8;

// 前回のボタンの状態
int lastButtonState = LOW;

// 前回チャタリング除去を行った時間
long lastDebounceTime = 0;

// チャタリング除去を行う時間
long debounceDelay = 50;

// ボタンが押されたカウント
int count = 0;

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // ボタンに接続したピンのモードを入力にセット
  pinMode(buttonPin, INPUT);

  // LCDの桁数と行数をセット
  lcd.begin(16, 2);

  // カウントをLCDにプリント
  printCount();
}

void loop() {
  // ボタンに接続したピンの状態を読み取る
  int buttonState = digitalRead(buttonPin);

  // 前回がLOWで今回がHIGHであれば以下を実行
  if (lastButtonState == LOW && buttonState == HIGH) {
    // 現在の時刻
    int now = millis();

    // 前回デバウンスを行ってから一定時間が経過していればonPressを実行
    if ((now - lastDebounceTime) > debounceDelay) {
      onPress();
    }

    // 前回デバウンスを行った時間として現在の時刻をセット
    lastDebounceTime = now;
  }

  // 前回の状態として現在の状態をセット
  lastButtonState = buttonState;
}

void onPress() {
  // カウントを1だけ増やす
  count = count + 1;
  // LCDにカウントをプリント
  printCount();
}

void printCount() {
  // LCDの表示内容をクリアした後カウントをプリント
  lcd.clear();
  lcd.print("Count: ");
  lcd.print(count);
}

