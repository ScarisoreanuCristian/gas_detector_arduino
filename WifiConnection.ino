
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
float ppm;


// WiFi parameters to be configured
const char* ssid = "DESKTOP-TBT28U4 9954"; // Write here your router's username
const char* password = "cristian"; // Write here your router's passward


// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "scarisoreanu_cristian"
#define AIO_KEY         "aio_TMIY45KXnXD8ei9fknZkh4KNQQDH" 

WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish PPM = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/PPM");

SoftwareSerial Arduino(D6,D5);

void setup(void)
{

  Serial.begin(9600);
  Arduino.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
   connect();
}
void connect() {
  Serial.print(F("Connecting to Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(10000);
  }
  Serial.println(F("Adafruit IO Connected!"));
}

void loop() {
  // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }

  ppm=Arduino.parseFloat();

if (! PPM.publish(ppm)) {                     //Publish to Adafruit
      Serial.println(F("Failed"));
    } 
    else {
      Serial.println(F("Sent!"));
      Serial.print("Parts per milion: ");
      Serial.println(ppm);
    }
delay(2000);
}
