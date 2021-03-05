#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);
/*
LCDは下記の通りの配線で
SDA → A4
SCL → A5
*/

int DIR = 13;  //define Direction pin
int ENA = 12;  //define Enable Pin
int PUL = 11;  //define Pulse pin
int HOL = 10;  //home&Origine status LED

int H_sw = 9;  //home end swich
int P_sw = 8;  //プラススイッチ読み込み
int M_sw = 7;  //マイナススイッチ読み込み
int S_sw = 6;  //セレクトスイッチ読み込み


int C = 0;
float N = 0;
int G = 1; //モータのギヤ比xマイクロステップ数 ギヤ,マイクロステップがない場合 G=1

void home()
{
  while (digitalRead(H_sw))
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
    N = N - 0.01;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(N);
  }
  delay(100);

  for (int h = 0; h < 1000*G; h++)
  {
    digitalWrite(DIR, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
    N = N + 0.01;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(N);
  }

  while (digitalRead(H_sw))
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL, LOW);
    delayMicroseconds(50);
    N = N - 0.01;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(N);
  }
  delay(100);
  N = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(N);
}

void setup()
{
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(HOL, OUTPUT);
  pinMode(P_sw, INPUT_PULLUP);
  pinMode(M_sw, INPUT_PULLUP);
  pinMode(S_sw, INPUT_PULLUP);
  pinMode(H_sw, INPUT_PULLUP);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);

  //home();//電源投入時自動で原点復帰する場合コメントアウト
}

void loop()
{

  if (!digitalRead(S_sw))
  {
    C++;
  }
  if (!digitalRead(H_sw))
  {
    lcd.setCursor(0, 10);
    lcd.print("HOME!");
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
    lcd.setCursor(0, 1);
    lcd.print("mode:Home&Origin");
    break;

  case 1: //0.1mm
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 10*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N + 0.01;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.print(N);
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 10*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N - 0.01;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.print(N);
      }
    lcd.setCursor(0, 1);
    lcd.print("mode:0.1mm");
    }
    break;

  case 2: //1.0mm
    
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 100*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N + 0.01;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.print(N);
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 100*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N - 0.01;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.print(N);
      }
    lcd.setCursor(0, 1);
    lcd.print("mode:1.0mm");
    }
    break;

  case 3: //10mm
    if (!digitalRead(P_sw))
    {
      for (int i = 0; i < 1000*G; i++)
      {
        digitalWrite(DIR, LOW);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N + 0.01;
        lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.print(N);
      }
    }
    if (!digitalRead(M_sw) && digitalRead(H_sw))
    {
      for (int i = 0; i < 1000*G; i++)
      {
        digitalWrite(DIR, HIGH);
        digitalWrite(ENA, HIGH);
        digitalWrite(PUL, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL, LOW);
        delayMicroseconds(50);
        N = N - 0.01;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.print(N);
      }
    lcd.setCursor(0, 1);
    lcd.print("mode:10mm");
    }
    break;

  default:
    C = 0;
    break;
  }
  delay(100);
}