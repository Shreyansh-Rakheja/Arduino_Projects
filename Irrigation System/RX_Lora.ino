/* 1byte LORa SX1278 TRANSMITTER example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut97.php
 * Code: http://electronoobs.com/eng_arduino_tut97_code1.php
 * Scheamtic: http://electronoobs.com/eng_arduino_tut97_sch1.php
 * Youtube Channel: http://www.youtube/c/electronoobs   
 * 
  Module SX1278 // Arduino UNO/NANO    
    GND         ->   GND
    Vcc         ->   3.3V
    MISO        ->   D12
    MOSI        ->   D11     
    SLCK        ->   D13
    Nss         ->   D10
    Di00        ->   D2
    RST         ->   D9      
 */

#include <SPI.h>
#include <LoRa.h>
int LED = 3;
String inString = "";    // string to hold input
int val = 0;
unsigned long previousMillis=0;


void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString.toInt();       
    }
    inString = "";     
    LoRa.packetRssi();    
  }
  if(millis() - previousMillis > 1000)
  {
    Serial.print("<A");Serial.print(val);Serial.print(">");Serial.println("");  
    previousMillis = millis();
  }

  
}
