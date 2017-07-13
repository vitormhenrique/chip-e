enum MotorName {                          // Giving each motor a name
  hipFrontLeft,
  hipFrontRight,
  hipRearLeft,
  hipRearRight,
  kneeFrontLeft,
  kneeFrontRight,
  kneeRearLeft,
  kneeRearRight,
  ankleFrontLeft,
  ankleFrontRight,
  ankleRearLeft,
  ankleRearRight
};

int times;                                // Global variable that stores part the received IR command
int speedms;                              // Global variable that stores part the received IR command

unsigned long currentMillis; // store current loop's millis value
char endOfString = '!';
char stringSeparator = ';' ;
String inputString = "";         // a string to hold incoming data from BLE
bool stringComplete = false;  // whether the string is complete
bool calibrate = false;  // whether the string is complete
int brightness = 0;
bool redEye = false;
bool previousRedEye = false;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------
getParameter:  get the parameter on the passed string and return a string
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
String getParameter(int prmNumber, String str){
  String newStr = str;
  newStr.replace(String(stringSeparator),"");
  int totalPrm = str.length()-newStr.length();
  if(prmNumber>totalPrm){
    return "";
  }
  int startLoc = 0;
  int endLoc = 0;
  bool foundChar = false;
  int separatorsFound = 0;
  if(prmNumber!=0){
    do
    {
       if (str.charAt(startLoc)== stringSeparator){
        separatorsFound++;
        if(separatorsFound==prmNumber){
          foundChar=true;
        }
      }
      startLoc++;
    } while (!foundChar);
  }
  foundChar = false;
  endLoc = startLoc+1;
  do
  {
    if(str.charAt(endLoc)== stringSeparator || str.charAt(endLoc)== endOfString){
      foundChar = true;
    } else {
      endLoc++;
    }
  } while (!foundChar);
  String returningString = str.substring(startLoc,endLoc);
  // DEBUG_PRINTLN("Return parameter: ");
  // DEBUG_PRINTLN(prmNumber);
  // DEBUG_PRINTLN(" value: ");
  // DEBUG_PRINTLNLN(returningString);
  return returningString;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------
getAnalogChannel:
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int getAnalogChannel(int channel){
  channel = channel + 20;
  int value = 0;
  value = getParameter(channel,inputString).toInt();
  return value;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------
getDigitalChannel:
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool getDigitalChannel(int channel){
  return getParameter(channel,inputString).toInt();
}

void calibration_pos(){
  BOT.move(hipFrontLeft,90);
  BOT.move(hipFrontRight,90);
  BOT.move(hipRearLeft,90);
  BOT.move(hipRearRight,90);
  BOT.move(kneeFrontLeft,90);
  BOT.move(kneeFrontRight,90);
  BOT.move(kneeRearLeft,90);
  BOT.move(kneeRearRight,90);
  BOT.move(ankleFrontLeft,90);
  BOT.move(ankleFrontRight,90);
  BOT.move(ankleRearLeft,90);
  BOT.move(ankleRearRight,90);
  BOT.animate(500);
}

//--------------------------------------------------------------
void standup(){

  BOT.move(kneeFrontLeft, 110);
  BOT.move(kneeFrontRight, 110);
  BOT.animate(500);

  BOT.move(kneeRearLeft, 110);
  BOT.move(kneeRearRight, 110);
  BOT.animate(500);

  BOT.move(kneeFrontLeft, 90);
  BOT.animate(100);
  BOT.move(ankleFrontLeft, 20);
  BOT.animate(100);
  BOT.move(kneeFrontLeft, 110);
  BOT.animate(100);

  BOT.move(kneeFrontRight, 90);
  BOT.animate(100);
  BOT.move(ankleFrontRight, 20);
  BOT.animate(100);
  BOT.move(kneeFrontRight, 110);
  BOT.animate(100);

  BOT.move(kneeRearLeft, 90);
  BOT.animate(100);
  BOT.move(ankleRearLeft, 20);
  BOT.animate(100);
  BOT.move(kneeRearLeft, 110);
  BOT.animate(100);

  BOT.move(kneeRearRight, 90);
  BOT.animate(100);
  BOT.move(ankleRearRight, 20);
  BOT.animate(100);
  BOT.move(kneeRearRight, 110);
  BOT.animate(100);

}

//--------------------------------------------------------------
void waverearleft(int waves, int speedms){

    BOT.move(kneeRearLeft, 150);
    BOT.move(kneeFrontRight, 60);
    BOT.move(ankleFrontRight, 0);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 0);
    BOT.animate(speedms);

  for (int i = 0; i < waves; i++){
    BOT.move(ankleRearLeft, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleRearLeft, 60);
    BOT.animate(speedms/2);

    BOT.move(ankleRearLeft, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleRearLeft, 60);
    BOT.animate(speedms/2);
  }

    BOT.move(kneeRearLeft, 110);
    BOT.move(kneeFrontRight, 110);
    BOT.move(ankleRearLeft, 20);
    BOT.move(ankleFrontRight, 20);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void waverearright(int waves, int speedms){

    BOT.move(kneeRearRight, 150);
    BOT.move(kneeFrontLeft, 60);
    BOT.move(ankleFrontLeft, 0);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 0);
    BOT.animate(speedms);

  for (int i = 0; i < waves; i++){
    BOT.move(ankleRearRight, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleRearRight, 60);
    BOT.animate(speedms/2);

    BOT.move(ankleRearRight, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleRearRight, 60);
    BOT.animate(speedms/2);
  }

    BOT.move(kneeRearRight, 110);
    BOT.move(kneeFrontLeft, 110);
    BOT.move(ankleRearRight, 20);
    BOT.move(ankleFrontLeft, 20);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void wavefrontright(int waves, int speedms){

    BOT.move(kneeFrontRight, 150);
    BOT.move(kneeRearLeft, 60);
    BOT.move(ankleRearLeft, 0);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 0);
    BOT.animate(speedms);

  for (int i = 0; i < waves; i++){
    BOT.move(ankleFrontRight, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontRight, 60);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontRight, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontRight, 60);
    BOT.animate(speedms/2);
  }

    BOT.move(kneeFrontRight, 110);
    BOT.move(kneeRearLeft, 110);
    BOT.move(ankleFrontRight, 20);
    BOT.move(ankleRearLeft, 20);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void wavefrontleft(int waves, int speedms){
    BOT.move(kneeFrontLeft, 150);
    BOT.move(kneeRearRight, 60);
    BOT.move(ankleRearRight, 0);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 0);
    BOT.animate(speedms);

  for (int i = 0; i < waves; i++){
    BOT.move(ankleFrontLeft, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontLeft, 60);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontLeft, 90);
    BOT.animate(speedms/2);

    BOT.move(ankleFrontLeft, 60);
    BOT.animate(speedms/2);
  }

    BOT.move(kneeFrontLeft, 110);
    BOT.move(kneeRearRight, 110);
    BOT.move(ankleFrontLeft, 20);
    BOT.move(ankleRearRight, 20);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void scared(int shakes, int beeps){
    for (int i = 0; i < shakes; i++){
      BOT.move(kneeFrontLeft, 80);
      BOT.move(kneeFrontRight, 80);
      BOT.move(kneeRearLeft, 80);
      BOT.move(kneeRearRight, 80);
      BOT.move(ankleFrontLeft, 0);
      BOT.move(ankleFrontRight, 0);
      BOT.move(ankleRearLeft, 0);
      BOT.move(ankleRearRight, 0);
      BOT.animate(30);

      BOT.move(kneeFrontLeft, 110);
      BOT.move(kneeFrontRight, 110);
      BOT.move(kneeRearLeft, 110);
      BOT.move(kneeRearRight, 110);
      BOT.move(ankleFrontLeft, 20);
      BOT.move(ankleFrontRight, 20);
      BOT.move(ankleRearLeft, 20);
      BOT.move(ankleRearRight, 20);
      BOT.animate(30);
    }
}
//--------------------------------------------------------------
void leanright(int speedms){
    BOT.move(kneeFrontRight, 80);
    BOT.move(kneeRearRight, 80);
    BOT.move(ankleFrontRight, 0);
    BOT.move(ankleRearRight, 0);
    BOT.animate(speedms*2);

    delay(speedms*3);

    BOT.move(kneeFrontRight, 110);
    BOT.move(kneeRearRight, 110);
    BOT.move(ankleFrontRight, 20);
    BOT.move(ankleRearRight, 20);
    BOT.animate(speedms*2);
}
//--------------------------------------------------------------
void leanleft(int speedms){
    BOT.move(kneeFrontLeft, 80);
    BOT.move(kneeRearLeft, 80);
    BOT.move(ankleFrontLeft, 0);
    BOT.move(ankleRearLeft, 0);
    BOT.animate(speedms*2);

    delay(speedms*3);

    BOT.move(kneeFrontLeft, 110);
    BOT.move(kneeRearLeft, 110);
    BOT.move(ankleFrontLeft, 20);
    BOT.move(ankleRearLeft, 20);
    BOT.animate(speedms*2);
}
//--------------------------------------------------------------
void leanforward(int speedms){
    BOT.move(kneeFrontLeft, 80);
    BOT.move(kneeFrontRight, 80);
    BOT.move(ankleFrontLeft, 0);
    BOT.move(ankleFrontRight, 0);
    BOT.animate(speedms*2);

    delay(speedms*3);

    BOT.move(kneeFrontLeft, 110);
    BOT.move(kneeFrontRight, 110);
    BOT.move(ankleFrontLeft, 20);
    BOT.move(ankleFrontRight, 20);
    BOT.animate(speedms*2);
}
//--------------------------------------------------------------
void leanbackward(int speedms){
    BOT.move(kneeRearLeft, 80);
    BOT.move(kneeRearRight, 80);
    BOT.move(ankleRearLeft, 0);
    BOT.move(ankleRearRight, 0);
    BOT.animate(speedms*2);

    delay(speedms*3);

    BOT.move(kneeRearLeft, 110);
    BOT.move(kneeRearRight, 110);
    BOT.move(ankleRearLeft, 20);
    BOT.move(ankleRearRight, 20);
    BOT.animate(speedms*2);

}
//--------------------------------------------------------------
void lookleft(int speedms){
    BOT.move(hipRearLeft, 80);
    BOT.move(hipRearRight, 10);
    BOT.move(hipFrontLeft, 10);
    BOT.move(hipFrontRight, 80);
    BOT.animate(speedms);

    delay(speedms/2);

    BOT.move(hipRearRight, 45);
    BOT.move(hipRearLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void lookright(int speedms){
    BOT.move(hipRearRight, 80);
    BOT.move(hipRearLeft, 10);
    BOT.move(hipFrontRight, 10);
    BOT.move(hipFrontLeft, 80);
    BOT.animate(speedms);

    delay(speedms/2);

    BOT.move(hipRearRight, 45);
    BOT.move(hipRearLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void walkforward(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontRight, 45);
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontLeft, 45);
    BOT.move(hipRearLeft, 45);
    BOT.animate(speedms);
  }
}
//--------------------------------------------------------------
void walkbackward(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(hipRearRight, 45);
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(hipRearLeft, 45);
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
  }
}
//--------------------------------------------------------------
void walkleft(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(hipRearLeft, 45);
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);
  }
}
//--------------------------------------------------------------
void walkright(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(hipRearLeft, 45);
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);
  }
}
//--------------------------------------------------------------
void turnleft(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.move(hipRearLeft, 45);
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);
  }
}
//--------------------------------------------------------------
void turnright(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearRight, 80);
    BOT.move(hipRearRight, 10);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 110);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 80);
    BOT.move(hipRearLeft, 80);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 80);
    BOT.move(hipFrontLeft, 10);
    BOT.animate(speedms);

    BOT.move(kneeFrontLeft, 110);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 80);
    BOT.move(hipFrontRight, 80);
    BOT.animate(speedms);

    BOT.move(kneeFrontRight, 110);
    BOT.animate(speedms);

    BOT.move(hipFrontLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.move(hipRearLeft, 45);
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);
  }
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------
handleCommunication:
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void handleCommunication(){
  // get joysticks input and handle ComMotion
  int leftJoystickY = getAnalogChannel(CH_A_JOY_LEFT_Y);
  int leftJoystickX = getAnalogChannel(CH_A_JOY_LEFT_X);
  int rightJoystickX = getAnalogChannel(CH_A_JOY_RIGHT_X);
  int rightJoystickY = getAnalogChannel(CH_A_JOY_RIGHT_X);
  int pot1 = getAnalogChannel(CH_A_POT_1);
  int pot2 = getAnalogChannel(CH_A_POT_2);

  speedms  = map(pot1,0,1023,30,5);

  int neckAngle = map(rightJoystickX,0,1023,20,150);
  int cannonAngle = map(rightJoystickY,0,1023,20,150);

  // cannonServo.write(cannonAngle);
  // neckServo.write(neckAngle);

  times = 1;

  brightness = map(pot2,0,1023,0,200);

  //DEBUG_PRINTLNLN("ROBOT CLAW values...");
  //DEBUG_PRINTLN("frontRight: ");
  //DEBUG_PRINTLNLN(frontRight);
  //DEBUG_PRINTLN("backRight: ");
  //DEBUG_PRINTLNLN(backRight);
  //DEBUG_PRINTLN("frontLeft: ");
  //DEBUG_PRINTLNLN(frontLeft);
  //DEBUG_PRINTLN("backLeft: ");
  //DEBUG_PRINTLNLN(backLeft);

  if(leftJoystickY<20){
    walkbackward(times, (speedms*5));
    DEBUG_PRINTLN("walkbackward");
    DEBUG_PRINT("speedms: ");
    DEBUG_PRINTLN(speedms);
  }
  if(leftJoystickY>1000){
    walkforward(times, (speedms*5));
    DEBUG_PRINTLN("walkforward");
    DEBUG_PRINT("speedms: ");
    DEBUG_PRINTLN(speedms);
  }

  if(leftJoystickX<20){
    turnleft(times, (speedms*5));
    DEBUG_PRINTLN("turnleft");
    DEBUG_PRINT("speedms: ");
    DEBUG_PRINTLN(speedms);
  }

  if(leftJoystickX>1000){
    turnright(times, (speedms*5));
    DEBUG_PRINTLN("turnright");
    DEBUG_PRINT("speedms: ");
    DEBUG_PRINTLN(speedms);
  }

  if (getDigitalChannel(CH_D_RIGHT_HORIZONTAL_RIGHT)){
    leanright(speedms*5);
  }

  if (getDigitalChannel(CH_D_RIGHT_HORIZONTAL_LEFT)){
    leanleft(speedms*5);
  }

  if (getDigitalChannel(CH_D_RIGHT_VERTICAL_UP)){
    leanforward(speedms*5);
  }

  if (getDigitalChannel(CH_D_RIGHT_VERTICAL_DOWN)){
    leanbackward(speedms*5);
  }

  if (getDigitalChannel(CH_D_LEFT_HORIZONTAL_RIGHT)){
      wavefrontright(times, speedms*5);
  }

  if (getDigitalChannel(CH_D_LEFT_HORIZONTAL_LEFT)){
    wavefrontleft(times, speedms*5);
  }

  if (getDigitalChannel(CH_D_LEFT_VERTICAL_UP)){
    waverearright(times, speedms*5);
  }

  if (getDigitalChannel(CH_D_LEFT_VERTICAL_DOWN)){
    waverearleft(times, speedms*5);
  }

  if (getDigitalChannel(CH_D_BTN_LEFT_ATOP)){
    if(calibrate){
      calibration_pos();
    }
    else{
      standup();
    }
    calibrate = !calibrate;
  }

  if (getDigitalChannel(CH_D_BTN_LEFT_BOTTOM)){
    int track = random(1, 8);
    if (! sfx.playTrack(track) ) {
      DEBUG_PRINTLN("Failed to play track?");
    }
  }

  if (getDigitalChannel(CH_D_BTN_RIGHT_BOTTOM)){
    sfx.playTrack("T00RAND0WAV");
    digitalWrite(FIREPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a second
    digitalWrite(FIREPIN, LOW);    // turn the LED off by making the voltage LOW
  }


  digitalWrite(LASERPIN, getDigitalChannel(CH_D_BTN_RIGHT_ATOP));

  redEye = (getDigitalChannel(CH_D_SWITCH_1));

}
