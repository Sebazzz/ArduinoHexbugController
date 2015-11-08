// HexbugCtrl.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <IRremote.h>

class HexbugCtrl
{
 private:
	 static const unsigned int CODES_LENGTH = 25;
	 static const unsigned int CODES_FREQ = 38;

	 static const unsigned int CODE_FORWARD[CODES_LENGTH];
	 static const unsigned int CODE_LEFT[CODES_LENGTH];
	 static const unsigned int CODE_BACK[CODES_LENGTH];
	 static const unsigned int CODE_RIGHT[CODES_LENGTH];

	 IRsend _irSend; // PIN 3 (hardcoded)

	 void sendCode(const unsigned int code[]);
	 void setCode(const unsigned int code[]);

	 const void* _currentDirection;

 public:
	 HexbugCtrl();

	 void setup();
	 void run();

	 void forward();
	 void backwards();
	 void left();
	 void right();

	 void stop();
};