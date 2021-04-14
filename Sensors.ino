//6 grey scales --> 6 sounds (Blues Scals) maybe pentatonic -

//DF PLAYER LIBRARY
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//LIGHT SENSOR LIBRARY
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
int led = 5;



void setup() {
  //LIGHT SENSOR SETUP
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
  delay(1000);

  pinMode(led, OUTPUT);


  //DF PLAYER SETUP
  mySoftwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first first notes once when started up
}



void loop() {

  analogWrite(led, 255); //LIGHT SENSOR PART

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  int lightReading = lux;
  delay(50);
/*
  //NOTE PLAYING PART
  //if (lightReading < 9) {
   // myDFPlayer.playMp3Folder(1);

 // }
  //if ((lightReading > 9) && (lightReading < 12)){
  //myDFPlayer.playMp3Folder(2);
  // }
  //if ((lightReading > 12) && (lightReading < 50)){
 // myDFPlayer.playMp3Folder(3);
 //  }
  // if ((lightReading > 50) && (lightReading < 100)){
  //  myDFPlayer.playMp3Folder(4);
  // }
  // if ((lightReading > 1) && (lightReading < 1)){
  // myDFPlayer.playMp3Folder(5);
  // }
  if (lightReading > 140) {
    myDFPlayer.playMp3Folder(6);
    
  }*/
 
}
