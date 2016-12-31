//
//  ViewController.swift
//  32_6_UART
//
//  Created by Shigeru Kobayashi on 2016/07/16.
//  This is free and unencumbered software released into the public domain.
//

import UIKit
import CoreBluetooth
import UserNotifications

// UARTサービスのUUID文字列
let uartServiceUUIDString = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"

// UART TXキャラクタリスティックのUUID文字列
let uartTXCharUUIDString = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// UART RXキャラクタリスティックのUUID文字列
let uartRXCharUUIDString = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

class ViewController: UIViewController, CBCentralManagerDelegate, CBPeripheralDelegate {
  // セントラルマネージャ
  fileprivate var centralManager: CBCentralManager!
  
  // ペリフェラル
  fileprivate var peripheral: CBPeripheral?
  
  // UART TXキャラクタリスティック
  fileprivate var uartTXCharacteristic: CBCharacteristic?
  
  // UART RXキャラクタリスティック
  fileprivate var uartRXCharacteristic: CBCharacteristic?
  
  // 受信バッファ
  fileprivate var receivedBuffer = ""
  
  @IBOutlet weak var connectButton: UIButton!
  @IBOutlet weak var ledSwitch: UISwitch!
  @IBOutlet weak var buttonSwitch: UISwitch!
  @IBOutlet weak var logTextView: UITextView!
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    // Connectボタンの外枠を設定
    connectButton.layer.cornerRadius = 8.0
    connectButton.layer.borderColor = UIColor.lightGray.cgColor
    connectButton.layer.borderWidth = 1.0
    
    logTextView.layer.borderColor = UIColor.lightGray.cgColor
    logTextView.layer.borderWidth = 1.0
    
    // セントラルマネージャを初期化
    centralManager = CBCentralManager(delegate: self, queue: nil)
    
    // アラートを表示して通知許可を求める
    UNUserNotificationCenter.current().requestAuthorization(
    options: [.alert, .badge, .sound]) { (granted, _) in
      if granted {
        self.printToLog("Granted an authorization\n")
      } else {
        self.printToLog("Not granted an authorization\n")
      }
    }
  }
  
  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    // Dispose of any resources that can be recreated.
  }
  
  func printToLog(_ message: String) {
    // ログの先頭に時刻をプリント
    let date = Date()
    let formatter = DateFormatter()
    formatter.dateFormat = "HH:mm:ss"
    let formattedDate = formatter.string(from: date)
    
    // 指定されたメッセージを表示してテキストビューの最後にスクロール
    DispatchQueue.main.async {
      self.logTextView.insertText(formattedDate + " ")
      self.logTextView.insertText(message)
      let range = NSMakeRange(self.logTextView.text.characters.count - 1, 0)
      self.logTextView.scrollRangeToVisible(range)
    }
  }
  
  // セントラルマネージャの状態が変化すると呼ばれる
  func centralManagerDidUpdateState(_ central: CBCentralManager) {
    var state = ""

    switch central.state {
    case CBManagerState.unknown:
      state = "Unknown"
    case CBManagerState.resetting:
      state = "Resetting"
    case CBManagerState.unsupported:
      state = "Unsupported"
    case CBManagerState.unauthorized:
      state = "Unauthorized"
    case CBManagerState.poweredOff:
      state = "PoweredOff"
    case CBManagerState.poweredOn:
      state = "PoweredOn"
    }

    printToLog("Central Manager is " + state + "\n")
  }
  
  // ペリフェラルを発見すると呼ばれる
  func centralManager(_ central: CBCentralManager,
                      didDiscover peripheral: CBPeripheral,
                      advertisementData: [String : Any],
                      rssi RSSI: NSNumber)
  {
    // 発見したペリフェラルをコンソールにプリント
    printToLog("Found " + peripheral.debugDescription + "\n")
    
    // もし名前が「Adafruit Bluefruit LE」のペリフェラルを発見したら
    if peripheral.name == "Adafruit Bluefruit LE" {
      // 今後アクセスするためにperipheral変数に保存
      self.peripheral = peripheral
      
      // 目的のペリフェラルが見つかったのでスキャンを停止
      centralManager.stopScan()
      
      // ペリフェラルに接続開始
      centralManager.connect(peripheral, options: nil)
    }
  }
  
  // ペリフェラルへの接続が成功すると呼ばれる
  func centralManager(_ central: CBCentralManager,
                      didConnect peripheral: CBPeripheral)
  {
    // Connectボタンを更新
    connectButton.setTitle("Disconnect", for: UIControlState())
    connectButton.isEnabled = true
    
    // サービス探索結果を受け取るためにデリゲートをセット
    peripheral.delegate = self
    
    // UARTサービスを探索開始
    peripheral.discoverServices([CBUUID(string: uartServiceUUIDString)])
  }
  
  // ペリフェラルへの接続が失敗すると呼ばれる
  func centralManager(_ central: CBCentralManager,
                      didFailToConnect peripheral: CBPeripheral,
                      error: Error?)
  {
    print("[ERROR] didFailToConnectPeripheral: \(error)")
  }
  
  // サービス発見時に呼ばれる
  func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
    // もし何かエラーが発生していたらコンソールにエラーをプリント
    if let error = error {
      print("[ERROR] didDiscoverServices: \(error)")
      return
    }
    
    // もしサービスが見つからなければ
    guard let services = peripheral.services, services.count > 0 else {
      // サービスが見つからなかったことをコンソールにプリント
      print("Found no services")
      return
    }
    
    printToLog("Found " + String(services.count) + " service(s):\n")
    printToLog(services.debugDescription + "\n")
    
    // 発見したサービスの全てに対してキャラクタリスティックを探索開始
    for service in services {
      let characteristicsUUIDs = [CBUUID(string: uartTXCharUUIDString),
                                  CBUUID(string: uartRXCharUUIDString)]
      peripheral.discoverCharacteristics(characteristicsUUIDs, for: service)
    }
  }
  
  // キャラクタリスティック発見時に呼ばれる
  func peripheral(_ peripheral: CBPeripheral,
                  didDiscoverCharacteristicsFor service: CBService,
                  error: Error?)
  {
    // もし何かエラーが発生していたらコンソールにエラーをプリント
    if let error = error {
      print("[ERROR] didDiscoverCharacteristicsForService: \(error)")
      return
    }
    
    // もしキャラクタリスティックが見つからなければ
    guard let characteristics = service.characteristics, characteristics.count > 0 else {
      // キャラクタリスティックが見つからなかったことをコンソールにプリント
      print("Found no characteristics for \(peripheral)")
      return
    }
    printToLog("Found " + String(characteristics.count) + " characteristic(s):\n")
    printToLog(characteristics.debugDescription + "\n")
    
    // 発見したキャラクタリスティックの中からUART TXとUART RXを探す
    for characteristic in characteristics {
      if characteristic.uuid.isEqual(CBUUID(string: uartTXCharUUIDString)) {
        // 発見したことをプリントし、後からアクセスするためにuartTXCharacteristic変数に保存
        printToLog("Found the UART TX Characteristic\n")
        uartTXCharacteristic = characteristic
        
        // uartTXCharacteristicに対して通知を設定
        peripheral.setNotifyValue(true, for: uartTXCharacteristic!)
        
        // Buttonスイッチを有効にセット
        buttonSwitch.isEnabled = true
      } else if characteristic.uuid.isEqual(CBUUID(string: uartRXCharUUIDString)) {
        // 発見したことをプリントし、後からアクセスするためにuartRXCharacteristic変数に保存
        printToLog("Found the UART RX Characteristic\n")
        uartRXCharacteristic = characteristic
        
        // LEDスイッチを有効にセット
        ledSwitch.isEnabled = true
      }
    }
  }
  
  // データ更新時に呼ばれる
  func peripheral(_ peripheral: CBPeripheral,
                  didUpdateValueFor characteristic: CBCharacteristic,
                  error: Error?)
  {
    // もし何かエラーが発生していたらコンソールにエラーをプリント
    if let error = error {
      print("[ERROR] didUpdateValueForCharacteristic: \(error)")
      return
    }
    
    // 受け取ったデータを文字列に変換し、受信バッファに追加
    let receivedString = NSString(
      data: characteristic.value!, encoding: String.Encoding.utf8.rawValue)!
    receivedBuffer = receivedBuffer + (receivedString as String)
    
    // コマンド文字列が受信バッファにはもうないかどうかを判断する変数
    var noMoreEvent = false
    
    // コマンド文字列が受信バッファにある間繰り返し実行
    while (!noMoreEvent) {
      // 受信バッファの文字列の中で「*」を検索
      let strRange:Range? = receivedBuffer.range(of: "*")
      
      // もし見つからなければ
      if strRange == nil {
        // コマンド文字列は受信バッファにはもうないと判断して変数の値をセット
        noMoreEvent = true
      } else {
        // もし見つかったら、受信バッファから部分文字列をコマンドとして取り出して
        let command = receivedBuffer.substring(to: (strRange?.lowerBound)!)
        receivedBuffer = receivedBuffer.substring(from: (strRange?.upperBound)!)
        printToLog("Received '" + command + "'\n")
        
        // コマンドに応じてButtonスイッチの状態を更新
        if command == "Pressed" {
          buttonSwitch.setOn(true, animated: false)
        } else if command == "Released" {
          buttonSwitch.setOn(false, animated: false)
        }
        
        // バックグラウンド動作中もしくはロック画面であれば通知を表示する
        let content = UNMutableNotificationContent()
        content.title = "Received"
        content.body = command
        let trigger = UNTimeIntervalNotificationTrigger.init(
          timeInterval: 0.1, repeats: false)
        let request = UNNotificationRequest.init(
          identifier: "received", content: content, trigger: trigger)
        UNUserNotificationCenter.current().add(request)
      }
    }
  }
  
  // Connectボタンをタップした時に呼ばれる
  @IBAction func connectButtonTapped(_ sender: UIButton) {
    if peripheral == nil {
      // まだペリフェラルと接続していなければスキャンを開始
      let serviceUUIDs = [CBUUID(string: uartServiceUUIDString)]
      centralManager.scanForPeripherals(withServices: serviceUUIDs, options: nil)
      
      // スキャン中はConnectボタンを無効にセットしてタイトルも変更
      sender.isEnabled = false;
      sender.setTitle("Scanning...", for: UIControlState.disabled)
    } else {
      // 既にペリフェラルと接続していたら接続をキャンセル
      centralManager.cancelPeripheralConnection(peripheral!)
      peripheral = nil
      
      // Connectボタン、LEDスイッチ、Buttonスイッチを更新
      sender.setTitle("Connect", for: UIControlState())
      ledSwitch.isEnabled = false
      buttonSwitch.isEnabled = false
    }
  }
  
  // LEDスイッチの状態が変化した時に呼ばれる
  @IBAction func ledSwitchChanged(_ sender: UISwitch) {
    // ペリフェラルに書き込むデータ
    var command: Data
    
    // LEDスイッチの状態に応じてデータを用意し
    if sender.isOn {
      command = "On*".data(using: String.Encoding.utf8)!
    } else {
      command = "Off*".data(using: String.Encoding.utf8)!
    }
    
    // ペリフェラルのuartRXCharacteristicに対して書き込む
    if uartRXCharacteristic != nil {
      peripheral!.writeValue(
        command, for: uartRXCharacteristic!,
        type: CBCharacteristicWriteType.withoutResponse)
    }
  }
  
}
