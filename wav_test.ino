#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>
//#include <SD.h>                      // need to include the SD library
#include <SdFat.h>
SdFat sd;
#include <TMRpcm.h>           //  also need to include this library...

int SW1;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328
const int ledPin = 3;
const int btnPin = 2;

TMRpcm audio;   // create an object for use in this sketch

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up.");
  
  if (!sd.begin(SD_ChipSelectPin, SPI_FULL_SPEED)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  
  pinMode(ledPin, OUTPUT);
  audio.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
  audio.setVolume(2);
  pinMode(btnPin,INPUT);  //Define A0 as digital input.
  
  Serial.println("Setup Complete");
}

void loop() {
  if(!audio.isPlaying()){
    debugLEDOff();
    SW1=digitalRead(2);
    
    if(SW1 == HIGH){
      Serial.println("Switch 1");
      delay(500);
      SW1=digitalRead(2);
      
      if(SW1 == LOW){
        Serial.println("Gonna play now");
        audio.play("4.wav");
        debugLEDOn();
      }
    }
  }
}

void debugLEDOn(){
  analogWrite(ledPin, 50);
}

void debugLEDOff(){
  analogWrite(ledPin, 0);
}

