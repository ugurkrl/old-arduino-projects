
#include <Wire.h>
#include <HDQ.h>


#include <GOFi2cOLED.h>
#define butdec 2
#define butinc 3
#define butrev 8
#define butmod 9
#define fet1 4
#define fet2 5
#define fet3 6
#define fet4 12
int butdecstat;
int butincstat;
int butrevstat;
int butmodstat;
int halfsec=0;
bool screv=false;
int sec=0;
float r;
float cap = 0;
float en = 0;
float entemp = 0;
int stat=0;
int vmap;
int pixy;
int pixx;
HDQ HDQ(7); // Arduino digital pin 7
GOFi2cOLED Screen;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   void setup(){
  Serial.begin(9600);
  Serial.println("Hello!");
  Serial.println("Current , Capacity , Energy , Voltage");
  Screen.init(0x3C);
  Screen.clearDisplay();
  Screen.clearDisplay();
  Screen.drawRect( 0, 0,  128, 64, WHITE );
  Screen.println("");
  Screen.println("     LI-ION Tester");
  Screen.setCursor(40,44);
  Screen.setTextSize(2);
  Screen.print("V1.2");
  Screen.setCursor(26,22);
  Screen.setTextSize(1);
  Screen.print("Press Any Key");
  Screen.display();


  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(fet1,OUTPUT);
  pinMode(fet2,OUTPUT);
  pinMode(fet3,OUTPUT);
  pinMode(fet4,OUTPUT);
  digitalWrite(fet1,HIGH);
  digitalWrite(fet2,HIGH);
  digitalWrite(fet3,HIGH);
  digitalWrite(fet4,HIGH);
  while(digitalRead(2) == LOW && digitalRead(3) == LOW){};
  Screen.clearDisplay();
}
void loop(){
  butdecstat=digitalRead(butdec);
  butincstat=digitalRead(butinc);
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
  if(butdecstat==1 && stat > 0 ){
  stat = stat -1;
    }
  if(butincstat==1 && stat < 4 ){
  stat = stat +1;
    }
   if(stat==0){
    r=999;
    digitalWrite(fet1,HIGH);
    digitalWrite(fet2,HIGH);
    digitalWrite(fet3,HIGH);
    digitalWrite(fet4,HIGH);
   }
   if(stat==1){
    r=22; 
    digitalWrite(fet1,LOW);
    digitalWrite(fet2,HIGH);
    digitalWrite(fet3,HIGH);
    digitalWrite(fet4,HIGH);
   }

   if(stat==2){
    r=5.6;
    digitalWrite(fet1,HIGH);
    digitalWrite(fet2,LOW);
    digitalWrite(fet3,HIGH);
    digitalWrite(fet4,HIGH);
   }
   if(stat==3){
    r=4.7;
    digitalWrite(fet1,HIGH);
    digitalWrite(fet2,HIGH);
    digitalWrite(fet3,LOW);
    digitalWrite(fet4,HIGH);
   }
   if(stat==4){
    r=2.2;
    digitalWrite(fet1,HIGH);
    digitalWrite(fet2,HIGH);
    digitalWrite(fet3,HIGH);
    digitalWrite(fet4,LOW);
   }


  
  int sense = analogRead(A3);
  float v = sense * (5.0 / 1023.0);
  float I = r / v; //V = i*r
  I = 1/I;
  cap = I + cap;
  entemp = I * v;
  en = entemp + en;
  vmap=v*1000;
  pixy=map(vmap, 3050, 3950, 63, 33);
  if(pixx == 128){
    pixx = 1;
  }
  
  Screen.clearArea( 0, 0, 128, 32);
  Screen.setTextSize(2);
  Screen.setTextColor(BLACK,WHITE);
  Screen.setCursor(0,0);
  Screen.print(stat);
  Screen.setTextColor(WHITE,BLACK);
  Screen.setTextSize(1);
  Screen.setCursor(14,0);
  Screen.print("Voltage:");
  Screen.print(v);
  Screen.print("V");
  if(stat==0){
    Screen.setTextColor(BLACK,WHITE);
    Screen.setCursor(104,0);
    Screen.print("DONE");
    Screen.setTextColor(WHITE,BLACK);
   }
  Screen.setCursor(14,8);
  Screen.print("R:");
  Screen.print(r);
  Screen.print((char)233);
  Screen.setCursor(86,8);
  Screen.print("I:");
  Screen.print(I);
  Screen.print("A");
  Screen.setCursor(0,16);
  Screen.print("Capacity:");
  Screen.print(cap/7200);
  Screen.print("Ah");
  Screen.setCursor(0,24);
  Screen.print("Energy:");
  Screen.print(en/7200);
  Screen.print("Wh");
  if(stat > 0){
    Screen.setTextColor(BLACK,WHITE);
    Screen.setCursor(104,16);
    Screen.print("LOAD");
    Screen.setTextColor(WHITE,BLACK);
   }
  Screen.drawRect(0,32,128,32,WHITE);
//  Screen.drawPixel(pixx,pixy,WHITE); //For line Graph
  Screen.drawLine( pixx+1,33, pixx+1, 62, BLACK); //Both for line and bargraph
  Screen.drawLine( pixx+2,33, pixx+2, 62, BLACK); //Both for line and bargraph
  Screen.drawLine( pixx,pixy, pixx, 63, WHITE); 
  if(stat==1 && v <= 3.1){
    r=999; 
    stat=0;
    digitalWrite(fet1,HIGH);
    digitalWrite(fet2,HIGH);
    digitalWrite(fet3,HIGH);
    digitalWrite(fet4,HIGH);

    }
    if(stat==2 && v <= 2.9){
     stat=1;
    }
    if(stat==3 && v <=2.9){
      stat=2;
    }
    if(stat==4 && v <=3.1){
      stat=3;
    }
   

  Screen.display();
    if(stat > 0){
    halfsec = halfsec +1;   
  }
   if(halfsec == 32){
     pixx = pixx+1;
     halfsec = 0;
   }
   if(sec == 3){
  Serial.print(I);
  Serial.print(",");
  Serial.print(cap/7200);
  Serial.print(",");
  Serial.print(en/7200);
  Serial.print(",");
  Serial.println(v);
    sec = 0;
   }
  sec = sec + 1;
  uint8_t BYT1, BYT2;
  int dev, firm, hard, major, minor;

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
    
  delay(500);
  
}



