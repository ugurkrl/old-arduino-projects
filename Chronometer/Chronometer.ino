/*Arduino Chronometer V1.0*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sec=00;
int min=00;
int hr=00;

void setup() {
lcd.begin(16,2);
lcd.setCursor(2,1);
lcd.print("CHRONOMETER");
delay(1000);
lcd.setCursor(0,0);
lcd.print("STARTS IN 5");
delay(1000);
lcd.clear();
lcd.print("STARTS IN 4");
delay(1000);
lcd.clear();
lcd.print("STARTS IN 3");
delay(1000);
lcd.clear();
lcd.print("STARTS IN 2");
delay(1000);
lcd.clear();
lcd.print("STARTS IN 1");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
}

void loop() {

lcd.setCursor(2,2);
lcd.print("CHRONOMETER");
lcd.setCursor(4,0);
lcd.print(hr);
lcd.setCursor(6,0);
lcd.print(":");
lcd.print(min);
lcd.setCursor(9,0);
lcd.print(":");
lcd.print(sec);
sec=sec+1;
delay(1000);


if(sec == 60){
  sec=00;
  min=min+1; 
}else;
if(min == 60){
  min=0;
  hr=hr+1;
}else;

lcd.clear();
}
