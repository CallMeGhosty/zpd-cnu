#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIGGER A0
#define ECHO A1
#define BUZZER 3
#define THERMISTOR A3

byte bar[] = {A2, 12, 10, 9, 8, 7, 6, 5, 4, 2};
long duration, bars;
double distance;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  for (byte i = 0; i < 10; i++) pinMode(bar[i], OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Mate-info");
  lcd.setCursor(4, 1);
  lcd.print("intensiv");
}

void loop() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2.0;
  bars = 1000.0 / (10 * distance);

  if (bars > 10) bars = 10;
  
  for (int i = 0; i <= bars; i++) {
    for (byte j = 0; j < i; j++) digitalWrite(bar[j], HIGH);
    for (byte j = i; j < 10; j++) digitalWrite(bar[j], LOW);
  }

  analogWrite(BUZZER, bars * 255 / 10);
  
  delay(50);
}
