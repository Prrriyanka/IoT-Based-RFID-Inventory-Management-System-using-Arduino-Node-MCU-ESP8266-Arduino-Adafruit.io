#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#define WLAN_SSID       "Joshi"
#define WLAN_PASS       "28101967"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "TECHNOWEIRDS"
#define AIO_KEY       "aio_nxyD09u3ab6jZsFI6IxomJEV5zDC"

WiFiClient client ;

Adafruit_MQTT_Client mqtt(&client , AIO_SERVER , AIO_SERVERPORT ,AIO_USERNAME, AIO_KEY) ;
Adafruit_MQTT_Publish at = Adafruit_MQTT_Publish(&mqtt , AIO_USERNAME "/feeds/rfid" ) ; 

char ID ;
void setup() {
  Serial.begin(115200);
  Serial.println(F("Adafruit IO Example"));
 Serial.println(); 
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);
 WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  // connect to adafruit io
 mqtt.connect();
}

void loop() {
 // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      mqtt.connect();
      
  }
  if ( Serial.available() ) { // Update and send only after 1 seconds
   char a = Serial.read();
   ID = a;  
   Serial.print(ID);
   if (! at.publish(ID)) {                     //Publish to Adafruit
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("Sent!"));
    }
   }
}
