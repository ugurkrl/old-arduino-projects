/* Arduino Alkaline Battery Tester
 * Version 1.0 
 * Written By Uğur KIRÇIL
 */
#include <LiquidCrystal.h>
double percent=100.0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//CUSTOM CHARS
byte empty[8] = {
 B01110,
 B11011,
 B10001,
 B10001,
 B10001,
 B10001,
 B10001,
 B11111,
};

byte low[8] = {
        B01110,
        B11011,
        B10001,
        B10001,
        B10001,
        B11111,
        B11111,
        B11111
};

byte high[8] = {
        B01110,
        B11011,
        B10001,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
};

byte full[8] = {
        B01110,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
};


void setup(){
  pinMode(13,OUTPUT);
 lcd.createChar(0 ,empty);
 lcd.createChar(1 ,low);
 lcd.createChar(2 ,high);
 lcd.createChar(3 ,full);
 lcd.begin(16, 2);
 lcd.write("AA BATT TESTER");
 lcd.setCursor(0,1);
 lcd.write("UGUR KIRCIL");
 digitalWrite(13,LOW);
 delay(1000);
 digitalWrite(13,HIGH);
 delay(1000);
 digitalWrite(13,LOW);
 delay(1000);
 digitalWrite(13,HIGH);
 delay(1000);
 digitalWrite(13,LOW);
 delay(1000);
 lcd.clear();
 
 }

void loop(){
int sensorValue = analogRead(A0);
float voltage = sensorValue * (5.0 / 1023.0); //Analog data --> Voltage converter
  if(voltage < 0.75){
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,0);
    lcd.print(char(0));
  }
  if(voltage > 0.75 ){
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,0);
    lcd.print(char(1));
  }
  if( voltage > 1.20 ){
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,0);
    lcd.print(char(2));
  }
  if(voltage > 1.53 ) {
    
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,0);
    lcd.print(char(3));}
   if(voltage > 3) { //STOP SKETCH WHEN BATTERY VOLTAGE IS MORE THAN 2.99V 
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("BATT UNSUPPORT");
    lcd.setCursor(0,1);
    lcd.print("RST TO CONTINUE");
    digitalWrite(13, HIGH);
  
    delay(-1);
   }

  lcd.setCursor(2, 0);
  percent=(voltage-0.75)*(100/0.8);
  lcd.print(voltage);
  lcd.print("V  ");
  lcd.print(percent);
  lcd.print("% ");
  delay(1000);
  

 
}



