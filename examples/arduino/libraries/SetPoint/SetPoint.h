// 同じヘッダファイルが何回も読み込まれないようにするための条件分岐
// SET_POINT_Hが定義されていなければ以下を読み込む
#ifndef SET_POINT_H
#define SET_POINT_H

// LOWやHIGHなどが定義されているヘッダファイル
#include <Arduino.h>

// 立ち上がりと立ち下がり、それぞれのイベントの定義
#define RISING_EDGE (0)
#define FALLING_EDGE (1)

// イベントハンドラ関数の定義
extern "C" {
  typedef void (*eventHandlerFunction)(void);
}

// SetPointクラスの定義
class SetPoint {
  // 公開メソッドとメンバ変数（今回はメソッドのみ）
  public:
    // コンストラクタ
    SetPoint(void);

    // 閾値とヒステリシスを与えて初期化
    void begin(int threshold, int hysteresis);

    // イベントハンドラをセット
    void attach(int command,
                eventHandlerFunction eventHandler);

    // 新しい値を与えて更新
    void update(int value);

  // 非公開メソッドとメンバ変数（今回はメンバ変数のみ）
  private:
    // 閾値
    int _threshold;

    // ヒステリシス
    int _hysteresis;

    // 前回updateが呼ばれたときの状態
    int _lastState;

    // 立ち上がりと立ち下がり、それぞれのイベントハンドラ
    eventHandlerFunction _risingEdgeEventHandler;
    eventHandlerFunction _fallingEdgeEventHandler;
};

#endif // SET_POINT_Hの条件の終わり
