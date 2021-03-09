# Arduinoでカリ出し機のクリアランス調整プログラム
Arduinoでコマとコマの隙間をステッピングモータを使って調整するプログラム   
 入力はすべて内部プルアップ済み。  
 ### 仕様機材  
      *  Arduino  
      *  LCD 16x2(IC2接続)


    
## ~ インストール ~
 
        1,  Download ZIP もしくは、Git Cloneする。
          
        2,  ./src/main.cpp ファイル内の

            int G = 1; //モータのギヤ比　ギヤがない場合 G=1 
                ※例 ギヤ比1/20の場合 int G =20;
            
        3,   初期プログラムでは、テストモードで作動。(CW・CCWを交互に繰り返す)  
        　　テストモード解除は、132行目付近のtest()をコメントアウト。　　
        　　
        4,   主電源投入時または、Aruduinoリセット時に自動で原点復帰を行いたい場合、127行目付近の
            //home();//電源投入時自動で原点復帰する場合コメントアウト
            をコメントアウトすると自動原点復帰モードになる。


## ~ シナノケンシ　Stepper Motor Driver ~

ドライバの詳細は[リンク](http://www.plexmotion.com/download/files/CSB-UK-gear_manual.pdf)を参考にしました。

        
        SW1の1~3番ピンはON(ステップ分割数1・1パルス1.8°・分解能200)とする。
        SW1の4番ピンはOFF(1パルス入力方式)
        駆動電流減衰率設定ON(節電モードは制御しません)
        停止電流設定は説明書の通り、SW1を6=OFF,7=ON,8=ONとする。
        駆動電流設定は説明書の通り、SW2をB(2.0A)設定とする。
        
        ドライバは、1パルス設定・駆動電流制御信号OFF・停止電流設定信号OFF
        励磁タイミング信号の使用なし・モータ停止電流設定信号なし、として制御します。　　

## ~　配線　~
　　下記参照で配線の事　　

        DIR = 13;  //回転方向信号
        ENA = 12;  //出力電流イネーブル信号
        PUL = 11;  //回転パルス信号
        H_sw = 9;  //home end swich
        P_sw = 8;  //プラススイッチ読み込み
        M_sw = 7;  //マイナススイッチ読み込み
        S_sw = 6;  //セレクトスイッチ読み込み

    
以上
  