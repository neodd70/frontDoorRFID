
void setLedRed(){
  analogWrite(redPin, 180);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);

}

void setLedGreen(){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 220);
  analogWrite(bluePin, 255);

}

void setLedBlue(){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 200);

}

void setLedBlack(){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);

}


void fadeBlueToRed(){
  int blueVal=200;
  int greenVal=255;
  for(int redVal=255; redVal>180; redVal--){
    delay(15);
    if (blueVal<=250){blueVal++;}
    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);
  }
}

void fadeRedToBlue(){
  int blueVal=255;
  int greenVal=255;
  for(int redVal=180; redVal<255; redVal++){
    delay(15);
    blueVal--;
    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);
  }
}

void fadeBlueToGreen(){
  int blueVal=200;
  int redVal=255;
  for(int greenVal=255; greenVal>220; greenVal--){
    delay(20);
    if (blueVal<=250){blueVal++;}
    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);
  }
}

void fadeGreenToBlue(){
  int blueVal=255;
  int redVal=255;
  for(int greenVal=220; greenVal<255; greenVal++){
    delay(20);
    blueVal--;
    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);
  }
}
