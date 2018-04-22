#include "Nextion.h" 
#include "NexText.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


// Declare a text object [page id:0,component id:1, component name: "t0"]. 
NexText t1 = NexText(0, 2, "t1"); 
NexText t3 = NexText(0, 4, "t3"); 
NexText t5 = NexText(0, 6, "t5"); 
NexText t7 = NexText(0, 8, "t7"); 
NexText t9 = NexText(0, 10, "t9"); 
NexText t11 = NexText(0, 12, "t11"); 
NexText t13 = NexText(0, 14, "t13"); 
NexText t15 = NexText(0, 16, "t15"); 
NexText t17 = NexText(0, 18, "t17"); 

char buffer[100] = {0}; 
char buffer1[100] = {0};
uint16_t Value; 

IPAddress myip;

const char* ssid = "aaeon-asus";
const char* password = "aaeontcg";
int WiFi_LED = 13;  //GPIO13 (D7)

void setup(void) 
{ 
pinMode(WiFi_LED, OUTPUT);
digitalWrite(WiFi_LED, HIGH); // Wifi Disconnect 
Serial.begin(115200);
Serial.println("Booting");
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
Serial.println("Connection Failed! Rebooting...");
delay(5000);
ESP.restart();
//myip = WiFi.localIP();

sprintf(buffer1, WiFi.localIP().toString().c_str());
Serial.println(buffer1); 
}

ArduinoOTA.onStart([]() {
Serial.println("Start");
});
ArduinoOTA.onEnd([]() {
Serial.println("\nEnd");
});
ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
});
ArduinoOTA.onError([](ota_error_t error) {
Serial.printf("Error[%u]: ", error);
if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
else if (error == OTA_END_ERROR) Serial.println("End Failed");
});
ArduinoOTA.begin();
Serial.println("Ready");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

/* Set the baudrate which is for debug and communicate with Nextion screen. */
nexInit(); 
dbSerialPrintln("setup done"); 
Value = 60; 

}
void loop(void) 
{ 
Wifi_Check();  
ArduinoOTA.handle();
// Serial.println(Value);
memset(buffer,0,sizeof(buffer));
itoa(Value,buffer,10);
t3.setText(buffer); 
// inject your code to retrieve value from dht11
// set value you retrieved from your dht11
if (Value >0)
{
Value = Value -1;
}
else if (Value =1)
{
Value = 60;
} 

delay(100);
}

void Wifi_Check()
{

if ( WiFi.status() != WL_CONNECTED )
{ 
 digitalWrite(WiFi_LED, HIGH); // Wifi Disconnect 
}
else if ( WiFi.status() == WL_CONNECTED )
{
 digitalWrite(WiFi_LED, LOW);// Wifi Connect 
}
}
