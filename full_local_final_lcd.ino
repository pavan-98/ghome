#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "newpk";
const char* password = "12345687";
String  command =""; 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


 
int relay1 = 0;
int relay2 = 2;
int relay3 = 14;
int relay4 = 12;

void setup()
{
  Serial.begin(115200);

  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);  
  pinMode(relay3, OUTPUT);  
  pinMode(relay4, OUTPUT);  

  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);

   
  connectWiFi();
  server.begin();
}

void loop()
{
    client = server.available();
    if (!client) return; 
    command = checkClient ();

         if (command == "r1on"  || command == "turn on relay 1"    || command == "relay 1 on")        digitalWrite(relay1,0);
    else if (command == "r1off" || command == "turn off relay 1" || command == "relay 1 off")     digitalWrite(relay1,1);
    else if (command == "r2on"  || command == "turn on relay 2"    || command == "relay 2 on")      digitalWrite(relay2,0);     
    else if (command == "r2off" || command == "turn off relay 2" || command == "relay 2 off")   digitalWrite(relay2,1);
    else if (command == "r3on"  || command == "turn on relay 3"    || command == "relay 3 on")      digitalWrite(relay3,0);
    else if (command == "r3off" || command == "turn off relay 3" || command == "relay 3 off")   digitalWrite(relay3,1);
    else if (command == "r4on"  || command == "turn on relay 4"    || command == "relay 4 on")    digitalWrite(relay4,0);
    else if (command == "r4off" || command == "turn off relay 4" || command == "relay 4 off") digitalWrite(relay4,1);
    else if (command == "allon" || command == "Turn on all devices" || command == "all on") 
    {
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,LOW);
      digitalWrite(relay3,LOW);
      digitalWrite(relay4,LOW);
    }
    else if (command == "alloff" || command == "Turn off all devices" || command == "all off") 
    {
      digitalWrite(relay1,HIGH);
      digitalWrite(relay2,HIGH);
      digitalWrite(relay3,HIGH);
      digitalWrite(relay4,HIGH);
    }
    sendBackEcho(command); 
    command = "";
}


void connectWiFi()
{

  lcd.begin(5,4);
  //lcd.begin(0, 2); pin 0-SDA 2-SCL 
 lcd.backlight();
 

  
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));

  

  lcd.setCursor(0, 0);
  lcd.print("(PK) LocalIP is");
  lcd.setCursor(0, 1);
  lcd.print((WiFi.localIP()));
  
}

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}


void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 OK ");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
