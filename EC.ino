#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
 
#define RE 8
#define DE 7
 
const byte ec[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};
const byte salinity[] = {0x01, 0x03, 0x00, 0x14, 0x00, 0x01, 0xC4, 0x0E};
byte values[8];

 
SoftwareSerial mod(2, 3);
  
void setup()
{
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}
 
void loop()
{
/**************Soil EC Reading*******************/  
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
 
  if (mod.write(ec, sizeof(ec)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++)
    {
      values[i] = mod.read();
      //Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  int soil_ec = int(values[3]<<8|values[4]);
  delay(1000);
/**************Soil Salinity Reading*******************/ 
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(salinity, sizeof(salinity)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++)
    {
      values[i] = mod.read();
      //Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  int soil_salinity = int(values[4]);
  delay(1000);
 
  
  Serial.print("Soil EC: ");
  Serial.println(soil_ec);
  
  Serial.print("Soil Salinity: ");
  Serial.println(soil_salinity);
 
  delay(2000);
}
