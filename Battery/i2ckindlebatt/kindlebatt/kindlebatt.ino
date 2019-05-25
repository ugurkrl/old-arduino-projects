/* 
-AMAZON KINDLE I2C BATTERY READER- 
*Version 1.0 (9.6.2015)
*Written By Uğur KIRÇIL.
*/
#include <I2C.h> //i2cmaster lib is easy to use and supports smbus + i2c batts
int CYCT=0;
int CYCL=0;
int SOC=0;
void setup() {
I2c.begin(); //We should start i2c
Serial.begin(9600); //9600baud will be enough
Serial.println("AMAZON KINDLE I2C BATTERY READER");
Serial.println("Version 1.0");
Serial.println("Written By Ugur Kircil");
Serial.println("");
Serial.println("");
digitalWrite(13,HIGH); //LED will be high while scanning battery
I2c.scan(); // add // if you want to test i2c bus and scan batt
digitalWrite(13,LOW); //LOW the LED
}

void loop() {
I2c.read(0x0d, 0x2a ,8); //Read 0x2a address in 0x55 device 
int CYCT = I2c.receive(); 
Serial.print("Total Cycle Count : ");
Serial.print(CYCT); //print 0x2a address to serial terminal
Serial.print(" cycles");
Serial.println("");
I2c.read(0x0d, 0x28 ,8);
int CYCL = I2c.receive();
Serial.print("Cycle Count Since Learning Cycle : ");
Serial.print(CYCL);
Serial.print(" cycles");
Serial.println("");  
I2c.read(0x0d, 0x0B ,8);
int SOC = I2c.receive();
Serial.print("State Of Charge : %");
Serial.print(SOC);
Serial.println("");  

 delay(5000); //it will refresh in every 5sec
}
