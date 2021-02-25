#include <Arduino.h>
#include <M5Stack.h>

int PUL = 21;  //define Pulse pin
int DIR = 17;  //define Direction pin
int ENA = 16;  //define Enable Pin
int H_sw = 22; //home end swich
int C = 0;
float N = 0;
int G = 1; //モータのギヤ比 ギヤがない場合 G=1

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
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(80, 60);
    M5.Lcd.println(N);
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
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(80, 60);
    M5.Lcd.println(N);
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
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(80, 60);
    M5.Lcd.println(N);
  }
  delay(500);
  N = 0;
}

void setup()
{
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(H_sw, INPUT_PULLUP);
  M5.begin();
  //home();//電源投入時自動で原点復帰する場合コメントアウト
  M5.Lcd.drawRect(70, 20, 160, 80, BLUE);
  M5.Lcd.setCursor(240, 80);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("mm");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(5, 150);
  M5.Lcd.print("10mm  1.0mm  0.1mm");

  M5.Lcd.setCursor(255, 145);
  M5.Lcd.print("HOME");
  M5.Lcd.setCursor(240, 160);
  M5.Lcd.print("ORIGIN");

  M5.Lcd.setCursor(20, 220);
  M5.Lcd.print("+/HOME -/ORIGIN  SELECT");

  for (int t = 0; t < 340; t = t + 85)
  {
    int Tx1 = 15 + t;
    int Ty = 130;
    M5.Lcd.drawTriangle(Tx1, Ty, Tx1 + 20, Ty, Tx1 + 10, Ty + 10, BLUE);
  }

  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(80, 60);
  M5.Lcd.println(N);
}

void loop()
{
  M5.update();

  while (!H_sw)
  {
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(80, 60);
    M5.Lcd.print("HOME");
  }

  if (M5.BtnC.wasPressed())
  {
    C++;
    M5.Lcd.fillRect(0, 130, 320, 10, BLACK);
  }

  switch (C)
  {
  case 0: //HOME&ORIGIN
    for (int t = 0; t < 340; t = t + 85)
    {
      int Tx1 = 15 + t;
      int Ty = 130;
      M5.Lcd.drawTriangle(Tx1, Ty, Tx1 + 20, Ty, Tx1 + 10, Ty + 10, BLUE);
    }
    M5.Lcd.fillTriangle(270, 130, 270 + 20, 130, 270 + 10, 130 + 10, BLUE);

    if (M5.BtnA.wasPressed())
    {
      home();
    }
    if (M5.BtnB.wasPressed())
    {
      N = 0;
      M5.Lcd.setTextSize(4);
      M5.Lcd.setCursor(80, 60);
      M5.Lcd.println(N);
    }
    break;

  case 1: //0.1mm
    for (int t = 0; t < 340; t = t + 85)
    {
      int Tx1 = 15 + t;
      int Ty = 130;
      M5.Lcd.drawTriangle(Tx1, Ty, Tx1 + 20, Ty, Tx1 + 10, Ty + 10, BLUE);
    }
    M5.Lcd.fillTriangle(185, 130, 185 + 20, 130, 185 + 10, 130 + 10, BLUE);

    if (M5.BtnA.wasPressed())
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.fillRect(80, 30, 140, 60, BLACK);
        M5.Lcd.println(N);
      }
    }
    if (M5.BtnB.wasPressed() && digitalRead(H_sw))
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.fillRect(80, 30, 140, 60, BLACK);
        M5.Lcd.println(N);
      }
    }
    break;

  case 2: //1.0mm
    for (int t = 0; t < 340; t = t + 85)
    {
      int Tx1 = 15 + t;
      int Ty = 130;
      M5.Lcd.drawTriangle(Tx1, Ty, Tx1 + 20, Ty, Tx1 + 10, Ty + 10, BLUE);
    }
    M5.Lcd.fillTriangle(100, 130, 100 + 20, 130, 100 + 10, 130 + 10, BLUE);
    if (M5.BtnA.wasPressed())
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.println(N);
      }
    }
    if (M5.BtnB.wasPressed() && digitalRead(H_sw))
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.println(N);
      }
    }
    break;

  case 3: //10mm
    for (int t = 0; t < 340; t = t + 85)
    {
      int Tx1 = 15 + t;
      int Ty = 130;
      M5.Lcd.drawTriangle(Tx1, Ty, Tx1 + 20, Ty, Tx1 + 10, Ty + 10, BLUE);
    }
    M5.Lcd.fillTriangle(15, 130, 15 + 20, 130, 15 + 10, 130 + 10, BLUE);
    if (M5.BtnA.wasPressed())
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.println(N);
      }
    }
    if (M5.BtnB.wasPressed() && digitalRead(H_sw))
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
        M5.Lcd.setTextSize(4);
        M5.Lcd.setCursor(80, 60);
        M5.Lcd.println(N);
      }
    }
    break;

  default:
    C = 0;
    break;
  }
  delay(100);
}