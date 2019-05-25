#include <Wire.h>
#include <HDQ.h>
HDQ HDQ(7); // Arduino digital pin 7
#include <GOFi2cOLED.h>
#define butdec 2
#define butinc 3
#define butrev 8
#define butmod 9
int butdecstat;
int butincstat;
int butrevstat;
int butmodstat;
int halfsec=0;
bool screv=false;
int sec=0;
int stat=0;
int vmap;
int pixy;
int pixx;

GOFi2cOLED Screen;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   void setup(){
  Serial.begin(115200);
  Serial.println("Hello!");
  Screen.init(0x3C);
  Screen.clearDisplay();
  Screen.clearDisplay();
  Screen.drawRect( 0, 0,  128, 64, WHITE );
  Screen.println("");
  Screen.println("     HDQ MONITOR");
  Screen.setCursor(40,44);
  Screen.setTextSize(2);
  Screen.print("V0.9");
  Screen.setCursor(26,22);
  Screen.setTextSize(1);
  Screen.print("Press Any Key");
  Screen.display();


  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  while(digitalRead(2) == LOW && digitalRead(3) == LOW){};
  Screen.clearDisplay();
}
void loop(){
  uint8_t BYT1, BYT2;
  int dev, hard, major, minor;
    Serial.println("");
    //Serial.print(BYT2, HEX); Serial.println(BYT1, HEX);
    




    /* Current charge in mAH */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x10);
    BYT2 = HDQ.read(0x11);
    int RM=word(BYT2,BYT1);
    Serial.print("Remaining Capacity: ");
    Serial.print(word(BYT2, BYT1), DEC);
    Serial.println(" mAH");
    
    /* Full charge capacity mAH */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x12);
    BYT2 = HDQ.read(0x13);
    Serial.print("Full Charge Capacity: ");
    Serial.print(word(BYT2, BYT1), DEC);
    Serial.println(" mAH");
  
    /* Design capacity mAH */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x3c);
    BYT2 = HDQ.read(0x3d);
    Serial.print("Design Capacity: ");
    Serial.print(word(BYT2, BYT1), DEC);
    Serial.println(" mAH");

    /* Passed Chg mAH */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x34);
    BYT2 = HDQ.read(0x35);
    Serial.print("Passed Charge: ");
    int pssdchg = (word(BYT2,BYT1));
    Serial.print(pssdchg, DEC);
    Serial.println(" mAH");
    
    /* Time to Empty Minutes */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x16);
    BYT2 = HDQ.read(0x17);
    int tto = word(BYT2, BYT1);
    Serial.print("Time to empty: ");
    if(tto == -1){
      Serial.println("N/A, not discharging");
    }else{
      Serial.print(tto, DEC);
      Serial.println(" minutes");
    }
    
    /* Time to Full Minutes */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x18);
    BYT2 = HDQ.read(0x19);
    int ttf = word(BYT2, BYT1);
    Serial.print("Time to full: ");
    if(ttf == -1){
      Serial.println("N/A, not charging");
    }else{
      Serial.print(ttf, DEC);
      Serial.println(" minutes");
    }
  
    /* State of Charge % */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x2c);
    BYT2 = HDQ.read(0x2d);
    int soc = word(BYT2,BYT1);
    Serial.print("State of Charge: ");
    Serial.print(word(BYT2, BYT1), DEC);
    Serial.println(char(37));

    /* Voltage mV */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(8);
    BYT2 = HDQ.read(9);
    int mvolts = word(BYT2, BYT1);
    float volts = (mvolts*0.001);
    Serial.print("Battery Voltage: ");
    Serial.print(volts);
    Serial.print("V (");
    Serial.print(mvolts);
    Serial.println("mV)");

    
    /* Current mA */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x14);
    BYT2 = HDQ.read(0x15);
    Serial.print("Current: ");
    int dschg = word(BYT2,BYT1);
    Serial.print(dschg, DEC);
    Serial.println(" mA");
    

    /* Charge Cycle Count */
    BYT1 = HDQ.write(0x0, 0x01);
    BYT2 = HDQ.write(0x1, 0x00);
    BYT1 = HDQ.read(0x2a);
    BYT2 = HDQ.read(0x2b);
    Serial.print("Charge Cycle Count: ");
    Serial.print(word(BYT2, BYT1), DEC);
    Serial.println(" times");


  butrevstat=digitalRead(butrev);
  butmodstat=digitalRead(butmod);
  if(screv==true && butrevstat==1  ){
    Screen.setNormalDisplay();
    screv=false;
    butrevstat=0;
  }
  butmodstat=digitalRead(butmod);
  if(screv==false && butrevstat==1 ){
    Screen.setInverseDisplay();
    screv=true;
  }
  
  vmap=dschg;
  pixy=map(vmap, 150, 1300, 63, 34);
  if(pixx == 127){
    pixx = 1;
  }
  
  Screen.clearArea( 0, 0, 128, 32);
  Screen.setCursor(0,0);
  Screen.print("Voltage:");
  Screen.print(volts);
  Screen.print("V");

  Screen.setCursor(0,8);
  Screen.print("Current:");
  Screen.print(dschg);
  Screen.print("mA");

  Screen.setCursor(0,16);
  Screen.print("PCHG:");
  Screen.print(-pssdchg);
  Screen.print("mAh");

  Screen.setCursor( 88,8);
  Screen.print(RM);
  Screen.print("mAh");
  Screen.setCursor(102,16);
  Screen.print(soc);
  Screen.print("%");

 
  Screen.drawRect(0,32,128,32,WHITE);
  Screen.drawPixel(pixx,pixy,WHITE); //For line Graph
  Screen.drawLine( pixx+1,33, pixx+1, 62, BLACK); //Both for line and bargraph
  Screen.drawLine( pixx+2,33, pixx+2, 62, BLACK); //Both for line and bargraph
  Screen.drawLine( pixx,pixy+1, pixx, 63, BLACK); 


  Screen.display();


    halfsec = halfsec +1;   

   if(halfsec == 22){
     pixx = pixx+1;
     halfsec = 0;
   }
   if(sec == 3){
   sec = 0;
   }
  sec = sec + 1;



  delay(50);
  
}



