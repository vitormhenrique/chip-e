#include "Arduino.h"
#include <SoftwareSerial.h> //this is a must
#include <Servo.h>
#include <ALLBOT.h>
#include "Adafruit_Pixie.h"
#include <SerialLCD.h>
#include "config.h"
#include "Adafruit_Soundboard.h"

#define DEBUG //Uncoment this line to get debug information of the Serial port.
//#define WAIT_SERIAL //Uncoment this line to get debug information of the Serial port.

#ifdef DEBUG
	#define DEBUG_PRINT(x)     Serial.print (x)
	#define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
	#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
	#define DEBUG_PRINT(x)
	#define DEBUG_PRINTDEC(x)
	#define DEBUG_PRINTLN(x)
#endif

ALLBOT BOT(12);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial3, NULL, SFX_RST);

#include "utils.h"

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);
SerialLCD slcd(9,10);



/*------------------------------------------------------------------------
serialEvent1:
-------------------------------------------------------------------------*/
void serialEvent1() {
  while (Serial1.available()) {
  // get the new byte:
    char inChar = (char)Serial1.read();
  // if the incoming character is a exclamation mark, set a flag
  // so the main loop can do something about it:
    inputString += inChar;
    if (inChar == endOfString) {
      stringComplete = true;
      //DEBUG_PRINTLN(inputString);
    }
  }
}
/*------------------------------------------------------------------------
setup:
-------------------------------------------------------------------------*/
void setup()
{
	pinMode(FIREPIN, OUTPUT);
	digitalWrite(FIREPIN, LOW);

	pinMode(LASERPIN, OUTPUT);
	digitalWrite(LASERPIN, LOW);

	// cannonServo.attach(PIN_CANNON);
	// neckServo.attach(PIN_NECK);
	// cannonServo.write(90);
	// neckServo.write(90);

	Serial3.begin(9600);

	sfx.reset();

  DEBUG_PRINTLN("SFX board found");

  if (! sfx.playTrack("T00RAND7WAV") ) {
    DEBUG_PRINTLN("Failed to play track?");
  }

DEBUG_PRINTLN("try to start pixel...");
	pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
	strip.setBrightness(brightness);  // Adjust as necessary to avoid blinding
	DEBUG_PRINTLN("pixel started");


	DEBUG_PRINTLN("try to start slcd...");

	slcd.begin();
	slcd.backlight();
	slcd.print("ready...");
	DEBUG_PRINTLN("slcd started");


	DEBUG_PRINTLN("slcd...");

  // NAME.attach(motorname, pin, init-angle, flipped, offset-angle);
  BOT.attach(hipFrontLeft,   PIN_HIP_FRONT_LEFT,  45, 0,  0);
  BOT.attach(hipFrontRight,  PIN_HIP_FRONT_RIGHT,  45, 1,  0);
  BOT.attach(hipRearLeft,    PIN_HIP_REAR_LEFT,  45, 1,  0);
  BOT.attach(hipRearRight,   PIN_HIP_REAR_RIGHT,   45, 0,  0);

  BOT.attach(kneeFrontLeft,  PIN_KNEE_FRONT_LEFT,  10, 0,  0);
  BOT.attach(kneeFrontRight, PIN_KNEE_FRONT_RIGHT,  10, 1,  0);
  BOT.attach(kneeRearLeft,   PIN_KNEE_REAR_LEFT,   10, 0,  0);
  BOT.attach(kneeRearRight,  PIN_KNEE_REAR_RIGHT,   10, 1,  0);

  BOT.attach(ankleFrontLeft,  PIN_ANKLE_FRONT_LEFT,  0, 0,  0);
  BOT.attach(ankleFrontRight, PIN_ANKLE_FRONT_RIGHT,  0, 1,  0);
  BOT.attach(ankleRearLeft,   PIN_ANKLE_REAR_LEFT,  0, 0,  0);
  BOT.attach(ankleRearRight,  PIN_ANKLE_REAR_RIGHT,  0, 1,  0);

  // Perform the standup sequence
	DEBUG_PRINTLN("try to start standup...");
  standup();
	DEBUG_PRINTLN("standup...");

  // Starting the hardware UART, necessary for receiving IR
  Serial1.begin(38400);
}

/*------------------------------------------------------------------------
loop:
-------------------------------------------------------------------------*/
void loop()
{

  if(stringComplete){
    handleCommunication();
    inputString="";
    stringComplete=false;
  }

	strip.setBrightness(brightness);

	if(previousRedEye != redEye){
		if(redEye){
			strip.setPixelColor(0, 255, 0, 0);
			slcd.clear();
			slcd.setCursor(0, 0);
			slcd.print("brainsss!!");
		}else{
			slcd.clear();
			slcd.setCursor(0, 0);
			slcd.print("hello :)");
			strip.setPixelColor(0, 0, 0, 255);
		}
		previousRedEye=redEye;
	}

	strip.show();

}
