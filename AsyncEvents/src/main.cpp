// ****************************************************************** 
// COMP-10184 
// External LED Wiring, PIR Sensor Test Program 
// 
// @author Mohawk College 
 
#include <Arduino.h> 
#include <ESP8266WiFi.h>
 
// pin assignments for external LEDs 
#define PIN_LED_GREEN   D1 
#define PIN_LED_YELLOW  D2 
#define PIN_LED_RED     D3 
 
// pin assignment for PIR input 
#define PIN_PIR         D5  

#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)


WiFiServer server(80); 
void setup() { 
  // setup LED outputs 
  pinMode(PIN_LED_GREEN, OUTPUT); 
  pinMode(PIN_LED_YELLOW, OUTPUT); 
  pinMode(PIN_LED_RED, OUTPUT); 
 
  // setup PIR input 
  pinMode(PIN_PIR, INPUT); 
 
  // built-in LED 
  pinMode(LED_BUILTIN, OUTPUT); 

  Serial.println("Student Number: 000802106");
  Serial.println("Name: Rhagavy Rakulan, App: AsyncEvents");

  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    digitalWrite(PIN_LED_YELLOW, HIGH); 
    digitalWrite(PIN_LED_GREEN, LOW); 
    digitalWrite(PIN_LED_RED, LOW); 
  } 
  Serial.println("connected to Wifi"); 
 
  server.begin(); 

} 

volatile bool motionFlag;

void IRAM_ATTR isr(){
  motionFlag = true;
}


int motion = 0;
void loop() { 

  //check to see if connected to wifi
  if(WiFi.status()){
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_LED_YELLOW, LOW); 
    //print IP address
    Serial.printf("\nWeb server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
  }


  int motionSensor = digitalRead(PIN_PIR);
  //motion detected
  if(PIN_PIR == 1){
    Serial.println("Motion detected");
    //turn on Red led for 2 seconds
    digitalWrite(PIN_LED_RED, HIGH);
    
  }


  // set the fields with the values
  ThingSpeak.setField(1, motion);



  // cycle through LED colours, one at a time.. 
  // GREEN ON 
  // digitalWrite(PIN_LED_GREEN, HIGH); 
  // digitalWrite(PIN_LED_YELLOW, LOW); 
  // digitalWrite(PIN_LED_RED, LOW); 
  // delay(200); 
  // // YELLOW 
  // digitalWrite(PIN_LED_GREEN, LOW); 
  // digitalWrite(PIN_LED_YELLOW, HIGH); 
  // digitalWrite(PIN_LED_RED, LOW); 
  // delay(200); 
  // // RED 
  // digitalWrite(PIN_LED_GREEN, LOW); 
  // digitalWrite(PIN_LED_YELLOW, LOW); 
  // digitalWrite(PIN_LED_RED, HIGH); 
  // delay(200); 
 
  // echo PIR input to built-in LED OUTPUT (note: invert the sense of the PIR sensor!) 
  digitalWrite(LED_BUILTIN, !digitalRead(PIN_PIR)); 
} 