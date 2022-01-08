#include "MQ135.h"
#include <SoftwareSerial.h>


const int analogPin=0;

MQ135 gasSensor = MQ135(analogPin);
float ppm;

int alarm=2;
int sensor=A0;
int greenLed=3;
int redLed=4;

SoftwareSerial ESP_Serial(5, 6);

void setup() {
  Serial.begin(9600);
  ESP_Serial.begin(9600);
  pinMode(alarm,OUTPUT);
  pinMode(analogPin,INPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  

}

void loop() {
 ppm=gasSensor.getPPM();
 Serial.print("PPM:");
 Serial.println(ppm);
 ESP_Serial.println(ppm);
 if (ppm>75) 
 
 /*400ppm – 750ppm: Good for health
  750 ppm – 1200 ppm: Take care
  1200 ppm (and above): Harmful to health*/
 {
    tone(alarm, 1000, 100);
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
 }
 else
 {
    noTone(alarm);
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
    
 }
  
 delay(200);
}
