#include <Wire.h>  

// Took out NFC libraries here since this arduino is just dealing with Serial now
// Also killed readtag tab, same reason. That code was for a standalone 'duino

const int bluePin = 9;
const int redPin = 10;
const int greenPin = 11;
const int latch = 7;
const int door = 8;

float redVal = 0;
float greenVal = 0;
float blueVal = 0;

int doorState = LOW;

String serialstring; 
int flagIdleBreathing = 1;
int flagGreenBreathing = 0;

String tagString; // Make string null so there's never a residual tag string in there.
int tagLastReadAt = 0;
  
void setup(void){
  Serial.begin(9600);
  pinMode(latch, OUTPUT);
  pinMode(door, INPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(latch, LOW);
  
  writeLed(0, 0, 0);  // Blue
  
}

String database[5][2] = {  // Changed 3 to 2 in second bracket because we took out columns & numbered first bracket because definining the number of rows cuts down on mem use
//    Friendly Name                                 Tag UID                       
     "Mike's Left Hand",                            "04:AE:02:12:FF:38:84",                            
     "Mike's Magic Band",                           "04:95:2A:C2:D5:2C:80",                           
     "Corbyn's Magic Band",                         "04:78:51:C2:A4:2A:80",                          
     "Tiffany's Key FOB",                           "76:38:3A:95",                                   
     "Tiffany's Magic Band",                        "04:0F:61:62:9E:2B:80"       // Removed non essential rows for mem use
}; int dbSize = sizeof(database) / sizeof(database[0]);

int cardRead=false;

void loop(void) {
  unsigned long currentMillis = millis();
  
  readSerialString(tagString);
  
  if(flagIdleBreathing){
    blueVal = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
    writeLed(redVal, greenVal, blueVal);
  }  
  
  if(flagGreenBreathing){
    blueVal = 0;
    greenVal = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
    writeLed(redVal, greenVal, blueVal);
  }
  
  if (currentMillis <  endLatchOpenTime) {digitalWrite(latch, HIGH);} else {digitalWrite(latch, LOW);}
  
  int dbIndex = 0;
  if (tagString > 0 && lastReadMillis > currentMillis + 2000){
    for (; dbIndex < dbSize; dbIndex++){
      if (tagString == database[dbIndex][1]) {      
      
        unsigned long startTime, endTime, currentTime;
        currentTime=millis();
        endLatchOpenTime = currentTime+15000;
  
       
        fadeToGreen();
              
        endLatchOpenTime = currentMillis + 15000;        
        

          flagGreenBreathing = 1;
            
          currentTime=millis();
          //Serial.println(digitalRead(door));
          if (digitalRead(door) == HIGH){
            delay(750);  
            digitalWrite(latch, LOW);
            break;
          }
        } 
        
        flagGreenBreathing = 0;

             
        digitalWrite(latch, LOW);
        fadeToBlue();
        
        flagIdleBreathing = 1;
        lastReadMillis = millis();
                
        break;
      } 
      
      if (dbIndex == dbSize-1){  
        Serial.print("Unrecognized card: "); Serial.println(tagString);  // This line will only fire if a chip that is NOT in the database is presented. It reads out the UID over serial so you can copy and paste easily into the sketch, if so desired.
      
        fadeToRed();
        redBlink();
        fadeToBlue();
        flagIdleBreathing = 1;
        lastReadMillis = millis();
      }  
    }
  }  
}
