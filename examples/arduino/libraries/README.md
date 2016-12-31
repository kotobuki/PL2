# ライブラリ

## 内容

　「書類」フォルダ→Arduino→librariesにインストールして使用する。

* FSM：第9章「実践」で使用（P423参照）
* SetPoint：付録B「ライブラリの作成」で使用（P454参照）

## 補足情報

### FSMライブラリ

　FSMライブラリはAlexander Brevigが開発し、Terry Kingが更新した[HAL Libraries](http://arduino-info.wikispaces.com/HAL-LibrariesUpdates)の一部である。FiniteStateMachine.cppに記述されているFiniteStateMachineクラスtimeInCurrentStateメソッドの不具合を修正するため、次のような変更を加えた。

変更前：

```cpp
unsigned long FiniteStateMachine::timeInCurrentState() { 
    millis() - stateChangeTime; 
}
```

変更後：

```cpp
unsigned long FiniteStateMachine::timeInCurrentState() { 
    return millis() - stateChangeTime; 
}
```

　オリジナルに倣い、ライセンスは[Creative Commons Attribution Non-Commercial 3.0 License](https://creativecommons.org/licenses/by-nc/3.0/)とします。