// ESP8266に関連したライブラリのヘッダをインクルード
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-FiアクセスポイントのSSIDとパスワード
const char ssid[] = "********";
const char password[] = "********";

// IDCF Cloudに関する設定
const char host[] = "http://***.***.**.***";
const char trigger_1_uuid[] = "********-****-****-****-************";
const char trigger_1_token[] = "********";

// text1として送信するメッセージ
const char text1[] = "ping";

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
  Serial.println("IP address: ");
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
  // 形式：/data/{trigger-1のuuid}
  String url = host;
  url += "/data/";
  url += trigger_1_uuid;

  // IDCFクラウドのサーバを指定
  client.begin(url);
  client.addHeader("meshblu_auth_uuid", trigger_1_uuid);
  client.addHeader("meshblu_auth_token", trigger_1_token);
  client.addHeader("Content-Type",
                   "application/x-www-form-urlencoded");

  // メッセージのボディとして送信するテキスト
  // 形式：text1={テキスト1}
  String body = "text1=";
  body += text1;

  // サーバに接続してウェブリクエストを送信
  int httpCode = client.POST(body);

  // HTTPコードが正の値であれば
  if (httpCode > 0) {
    // 受け取ったHTTPコードをシリアルにプリント
    Serial.print("Code: ");
    Serial.println(httpCode);
  } else {
    // HTTPコードが負の値であればエラーを文字列としてシリアルにプリント
    Serial.printf("Failed: ");
    Serial.println(client.errorToString(httpCode));
  }

  client.end();
}

