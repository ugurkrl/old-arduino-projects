#include <DHT_U.h>
#include <DHT.h>
#include <TimeLib.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
/*Pinout*/
int D7 = 2;
int D6 = 3;
int D5 = 4;
int D4 = 5;
int E = 6;
int RS = 7;
int lcdled = 11;
int lcdbrightness;
int but0 = A3;
int but1 = 10;
int but2 = 12;
int but3 = 13;
int cache1 = 0;
int cache2 = 0;
int cache3 = 0;
int cache4 = 16;
int cursor[13] = {0,2,2,2,2,2,0,1,0,2,2,2,1};
int brght[24] = { 120,120,120,120,120,120,120,120,150,200,200,200,200,200,200,200,200,200,200,200,200,200,120,120 };
boolean buthinc;
boolean buthdec;
boolean butminc;
boolean butmdec;
int tmst = 0;
boolean yrst = 0;
boolean dtset = 0;
#define DHTPIN 8 
#define DHTTYPE DHT11
/*Ints*/
String months[13]= {"","Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik" };



/*Define LCD Pins*/
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

tmElements_t tm;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
	/*Pinmode*/
	pinMode(lcdled, OUTPUT);
	pinMode(but0 , INPUT);
	pinMode(but1, INPUT);
	pinMode(but2, INPUT);
	pinMode(but3, INPUT);
	analogWrite(lcdled, lcdbrightness);
	Serial.begin(9600);
	lcd.begin(16, 2);
	
	dht.begin();


}

void loop()
{
	
	RTC.read(tm);
	lcd.setCursor(cursor[tm.Month], 0);
	lcd.print(tm.Day);
	lcd.print(" ");
	lcd.print(months[tm.Month]);
	lcd.print(" ");
	lcd.print(tmYearToCalendar(tm.Year));
	lcd.setCursor(13, 2);
	lcd.print(dht.readTemperature(),0);
	lcd.print("C");
	lcd.setCursor(0, 2);
	lcd.print("%");
	lcd.print(dht.readHumidity(),0);
	lcd.setCursor(4, 2);
	print2digits(tm.Hour);
	lcd.print(":");
	print2digits(tm.Minute);
	lcd.print(":");
	print2digits(tm.Second);
	analogWrite(lcdled , brght[tm.Hour]);
	buthinc = digitalRead(but0);
	buthdec = digitalRead(but1);
	butminc = digitalRead(but3);
	butmdec = digitalRead(but2);
	if (buthinc == 1 && butminc == 1 ) {
		tmst++;
		if (tmst >= 3) {
			tmst = 0;
			
		}
		
		delay(1000);
		lcd.clear();
		
	}
	/*TIME*/
	if (buthinc==1 && tmst==0) {
		
			cache1 = tm.Hour + 1;
			if (cache1 >= 24) {
				cache1 = 0;
			}
			cache2 = tm.Minute;
			cache3 = tm.Second;
			settimefromcache();
		
		} 
	if (buthdec==1  && tmst==0 ) {
		cache1 = tm.Hour - 1;
		if (cache1 < 0) {
			cache1 = 24;
		}
		cache2 = tm.Minute;
		cache3 = tm.Second;
		settimefromcache();
	}
	if (butminc==1  && tmst==0 ) {
		cache2 = tm.Minute + 1;
		if (cache2 >= 60) {
			cache2 = 0;
		}
		cache1 = tm.Hour;
		cache3 = tm.Second;
		settimefromcache();
	}
	if (butmdec==1 && tmst==0 ) {
		cache2 = tm.Minute - 1;
		if (cache2 < 0) {
			cache2 = 60;
		}
		cache1 = tm.Hour;
		cache3 = tm.Second;
		settimefromcache();
	}
	/*DATE*/
	if (buthinc == 1 && tmst == 1) {

		cache2 = tm.Day + 1;
		if (cache2 > 31) {
			cache2 = 1;
		}
		cache1 = tm.Wday;
		cache3 = tm.Month;
		setdatefromcache();

	}
	if (buthdec == 1 && tmst == 1) {
		cache2 = tm.Day - 1;
		if (cache2 < 1) {
			cache2 = 31;
		}
		cache1 = tm.Wday;
		cache3 = tm.Month;
		setdatefromcache();
	}
	if (butminc == 1 && tmst == 1) {

		cache3 = tm.Month + 1;
		if (cache3 > 12) {
			cache3 = 1;
		}
		cache1 = tm.Wday;
		cache2 = tm.Day;
		setdatefromcache();

	}
	if (butmdec == 1 && tmst == 1) {
		cache3 = tm.Month - 1;
		if (cache3 < 1) {
			cache3 = 12;
		}
		cache1 = tm.Wday;
		cache2 = tm.Day;
		setdatefromcache();
	}
	/*YEAR*/
	if (buthinc == 1 && tmst == 2) {
		
		cache4 = cache4 +1;
		cache1 = cache4;
	
		setyrfromcache();

	}
	if (buthdec == 1 && tmst == 2) {
		cache4 = cache4 - 1;
		cache1 = cache4;

		setyrfromcache();

	}

	
	
	if (tmst == 1) {
		lcd.setCursor(0, 0);
		lcd.print("D");
	}
		if (tmst == 2) {
			lcd.setCursor(0, 0);
			lcd.print("Y");
	}
		if (tmst == 0) {
			lcd.setCursor(0, 0);
		
		 }
		delay(1000);
}
byte decToBcd(byte val) {
	return ((val / 10 * 16) + (val % 10));
}
byte bcdToDec(byte val) {
	return ((val / 16 * 10) + (val % 16));
}

void settimefromcache() {
	Wire.beginTransmission(0x68);
	Wire.write(byte(0));
	Wire.write(decToBcd(cache3)); //sec
	Wire.write(decToBcd(cache2)); //min
	Wire.write(decToBcd(cache1)); //hr
	Wire.write(byte(0));
	Wire.endTransmission();
}
void setdatefromcache()
{
	Wire.beginTransmission(0x68);
	Wire.write(byte(3));
	Wire.write(decToBcd(cache1)); //dow
	Wire.write(decToBcd(cache2)); //dom
	Wire.write(decToBcd(cache3)); //mo
	Wire.endTransmission();
}
void setyrfromcache()
{
	Wire.beginTransmission(0x68);
	Wire.write(byte(6));
	Wire.write(decToBcd(cache1)); //yr
	Wire.endTransmission();
	
}

void print2digits(int number) {
	if (number >= 0 && number < 10) {
		lcd.print('0');
	}
	lcd.print(number);
}