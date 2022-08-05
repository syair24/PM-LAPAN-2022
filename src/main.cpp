#include <Arduino.h>
#include "sdcard.h"
#include "sensor.h"
#include <Wire.h> 




void setup() {
Serial.begin(9600);
    pinMode(34, INPUT);
    pinMode(35, INPUT);
lcd.init();
lcd.backlight();

 lcd.setCursor(6, 0);
  lcd.print(F("LAPAN"));
  lcd.setCursor(0, 1);
  lcd.print(F("Smkn 2 Pontianak"));
  delay(2000);
  lcd.clear();

initSDCard();

if (! rtc.begin()) 
  {
   Serial.print("RTC tidak tersedia");
    while (1);
  }
if (! rtc.isrunning()) 
  {
    Serial.print("RTC tidak berfungsi");
  }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//Update otomatis dari jam komputer
    //rtc.adjust(DateTime(2021, 11, 25, 17, 30, 0));// Atur waktu manual 

SDopen111();
}

void loop() {
 
  if ((millis() - lastTime) > timerDelay)
  {
    tambah++;
    dsm501a();
    lcdpm();
    datetimeprint();
    if (tambah == 56)
    {
      savedata = String(tgl) + "," + String(jam) + "," + String(pm10) + "," + String(pm25) + "\r\n";
      Serial.print("Saving data: ");
      Serial.println(savedata);


      // Append the data to file
      appendFile(SD, "/DataPM.txt", savedata.c_str());
      tambah = 0;
    }
    lastTime = millis();
  }


}