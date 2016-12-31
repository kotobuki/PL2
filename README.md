# Prototyping Lab 第2版

　小林茂『[Prototyping Lab 第2版—「作りながら考える」ためのArduino実践レシピ](https://www.oreilly.co.jp/books/9784873117898/)』オライリー・ジャパン（2017年）で紹介しているサンプル、およびサポートのための情報を提供します。

　サンプルなどのファイルをダウンロードするには、画面右の「Clone or download」をクリックし、続けて「Download ZIP」をクリックし、ダウンロードされたZIP形式のファイルを展開します。

## フォルダ構成

* **examples** - ArduinoとProcessing、iOS用のサンプル
* **fritzing** - Fritzing用の部品ライブラリ

## 正誤情報

　まだ正誤情報はありません。

## 補足情報

### Arduino Create

　本書では、arduino.ccからダウンロードしたArduino IDEをオフラインで用いる方法を紹介しています。これ以外の方法として、2016年5月にアナウンスされたオンラインプラットフォーム「[Arduino Create](https://create.arduino.cc/)」を利用する方法もあります。

`URL` https://create.arduino.cc/

　Arduino Createは、オンラインのIDE「[Web Editor](https://create.arduino.cc/editor/)」やプロジェクトを公開できる「[Project Hub](https://create.arduino.cc/projecthub)」、クラウドサービス「[Arduino Cloud](https://cloud.arduino.cc/cloud/)」などから構成されます。オンラインのIDEで書いたスケッチに回路図や配線図を加えたものを簡単に公開できるため、教育機関やファブ施設などにおいてArduinoを使用したワークショップを開催する時には便利だと思われますので、そうした場面があれば試してみるとよいでしょう。

例：[サンプルI 4.6](https://create.arduino.cc/editor/kotobuki/1ed0e8bf-4350-4d16-8f58-a4a05bf0bd30/preview)

　Arduino Createを使用できるようにするまでの手順の例を以下に示します。

1. ウェブブラウザ（Google Chromeを推奨）で[arduino.cc](https://www.arduino.cc/)を開く
2. 画面右上の「[SIGN UP](https://id.arduino.cc/auth/signup)」をクリック
3. ユーザ名（Username）とパスワード（Password）、メールアドレス（Email Address）を入力してアカウントを作成
4. ウェブブラウザで「[Web Editor](https://create.arduino.cc/editor)」にアクセス
5. ウェブブラウザからPC上のUSBポート経由でArduinoボードにアクセスするためのプラグイン「Arduino Web Editor Plugin」を[画面上の指示](http://create.arduino.cc/getting-started/plugin)に従ってインストール

### 第8章：ネットワーク接続

　本書では、ネットワーク接続の方法としてレシピ32でBluetooth Low Energy（BLE）を、レシピ33と34でWi−Fiの2つを紹介しました。

　BLEで接続できるArduinoボードには、本書で紹介したArduino互換機「[Adafruit Feather 32u4 Bluefruit LE](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/)」のほかに「[Arduino/Genuino 101](https://www.arduino.cc/en/Main/ArduinoBoard101)」があります。Arduino/Genuino 101は、Intelがウェアラブルデバイス用に開発したBLEの無線通信機能を内蔵したモジュール「Curie」にくわえ、3軸の加速度センサと3軸のジャイロセンサなどをArduino Unoと同じピン配置のボード上に搭載しています。105ページの説明を参考に、ボードマネージャで「Intel Curie Boards」を追加するだけで簡単に利用できますので、BLEにくわえて加速度センサやジャイロセンサが必要な場合には試してみるとよいでしょう。

　Arduinoでネットワークに接続するBLEやWi−Fi以外の方法としては「3G」や「LTE」があります。3GやLTEは、携帯電話やスマートフォン、タブレットで音声やデータの通信手段として広く用いられている規格で、インフラとして既に普及しており日本のほぼすべての人口をカバーしているのが特長です。また、最近では映像や音声と比較してデータ量の少ないIoTを対象にした低価格のモジュールやプランも次々と登場しています。以下に、Arduinoと簡単に組み合わせられるものをいくつか紹介しますので、目的に応じて試してみるとよいでしょう。

* [3GIM V2.1](http://tabrain.jp/service3gim.html)
	* メーカー：[株式会社タブレイン](http://tabrain.jp/)
	* 通信規格：3G
	* Arduino Unoとの接続：3GIMシールドV2.0 for Arduino
* [さくらの通信モジュール（LTE）-β版](https://iot.sakura.ad.jp/product/)
	* メーカー：[さくらインターネット株式会社](https://www.sakura.ad.jp/)
	* 通信規格：LTE
	* Arduino Unoとの接続：Arduino用シールド

## 免責事項

　サンプルおよびドキュメントは、Arduinoを用いたプロトタイピングの手法および関連情報を紹介することを目的としています。著者および著作権者は、このサンプルおよびドキュメントに掲載した情報の利用によって利用者または第三者等に何らかの損害が発生したとしても、かかる損害については一切の責任を負うものではありません。掲載内容に誤りがあった場合も同様です。

## ライセンス

* examplesフォルダのサンプルは[クリエイティブ・コモンズ・ライセンス CC0 1.0 全世界](https://creativecommons.org/publicdomain/zero/1.0/deed.ja)で提供します
* ただし、examples/arduino/libraries/FSMはAlexander Brevigが開発し、Terry Kingが更新した[HAL Libraries](http://arduino-info.wikispaces.com/HAL-LibrariesUpdates)の一部に修正を加えたもので、ライセンスはオリジナルに倣い[Creative Commons Attribution Non-Commercial 3.0 License](https://creativecommons.org/licenses/by-nc/3.0/)とします
* fritzingフォルダのFritzing用部品ライブラリは[クリエイティブ・コモンズ・ライセンス 表示 - 継承 4.0 国際](https://creativecommons.org/licenses/by-sa/4.0/deed.ja)で提供します