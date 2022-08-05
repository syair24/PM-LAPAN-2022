#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
 #include <SPI.h>
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

char nama2hari[7][12] = {"Min", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};


/* SENSOR DSM501A */



int pin2 = 34;
int pin1 = 35;
unsigned long duration1;
unsigned long duration2;

float ratio1 = 0;
float ratio2 = 0;
float concentration1 = 0;
float concentration2 = 0;

void dsm501a()
{

 duration1 = pulseIn(pin1, LOW);
    duration2 = pulseIn(pin2, LOW);

        tes1 = tes1 + duration1;
    tes3 = tes3 + duration2;

        ratio1 = tes1 / (tes2 * 10.0);                                // Integer percentage 0=>100
        concentration1 = 0.001915 * pow(ratio2, 3) + 0.09522 * ratio2 + 0.00000; 

        ratio2 = tes3 / (tes2 * 10.0);                                // Integer percentage 0=>100
        concentration2 = 0.001915 * pow(ratio1, 3) + 0.09522 * ratio1 + 0.00000;  // using spec sheet curve //

         Serial.print("PM10 ");
        
        Serial.print("concentration1 = ");
        Serial.print(concentration1);
        Serial.println(" mg/m3 ");

         pm10 = String("pm10")+ " = " +  String(concentration1);

        Serial.print("PM2.5");
        Serial.print("concentration2 = ");
        Serial.print(concentration2);
        Serial.println(" mg/m3 ");
        
         pm25 = String("pm25")+ " = " +  String(concentration2);

        if (concentration1 < 50) {
            Serial.println("CLEAN");
        }

        
        if (concentration1 > 51 && concentration1 < 150) {
            Serial.println("GOOD");

        }

        if (concentration1 > 151 && concentration1 < 350) {
            Serial.println("ACCEPTABLE");

        }
        if (concentration1 > 351 && concentration1 < 420) {
            Serial.println("HEAVY");

        }

        if (concentration1 > 420) {
            Serial.println("HAZARD");

        }
        tes1 = 0.00;
        tes3 = 0.00;
}

void lcdpm(){
lcd.setCursor(7,0);
lcd.print("PM10");
lcd.setCursor(7,1);
lcd.print("PM25");

    lcd.setCursor(12,0);
    lcd.print(concentration1);
    lcd.setCursor(12,1);
    lcd.print(concentration2); 
}



void datetimeprint()
{

      DateTime now = rtc.now();
    Serial.print("JAM:");
    Serial.print(" ");
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.print(now.second());
    Serial.print("  ");

    Serial.print("TGL:");
   Serial.print(" ");
    //lcd.print(nama2hari[now.namahari()]);
    Serial.print(" ");
    Serial.print(now.day());
   Serial.print('/');
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.year());
   Serial.println("  ");   

  
   tgl = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
   jam = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

   jamlcd = String(now.hour()) + ":" + String(now.minute());
   lcd.setCursor(0,0);
   lcd.print(jamlcd);
}

