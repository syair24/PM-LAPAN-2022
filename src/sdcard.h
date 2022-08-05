#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

unsigned long tes1 = 0;
unsigned long tes2 = 1000;
unsigned long tes3 = 0;

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
unsigned long tambah = 0;

String savedata,tgl,jam,jamlcd,pm10,pm25;

#define SD_CS 5

void initSDCard()
{
    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");

        return;
    }

    Serial.println("SD opened!");
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }
    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}


void SDopen111()
{

File file = SD.open("/DataPM.txt");
  if (!file)
  {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/DataPM.txt", "Data PM Lapan\r\n");
  }
  else
  {
    Serial.println("File already exists");
  }
  file.close();
}