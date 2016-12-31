// ESP8266に関連したライブラリのヘッダをインクルード
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-FiアクセスポイントのSSIDとパスワード
const char ssid[] = "********";
const char password[] = "********";

// IFTTTで発行されたキー
const char key[] = "**********************";

// IFTTTサーバ
const char host[] = "https://maker.ifttt.com";

// IFTTTサーバのフィンガープリント
// 参照：https://ssl-tools.net/webservers/maker.ifttt.com
const char fingerPrint[] = "C0:5D:08:5E:E1:3E:E0:66:F3:79:27:1A:CA:1F:FC:09:24:11:61:62";

// イベント名
const char event[] = "ping";

// ボタンに接続したピンの番号
const int buttonPin = 12;

// 前回のボタンの状態
int lastButtonState = 0;

void setup() {
  // ボタンに接続したピンを入力に設定
  pinMode(buttonPin, INPUT);

  // シリアル通信を開始
  Serial.begin(115200);
  Serial.println();

  // Wi-Fiアクセスポイントに接続
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // ボタンに接続したピンの状態を読み取る
  int buttonState = digitalRead(buttonPin);

  // 前回がLOWで今回がHIGHであれば以下を実行
  if (lastButtonState == LOW && buttonState == HIGH) {
    // シリアルに文字列「Pressed」をプリントして
    Serial.println("Pressed");

    // IFTTTサーバにウェブリクエストを送信
    sendWebRequest();
  }

  // 前回の状態として現在の状態をセット
  lastButtonState = buttonState;
}

void sendWebRequest() {
  // HTTPクライアント
  HTTPClient client;

  // URLを生成
  // 形式：maker.ifttt.com/trigger/{event}/with/key/{key}
  String url = host;
  url += "/trigger/";
  url += event;
  url += "/with/key/";
  url += key;

  // IFTTTのサーバとフィンガープリントを指定
  client.begin(url, fingerPrint);

  // サーバに接続してウェブリクエストを送信
  int httpCode = client.GET();

  // HTTPコードが正の値であれば
  if (httpCode > 0) {
    // 受け取ったHTTPコードをシリアルにプリント
    Serial.print("Code: ");
    Serial.println(httpCode);

    // 受け取ったコードがHTTP_CODE_OKであれば
    if (httpCode == HTTP_CODE_OK) {
      // レスポンスをシリアルにプリント
      Serial.print("Response: ");
      Serial.println(client.getString());
    }
  } else {
    // HTTPコードが負の値であればエラーを文字列としてシリアルにプリント
    Serial.print("Failed: ");
    Serial.println(client.errorToString(httpCode));
  }

  client.end();
}

