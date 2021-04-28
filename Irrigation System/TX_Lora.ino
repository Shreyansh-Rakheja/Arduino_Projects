int Pump = 8;
const int AirValue = 900;   //you need to replace this value with Value_1
const int WaterValue = 770;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;
#include <SPI.h>
#include <LoRa.h>
unsigned long previousMillis=0;


void setup() 
{
  Serial.begin(9600);
  pinMode(Pump , OUTPUT);
  digitalWrite(Pump , HIGH); // Relay OFF  
  //while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(20);
}

void Soil_sensor()
{
 soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
 Serial.println(soilMoistureValue);
 soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
 if(soilmoisturepercent >= 100){soilmoisturepercent = 100;Serial.print("Soil Map : "); Serial.print(soilmoisturepercent);Serial.println("%");}
 else if(soilmoisturepercent <=0){soilmoisturepercent = 0; Serial.print("Soil Map : "); Serial.print(soilmoisturepercent);Serial.println("%");}
 else if(soilmoisturepercent >0 && soilmoisturepercent < 100){Serial.print("Soil Map : "); Serial.print(soilmoisturepercent);Serial.println("%");} 
 LoRa.beginPacket();
    LoRa.print(soilmoisturepercent);
    LoRa.endPacket();
    Serial.println("send data ");
 if(soilmoisturepercent > 0 && soilmoisturepercent < 5)
 {
   // Pump Off
   digitalWrite(Pump , HIGH); // Relay OFF
   delay(100);  
 }
 else if (soilmoisturepercent > 5 && soilmoisturepercent < 65)
 {
  // Pump ON
  digitalWrite(Pump , LOW); // Relay OFF
  delay(100);
 }
 else if (soilmoisturepercent > 65)
 {
  // Pump Off
  digitalWrite(Pump , HIGH); // Relay OFF
  delay(100);
 }
 
}
void loop() 
{
  Soil_sensor();
  /*if(millis() - previousMillis > 3000)
  {
    LoRa.beginPacket();
    LoRa.print(soilmoisturepercent);
    LoRa.endPacket();
    Serial.println("send data ");
    previousMillis = millis();
  }*/
  delay(2000);
}
