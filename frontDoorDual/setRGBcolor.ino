void writeLed(int redVal, int greenVal, int blueVal){
  analogWrite(redPin, map(redVal, 255, 0, 170, 255));
  analogWrite(greenPin, map(greenVal, 255, 0, 0, 255));
  analogWrite(bluePin, map(blueVal, 255, 0, 0, 255));
}

void fadeToRed(){
  flagIdleBreathing = 0;
  for(; redVal<254; redVal++){
    if (blueVal>=1){blueVal--;}
    if (greenVal>=1){greenVal--;}
    writeLed(redVal, greenVal, blueVal);
    delay(15);
  }
}

void fadeToBlue(){
  flagIdleBreathing = 0;
  for(; blueVal<254; blueVal++){
    if (redVal>=1){redVal--;}
    if (greenVal>=1){greenVal--;}
    writeLed(redVal, greenVal, blueVal);
    delay(15);
  }
}

void fadeToGreen(){
  flagIdleBreathing = 0;
  for(; greenVal<254; greenVal++){
    if (blueVal>=1){blueVal--;}
    if (redVal>=1){redVal--;}
    writeLed(redVal, greenVal, blueVal);
    delay(15);
  }
}

void redBlink(){
  flagIdleBreathing = 0;
  for(int redBlinkI=0; redBlinkI<8; redBlinkI++){
    writeLed(255, 0, 0);
    delay(150);
    writeLed(0, 0, 0);
    delay(150);
  }
}
