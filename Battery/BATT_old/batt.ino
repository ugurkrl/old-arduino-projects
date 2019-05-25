
#include <I2C.h> //i2cmaster lib is easy to use and supports smbus + i2c batts


void setup() {
I2c.begin(); //We should start i2c
Serial.begin(9600); //9600baud will be enough
Serial.println("SMBUS BATTERY READER");
Serial.println("Version 1.0");
Serial.println("Written By Ugur Kircil");
Serial.println("21/06/2015);
Serial.println("");
digitalWrite(13,HIGH); //LED will be high while scanning battery
I2c.scan(); // remove // if you want to test i2c bus and scan batt
digitalWrite(13,LOW); //LOW the LED
}

void loop() { 
 
int CYCT; 
I2c.read(0x0b, 0x17 ,2,(uint8_t*) &CYCT); //Read 0x17 address in 0x0b device 
Serial.print("Total Cycle Count : ");
Serial.print(CYCT); //print 0x17 address to serial terminal
Serial.print(" cycles");
Serial.println("");

int VBAT;
I2c.read(0x0b, 0x09 ,2, (uint8_t*) &VBAT);
Serial.print("Battery Voltage : ");
Serial.print(VBAT);
Serial.print("mV");
Serial.println("");  

int RSOC;
I2c.read(0x0b, 0x0d ,2,(uint8_t*) &RSOC);
Serial.print("Relative State Of Charge : %");
Serial.print(RSOC);
Serial.println("");  

int FCC;
I2c.read(0x0b, 0x10 ,2, (uint8_t*) &FCC);
Serial.print("Full Charge Capacity: ");
Serial.print(FCC);
Serial.print("0 mWh"); //change to mah if your device uses this.
Serial.println("");  


int DC;
I2c.read(0x0b, 0x18 ,2, (uint8_t*) &DC);
Serial.print("Design Capacity: ");
Serial.print(DC);
Serial.print("0 mWh");
Serial.println("");



int RC;
I2c.read(0x0b, 0x0f ,2, (uint8_t*) &RC);
Serial.print("Remaining Capacity: ");
Serial.print(RC);
Serial.print("0 mWh");
Serial.println("");  


int CURR;
I2c.read(0x0b, 0x0a ,2, (uint8_t*) &CURR);
Serial.print("Current: ");
Serial.print(CURR);
Serial.print("mA");  
Serial.println(""); 

int TTE;
I2c.read(0x0b, 0x12 ,2, (uint8_t*) &TTE);
Serial.print("Time To Empty: ");
Serial.print(TTE);
Serial.print(" Mins");
Serial.println(""); 

int TTF;
I2c.read(0x0b, 0x13 ,2, (uint8_t*) &TTF);
Serial.print("Time To Full ");
Serial.print(TTF);  
Serial.print(" Mins");
Serial.println(""); 

float WEARAGE = (float)FCC/(float)DC;
WEARAGE=WEARAGE*100;
Serial.print("Battery Wear : %");
Serial.print(WEARAGE);

Serial.println(""); 
Serial.println(""); 
delay(5000); //it will refresh in every 5sec
 
}
