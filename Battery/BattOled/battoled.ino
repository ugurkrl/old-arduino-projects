/**********INFO******************* 
SMBUS Battery Reader. Version 1.1
Written By Ugur Kircil
**********************************/

/**********CHANGE  LOG*************
Version 1.1:
Finished in 12.6.2015
->Added OLED Screen
->Changed Sequence of RC,FCC,DC
->Cleaned The Sketch a little bit
Version 1.0:
Finished in 09.6.2015
->Base Program
************************************/

#include <Wire.h>
#include <GOFi2cOLED.h>
GOFi2cOLED oled;
#include <I2C.h> //i2cmaster lib is easy to use and supports smbus + i2c batts


void setup() {
I2c.begin(); //We should start i2c
Serial.begin(9600); //9600baud will be enough
oled.init(0x3c);
oled.display();
Serial.println("SMBUS BATTERY READER");
Serial.println("Version 1.0");
Serial.println("Written By Ugur Kircil");
Serial.println("");
Serial.println("");
digitalWrite(13,HIGH); //LED will be high while scanning battery
//I2c.scan(); // remove // if you want to test i2c bus and scan batt
digitalWrite(13,LOW); //LOW the LED
oled.clearDisplay();
}

void loop() { 
oled.clearDisplay(); 

int CYCT; 
I2c.read(0x0b, 0x17 ,2,(uint8_t*) &CYCT); //Read 0x17 address in 0x0b device 
Serial.print("Total Cycle Count : ");
Serial.print(CYCT); //print 0x17 address to serial terminal
Serial.print(" cycles");
Serial.println("");
oled.setCursor(0,48);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("Cycle Count:");
oled.print(CYCT);
oled.print("Cycle");

int VBAT;
I2c.read(0x0b, 0x09 ,2, (uint8_t*) &VBAT);
Serial.print("Battery Voltage : ");
Serial.print(VBAT);
oled.setCursor(0,0);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("Vbatt:");
oled.print(VBAT);
oled.print("mV ");
Serial.print("mV");
Serial.println("");  

int RSOC;
I2c.read(0x0b, 0x0d ,2,(uint8_t*) &RSOC);
Serial.print("Relative State Of Charge : %");
Serial.print(RSOC);
oled.setTextSize(2);
oled.print("%");
oled.print(RSOC);
Serial.println("");  

int RC;
I2c.read(0x0b, 0x0f ,2, (uint8_t*) &RC);
Serial.print("Remaining Capacity: ");
Serial.print(RC);
Serial.print("0 mWh");
Serial.println(""); 
oled.setCursor(0,32);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("RemainCap:");
oled.print(RC);
oled.print("0Wh");

int FCC;
I2c.read(0x0b, 0x10 ,2, (uint8_t*) &FCC);
Serial.print("Full Charge Capacity: ");
Serial.print(FCC);
Serial.print("0 mWh"); //change to mah if your device uses this.
Serial.println("");  
oled.setCursor(0,40);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("FullChgCap:");
oled.print(FCC);
oled.print("0Wh");

int DC;
I2c.read(0x0b, 0x18 ,2, (uint8_t*) &DC);
Serial.print("Design Capacity: ");
Serial.print(DC);
Serial.print("0 mWh");
Serial.println("");

int CURR;
I2c.read(0x0b, 0x0a ,2, (uint8_t*) &CURR);
Serial.print("Current: ");
Serial.print(CURR);
Serial.print("mA");  
oled.setCursor(0,8);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("Current:");
oled.print(CURR);
oled.print("mA");
Serial.println(""); 

int TTE;
I2c.read(0x0b, 0x12 ,2, (uint8_t*) &TTE);
Serial.print("Time To Empty: ");
Serial.print(TTE);
Serial.print(" Mins");
Serial.println(""); 
oled.setCursor(0,16);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("To Empty:");
oled.print(TTE);
oled.print(" Mins");

int TTF;
I2c.read(0x0b, 0x13 ,2, (uint8_t*) &TTF);
Serial.print("Time To Full ");
Serial.print(TTF);  
Serial.print(" Mins");
Serial.println(""); 
oled.setCursor(0,24);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("To Full:");
oled.print(TTF);
oled.print(" Mins");

float WEARAGE = (float)FCC/(float)DC;
WEARAGE=WEARAGE*100;
WEARAGE=100-WEARAGE;
Serial.print("Battery Wear : %");
Serial.print(WEARAGE);
oled.setCursor(0,56);
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.print("Wearage:%");
oled.print(WEARAGE);

oled.display();
Serial.println(""); 
Serial.println(""); 
delay(1000); //it will refresh in every 5sec
 
}
