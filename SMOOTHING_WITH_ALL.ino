//6 grey shades --> 6 sounds (Blues Scals) maybe pentatonic -

//DF PLAYER LIBRARY
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

//LIGHT SENSOR LIBRARY
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
int led = 5;

/*///////SMOOTHING//////
const int numReadings = 3;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
*/

//MOTOR 
int motorPin = 9;



void setup() {
/*///////SMOOTHING//////
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  */
  
  //MOTOR SETUP
  pinMode(motorPin, OUTPUT);
  
  
  //LIGHT SENSOR SETUP
  Wire.begin();
  lightMeter.begin();
  //Serial.println(F("Light To Sound Test"));
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

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first first notes once when started up
}



void loop() {

  //LIGHT SENSOR PART
  analogWrite(led, 255); 

  float lux = lightMeter.readLightLevel();
  delay(130);
  int lightReading = lux;

  //MOTOR PART
  //int speed = map(analogRead(A0), 0, 1023, 0, 255); //map potentiometer to 0 to 255
 if (lightReading < 500){
   analogWrite(motorPin, 255);
    }else { analogWrite(motorPin, 0);
  }
  
/*
  ///////SMOOTHING//////
   // subtract the last reading:
  total = total - readings[readIndex]; //store reading in buffer
  // read from the sensor:
  readings[readIndex] = lightMeter.readLightLevel();
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
    Serial.print("Light: ");
    Serial.println(average);
    Serial.print("Speed: ");
    //Serial.println(speed);
  delay(10);        // delay in between reads for stability
*/

  //NOTE PLAYING PART
  
  if (lightReading < 0.5) {
    myDFPlayer.playMp3Folder(1);

  }
   if ((lightReading > 0.51 ) && (lightReading < 9)){
    myDFPlayer.playMp3Folder(2);
   }
   if ((lightReading > 9.1) && (lightReading < 35)){
    myDFPlayer.playMp3Folder(3);
   }
   if ((lightReading > 35.1) && (lightReading < 45)){
    myDFPlayer.playMp3Folder(4);
   }
   if ((lightReading > 45.1) && (lightReading < 90)){
   myDFPlayer.playMp3Folder(5);
   }
  if ((lightReading > 90.1) && (lightReading < 500)){
    myDFPlayer.playMp3Folder(6);
  }
 
 
}
