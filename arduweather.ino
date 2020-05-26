#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"
Adafruit_BME280 bme;


File data;
int meteoCount = 1;
RTC_DS1307 rtc;
const int chipSelect = 10;
int timestring;
void setup() {
    Serial.begin(9600);
   Serial.println("Stazione meteo By Marco Strozzi https://potassio83.it");
   Wire.begin();
  delay(3000);
  bme.begin(0x76);
  pinMode(10, OUTPUT);
  SD.begin(4);
  Wire.begin();
  

  data = SD.open("dati.txt", FILE_WRITE);
  data.println("Temperature:,Pressure:,Humidity:,Time:,Count no.");
  data.close();
}
  
void loop() {
  data = SD.open("MetData.txt", FILE_WRITE);
  DateTime now = rtc.now(); 
  data.print(" | ");
  data.print(bme.readTemperature());
  data.print(" | ");
  data.print(bme.readPressure() / 100.0F);
  data.print(" | ");
  data.print(bme.readHumidity());
  data.print(" |    ");
  data.print(now.day());
  data.print("/");
  data.print(now.month());
  data.print("/");
  data.print(now.year());
  data.print("    ");
  data.print(now.hour());
  data.print(":");
  data.print(now.minute());
  data.print(":");
  data.print(now.second());
  data.print("   Count No.");
  data.print(meteoCount);
  data.println("");
  
  data.close();  
  Serial.println("Scrittura su SD effettuata correttamente");
  meteoCount++;
  
  delay(60000);
  
}
