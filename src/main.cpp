#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
 
LiquidCrystal_I2C lcd(0x27,16,2);
/**************LCD配線******************/
  //SDA → A4
  //SCL → A5
/**************************************/


/********************モータドライバ配線と設定***********************/
  //下記プログラム参照で配線の事
  //SW1の1~3番ピンはON(ステップ分割数1・1パルス1.8°・分解能200)とする。
  //SW1の4番ピンはOFF(1パルス入力方式)
  //駆動電流減衰率設定ON(節電モードは制御しません)
  //停止電流設定は説明書の通り、SW1を6=OFF,7=ON,8=ONとする。
  //駆動電流設定は説明書の通り、SW2をB(2.0A)設定とする。

  //ドライバは、1パルス設定・駆動電流制御信号OFF・停止電流設定信号OFF
  //励磁タイミング信号の使用なし・モータ停止電流設定信号なし
  //として制御します。

int DIR = 13;  //回転方向信号
int ENA = 12;  //出力電流イネーブル信号
int PUL = 11;  //回転パルス信号

/*****************************************************************/

/************************入力信号読み込み***************************/
int H_sw = 9;  //home end swich
int P_sw = 8;  //プラススイッチ読み込み
int M_sw = 7;  //マイナススイッチ読み込み
int S_sw = 6;  //セレクトスイッチ読み込み
/*****************************************************************/

int C = 0; //モード切り替え用
float N = 0;//現在地表示用
int G = 10; //モータのギヤ比を代入

void home()
{
  while (digitalRead(H_sw))
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL, LOW);
    delayMicroseconds(800);
    
  }
  

  for (int i = 0; i < 300*G; i++)
  {
    digitalWrite(DIR, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL, LOW);
    delayMicroseconds(800);
    
  }

  for (int i = 0; i < 300*G; i++)
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL, LOW);
    delayMicroseconds(800);
  }
  
  N = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(N);
}

void test()//test mode CW,CCW1回転を繰り返す。
{
  for (int i = 0; i < 200*G; i++)
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL, LOW);
    delayMicroseconds(800);
  }
  delay(100);
  for (int i = 0; i < 200*G; i++)
  {
    digitalWrite(DIR, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL, LOW);
    delayMicroseconds(800);
  }
}

void setup()
{
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(P_sw, INPUT_PULLUP);
  pinMode(M_sw, INPUT_PULLUP);
  pinMode(S_sw, INPUT_PULLUP);
  pinMode(H_sw, INPUT_PULLUP);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(115200);

  //home();
  //電源投入時自動で原点復帰する場合コメントアウト
}

void loop()
{
  //test();//test mode正式実装の場合コメントアウトしてください。

  if (!digitalRead(S_sw))
  {
    C++;
    delay(500);
  }
  if (!digitalRead(H_sw))
  {
    lcd.setCursor(0, 10);
    lcd.print("HOME");
  }

  switch (C)
  {
  case 0: //HOME&ORIGIN

    if (!digitalRead(P_sw))
    {
      home();
    }
    if (!digitalRead(M_sw))
    {
      N = 0;
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.print(N);
    }
    lcd.setCursor(0, 0);
    lcd.print("mode:Home&Origin");
    Serial.println("mode:Home&Origin");
    lcd.setCursor(0, 1);
    lcd.print(N);
    break;

  case 1: //0.1mm
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 10*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        
        N = N + (0.01/G);
        
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 10*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        N = N - (0.01/G);
       if (!digitalRead(H_sw))
       {
         break;
       }
       
      }
    

    }
    lcd.setCursor(0, 0);
    lcd.print("mode:0.1mm      ");
    lcd.setCursor(0, 1);
    
    lcd.print(N);
    
    Serial.print("mode:0.1mm ");
    Serial.println(N);
    break;

  case 2: //1.0mm
    
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 100*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        N = N + (0.01/G);
        
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 100*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        N = N - (0.01/G);
        if (!digitalRead(H_sw))
       {
         break;
       }
      }
    
    }
    
    lcd.setCursor(0, 1);
    
    lcd.print(N);
    lcd.setCursor(0, 0);
    lcd.print("mode:1.0mm      ");
    Serial.print("mode:1.0mm ");
    Serial.println(N);
    break;

  case 3: //10mm
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 1000*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        N = N + (0.01/G);
        
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 1000*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, LOW);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(800);
        digitalWrite(PUL, LOW);
        delayMicroseconds(800);
        N = N - (0.01/G);
        if (!digitalRead(H_sw))
       {
         break;
       }
      }
    
    }
    
    lcd.setCursor(0, 1);
    
    lcd.print(N);
    lcd.setCursor(0, 0);
    lcd.print("mode:10mm      ");
    Serial.print("mode:10mm ");
    Serial.println(N);
    break;

  default:
    C = 0;
    break;
  }
}