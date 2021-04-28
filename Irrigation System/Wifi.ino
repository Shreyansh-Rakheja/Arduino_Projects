  #define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "_7drWkkDoLKV2hH1p887DEQvhR-8U5-h";
char ssid[] = "*_*";
char pass[] = "jaimatadi";
char cmd_arr1[100];
int cmd_count1;
int Soil = 0;
int led = D1;


//*****************************************************************
void serial_get_command()
{
char inchar=0;
  if(Serial.available() > 0)
  {
    inchar = Serial.read();    
    if(inchar == '<')
    {
      cmd_count1=0;
      while(inchar != '>' && cmd_count1<80)
      {
        if(Serial.available() > 0)
        {
          inchar = Serial.read();
          cmd_arr1[cmd_count1++] = inchar;
          cmd_arr1[cmd_count1] = '\0';
        }        
      }
      if(inchar == '>')
      {
        cmd_count1--;
        cmd_arr1[cmd_count1] = '\0';
        
        if(cmd_arr1[0]=='A')
        {cmd_arr1[0]='0';Soil = atof(cmd_arr1);Blynk.virtualWrite(V0,Soil);}
        else
        {
          
        }
      }
    }
 }
}
//*****************************************************************
BLYNK_CONNECTED()
{
  digitalWrite(led, HIGH);
}
//*****************************************************************

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(led, OUTPUT);digitalWrite(led, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() 
{
  if(!Blynk.connected())
  {
    Serial.println("Reconnecting ... ");
    digitalWrite(led, LOW);
    Blynk.connect();
  }
  Blynk.run();
  serial_get_command();
}
