// ESP8266に関連したライブラリのヘッダをインクルード
#include <ESP8266WiFi.h>

// MQTTを扱うためのライブラリ
#include <MQTTClient.h>

// JSONを扱うためのライブラリ
#include <ArduinoJson.h>

// Wi-FiアクセスポイントのSSIDとパスワード
const char ssid[] = "********";
const char password[] = "********";

// Beebotteで発行されたチャンネルトークン
const char channelToken[]
  = "******************************";

// Beebotteのトピック名 (形式：{channel名}/{resource名})
const char topic[] = "ifttt/action";

// Beebotteサーバ
const char host[] = "mqtt.beebotte.com";

// MQTTで接続する際のクライアントID
const char clientID[] = "ESP8266";

// LEDに接続したピンの番号
const char ledPin = 14;

// Wi-Fiクライアント
WiFiClient wifiClient;

// MQTTクライアント
MQTTClient client;

void setup() {
  // LEDに接続したピンのモードを出力に設定
  pinMode(ledPin, OUTPUT);

  // シリアル通信を開始
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  // もしWi-Fiアクセスポイントに接続していなければ
  if (WiFi.status() != WL_CONNECTED) {
    // 接続を試みる
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, password);

    // もし接続に失敗したら
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      // 5秒間待って再度接続を試みる
      Serial.println("Failed to connect");
      delay(5000);
      return;
    } else {
      // 接続に成功したら取得したIPアドレスをシリアルにプリント
      Serial.print("Wi-Fi connected: ");
      Serial.println(WiFi.localIP());

      // MQTTクライアントを開始
      client.begin(host, wifiClient);
    }
  }

  // もしWi-Fiクライアントが接続していなければ
  if (!client.connected()) {
    // サーバへの接続を試みる
    String username = "token:";
    username += channelToken;
    client.connect(clientID, username.c_str(), "");

    // もしサーバに接続できたら
    if (client.connected()) {
      // 接続できたことをシリアルにプリントし
      Serial.print("MQTT connected: ");
      Serial.println(host);

      // Beebotteのトピック名をトピックに指定してsubscribe
      client.subscribe(topic);
    } else {
      // 接続できなければ5秒間待ってから再度試みる
      delay(5000);
    }
  } else {
    // クライアントが入ってくるメッセージを処理し、
    // サーバとの接続を維持するために定期的に実行
    client.loop();
  }
}

void messageReceived(String topic, String payload,
                     char bytes[], unsigned int length) {
  // 受け取ったペイロードをシリアルにプリント
  Serial.print("Received: ");
  Serial.println(payload);

  // ペイロードをJSON形式のデータとしてデコード
  StaticJsonBuffer<MQTT_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);

  // もしデコードに成功したら以下を実行
  if (root.success()) {
    // もしdataの値が空でなければ
    String message = root["data"];
    if (message.length() > 0) {
      // 受け取ったメッセージが「Ping」であればLEDを短時間点灯
      if (message.equals("Ping")) {
        digitalWrite(ledPin, HIGH);
        delay(250);
        digitalWrite(ledPin, LOW);
      }
    }
  }
}

