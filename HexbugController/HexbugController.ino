/*
 Name:		HexbugController.ino
 Created:	10/25/2015 3:02:25 PM
 Author:	Sebazzz
*/

// the setup function runs once when you press reset or power the board
#include "Direction.h"
#include "HexbugCtrl.h"
#include "HexbugInput.h"
#include "Led.h"
#include "Storage.h"
#include "StepRecorder.h"
#include "ToggleSwitch.h"
#include <IRremote.h>

HexbugCtrl bug;
Led led;
StepCollection steps;
StepRecorder recorder(&led, &bug, &steps);
StepPlayer player(&led, &bug, &steps);
ToggleSwitch stateSwitch(4);
enum { State_Recording, State_Playing } state;

void setup() {
	DebugLog::init();

	led.init();
	led.setMode(LedMode_Recording);

	HexbugInput::setup();
	bug.setup();
	state = State_Recording;

	Serial.println("Beginning in recording mode");
}

// the loop function runs over and over again until power down or reset
void loop() {
	led.run();
	stateSwitch.run();
	bug.run();
	//HexbugInput::forwardCurrentInput(&bug);

	switch (state) {
		case State_Recording:
			recording();
			return;

		case State_Playing:
			playing();
			return;
	}
}

void recording() {
	recorder.record();

	// switch
	if (stateSwitch.isChanged()) {
		while (!stateSwitch.isJustDepressed()) stateSwitch.run();

		state = State_Playing;
		Serial.println("Change: Playing mode");
		led.setMode(LedMode_Playing);

		recorder.reset();
		player.play();
	}
}

void playing() {
	player.play();

	// switch
	if (stateSwitch.isChanged()) {
		while (!stateSwitch.isJustDepressed()) stateSwitch.run();

		state = State_Recording;
		Serial.println("Change: Recording mode");
		led.setMode(LedMode_Recording);

		player.reset();
		recorder.record();

		steps.clear(true);
	}
}