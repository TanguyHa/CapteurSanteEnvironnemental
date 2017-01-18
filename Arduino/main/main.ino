#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#define DHTPIN 2


File Dhtemp;
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(10, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(15)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  dht.begin();
}
void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Dhtemp = SD.open("Temp.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (Dhtemp || 1) {
    //Le code qui suit est addapter pour les split pour la partie Qt:
    Serial.print("D");
    Serial.print("H:");
    Serial.print(h);
    Serial.print("T:");
    Serial.print(t);
    //Ecriture dans la carte SD
   
    Dhtemp.print("Humidity:  ");
    Dhtemp.print(h);
    Dhtemp.print("%\t");
    Dhtemp.print("Temperature:   ");
    Dhtemp.print(t);
    Dhtemp.println("*C");
    // close the file:
    Dhtemp.close();
    Serial.flush();
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Temp.txt");
  }
}

