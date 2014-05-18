#include <Wire.h>  
#include <Adafruit_NFCShield_I2C.h>  
Adafruit_NFCShield_I2C nfc(2, 3); // Pin 2 is IRQ, Pin 3 is RESET (By default on shield) Pins can be changed here.

const int bluePin = 9;
const int redPin = 10;
const int greenPin = 11;
const int latch = 7;
const int door = 8;
int doorState = LOW;


void setup(void)
   {Serial.begin(9600);
   pinMode(latch, OUTPUT);
   pinMode(door, INPUT);
   pinMode(bluePin, OUTPUT);
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(13, OUTPUT);
   digitalWrite(latch, LOW);
   
   setLedBlue();
   nfc.begin();
   nfc.SAMConfig();}

String database[3][2] = {
//    Friendly Name                                 Tag UID                                 
   "Pocky's Left Hand",                       "04:24:04:12:FF:38:85",                            
   //"Jenna's Right Hand",                      "04:32:FD:12:FF:38:81",                             
   "Pocky's Right Hand",                      "04:D5:04:12:FF:38:84",                            
   "Mike's Left Hand",                        "04:AE:02:12:FF:38:84",                            
   //"Mike's Magic Band",                       "04:95:2A:C2:D5:2C:80",                           
   //"Corbyn's Magic Band",                     "04:78:51:C2:A4:2A:80",                          
   //"Tiffany's Key FOB",                       "76:38:3A:95",                                   
   //"Tiffany's Magic Band",                    "04:0F:61:62:9E:2B:80",                            
   //"Pocky's Magic Band",                      "04:68:65:CA:8B:34:80",                             
   //"Lance's Magic Band",                      "04:68:65:52:8C:34:80"                          
   



}; int dbSize = sizeof(database) / sizeof(database[0]);

void loop(void) {
   
   String tagString;
   readTag(tagString);
  
   for (int dbIndex = 0; dbIndex < dbSize; dbIndex++){
      if (tagString == database[dbIndex][1]) {      
        Serial.print("Read ");  Serial.print(database[dbIndex][2]);  Serial.println("'s tag.");  // This line will only fire if a chip is matched from the DB. Put stuff to do if an authorized chip is presented here.
        unsigned long startTime, endTime, currentTime;
        currentTime=millis();
        //startTime = millis();
        endTime = currentTime+15000;
          
          fadeBlueToGreen();
          digitalWrite(latch, HIGH);
          
              int fadeVal=1;
              int blueVal=255;
              int greenVal=220;
              int redVal=255;
              int delayVal=40;
              int ctr1=1;
              int ctr2=0;
              
              
        while (currentTime <= endTime){
          currentTime=millis();
          Serial.println(digitalRead(door));
            if (digitalRead(door) == HIGH){
              delay(750);  
              digitalWrite(latch, LOW);
            }
              greenVal=greenVal+fadeVal;
              
                if (greenVal==255 || greenVal==220){
       
                  fadeVal= -fadeVal;
                  if(delayVal > 5){
                    if(ctr2 == 0){
                      ctr1+=1;
                      ctr2=ctr1;
                      delayVal-=7;
                  }
                  ctr2--;
                }
                  } 
                 
                delay(delayVal);
               
                analogWrite(redPin, redVal);
                analogWrite(greenPin, greenVal);
                analogWrite(bluePin, blueVal);
        }

      //endTime = millis();
    
          
    digitalWrite(latch, LOW);
    fadeGreenToBlue();
    
    
        break;
    } if (dbIndex == dbSize-1){  
        Serial.print("Unrecognized card: "); Serial.println(tagString);  // This line will only fire if a chip that is NOT in the database is presented. It reads out the UID over serial so you can copy and paste easily into the sketch, if so desired.
        fadeBlueToRed();
        for(int redBlinkI=0; redBlinkI<8; redBlinkI++){
        setLedRed();
        delay(150);
        setLedBlack();
        delay(150);
        }
        fadeRedToBlue();
        //setLedBlue();
    }   
  }
}   

