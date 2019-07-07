
#define BLYNK_PRINT Serial

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "@#%%@$@$@$@%%@cf"; //obtain from blynk app


char ssid[] = "newpk";
char pass[] = "12345687";

void setup()
{
 
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  connectWiFi();
  
 
}

void loop()
{
  Blynk.run();
}



void connectWiFi()
{

  lcd.begin(5,4);
  //lcd.begin(0, 2); pin 0-SDA 2-SCL 
 lcd.backlight();
 

  lcd.setCursor(0, 0);
  lcd.print("Blynk Server");
   lcd.setCursor(0, 1);
   lcd.print("Online");
  
}
