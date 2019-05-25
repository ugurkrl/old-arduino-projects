/* 
   HDQ Interface Battery Reader 
  With 128x64 OLED Screen Support
          Version 0.01
            Ugurkrl            
          20.06.2017
 */

 /*  
      CHANGELOG
 0.01 - 20.06.2017 20:55
 -> Initial
 0.15 - 22.06.2017 19:00
 -> Define HDQ Addresses
 -> Add Read Command
 
 */

/* INCLUDES */
 
#include <HDQ.h>
#include <GOFi2cOLED.h>

/* PIN CONFIG */

/* DEFINE */

#define ver "0.15_22.06.2017_19:00"

uint8_t BYT1;
uint8_t BYT2;

//CMDS
#define CNTL 0x00,0x01
#define AR 0x02,0x03
#define ARTTE 0x04,0x05
#define TEMP 0x06,0x07
#define VOLT 0x08,0x09
#define FLAGS 0x0a,0x0b
#define NAC 0x0c,0x0d
#define FAC 0x0e,0x0f
#define RM 0x10,0x11
#define FCC 0x12,0x13
#define AI 0x14,0x15
#define TTE 0x16,0x17
#define TTF 0x18,0x19
#define SI 0x1a,0x1b
#define STTE 0x1c 0x1d
#define MLI 0x1e,0x1f
#define MLTTE 0x20,0x21
#define AE 0x22,0x23
#define AP 0x24,0x25
#define TTECP 0x26,0x27
#define CC 0x2a,0x2b
#define SOC 0x2c,0x2d
//extCMDS
#define DCAP 0x3c,0x3d
#define DFCLS 0x3e
#define DFBLK 0x3f
#define ADF 
#define ACKSDFD
#define DFD
#define DFDCKS 0x60
#define DFDCNTL 0x61
#define DNAMELEN 0x62,0xFF
#define DNAME
//CNTLcmds
#define CONTROL_STATUS
#define DEVICE_TYPE
#define FW_VERSION
#define HW_VERSION
#define DF_CHECKSUM
#define RESET_DATA
#define PREV_MACWRITE
#define CHEM_ID
#define SET_FULLSLEEP
#define SET_HIBERNATE
#define CLEAR_HIBERNATE
#define SET_SHUTDOWN
#define CLEAR_SHUTDOWN
#define SEALED
#define IT_ENABLE
#define CAL_MODE
#define RESET

HDQ HDQ(7); 

void ReadDname(){
char BYTT;

BYT1 = HDQ.read(0x63);
BYTT = BYT1 - 1 ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x64);
BYTT = BYT1  ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x65);
BYTT = BYT1 - 1 ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x66);
BYTT = BYT1  ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x67);
BYTT = BYT1 - 1 ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x68);
BYTT = BYT1  ;
Serial.print(BYTT);

BYT1 = HDQ.read(0x69);
BYTT = BYT1 - 1 ;
Serial.print(BYTT);




} 

int read2(uint8_t BYTL,uint8_t BYTH){

BYT1 = HDQ.write(0x0, 0x01);
BYT2 = HDQ.write(0x1, 0x00);
BYT1 = HDQ.read(BYTL);
BYT2 = HDQ.read(BYTH);

if(BYTH==0xFF){
  return BYT1;
 }else{
  return (BYT2 << 8) | BYT1;
  }



} 

void read1(){

}

void setup() {
  Serial.begin(115200);
  Serial.println("HDQ Battery Reader");
  Serial.print("Version:");
  Serial.println(ver);
}



void loop() {

/* ATRate */
  Serial.print("AT Rate:");
  Serial.print(read2(AR));
  Serial.println("mA");
/* ATRateTimeToEmpty */
  Serial.print("AT Rate TTE:");
  Serial.print(read2(ARTTE));
  Serial.println(" mins");
/* Temperature (CHK) */
  BYT1 = HDQ.read(6);
  BYT2 = HDQ.read(7);
  int tempK = word(BYT2, BYT1);
  float tempC = (tempK-2731)/10;
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(char(176));
  Serial.println("C");
/* Voltage */
  Serial.print("Voltage:");
  Serial.print(read2(VOLT));
  Serial.println("mV");
/* Flags (WIP) */
  Serial.print("Voltage:");
  Serial.print(read2(FLAGS));
  Serial.println("mV");  
/* NominalAvailableCapacity (CHK) */
  Serial.print("Nominal Available Capacity:");
  Serial.print(read2(NAC));
  Serial.println("mAh"); 
/* FullAvailableCapacity (CHK) */
  Serial.print("Full Available Capacity:");
  Serial.print(read2(FAC));
  Serial.println("mAh"); 
/* RemainingCapacity (CHK) */
  Serial.print("Remaining Capacity:");
  Serial.print(read2(RM));
  Serial.println("mAh"); 
/* FullChargeCapacity (CHK) */
  Serial.print("Full Charge Capacity:");
  Serial.print(read2(FCC));
  Serial.println("mAh");   
/* AverageCurrent (CHK) */
  Serial.print("Average Current:");
  Serial.print(read2(AI));
  Serial.println("mA");     
/* TimeToEmpty (CHK) */  //Going to add function to recognize if charging or not
  Serial.print("Time To Empty:");
  Serial.print(read2(TTE));
  Serial.println("Minutes");   
/* TimeToFull (CHK) */  //Going to add function to recognize if charging or not
  Serial.print("Time To Full:");
  Serial.print(read2(TTF));
  Serial.println("Minutes");     





  Serial.println("");
  delay(2000);
  
}




