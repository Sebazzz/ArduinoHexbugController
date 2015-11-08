#include "Direction.h"
#include "HexbugInput.h"
#include "Storage.h"
#include "StepRecorder.h"
#include "Led.h"

// ----- StepRecorder
StepRecorder::StepRecorder(Led* lcd, HexbugCtrl* ctrl, StepCollection* steps)
{
	this->_isRecording = false;
	this->_startTime = 0;
	this->_steps = steps;
	this->_ctrl = ctrl;

	this->_lcd = lcd;
	this->_currentDirection = NULL;
}


StepRecorder::~StepRecorder()
{
}

void StepRecorder::record()
{
	const Direction* newDirection = HexbugInput::getCurrentDirection();

	if (this->_isRecording == false) {
		if (newDirection != NULL) {
			Serial.print("Starting initial recording with direction ");
			Serial.println(newDirection->name);
			this->initRecordPiece(newDirection);
		}

		return;
	}

	if (this->_currentDirection != newDirection) {
		this->finishRecordPiece();
		this->initRecordPiece(newDirection);
	}
}

void StepRecorder::reset()
{
	if (this->_isRecording == false) return;
	if (this->_currentDirection != NULL) this->finishRecordPiece();
	this->_isRecording = false;
}

void StepRecorder::initRecordPiece(const Direction* direction){
	this->_currentDirection = direction;
	this->_startTime = millis();

	if (direction != NULL) {
		Serial.print("Recorder: START ");
		Serial.println(direction->name);
		direction->execute(this->_ctrl);
	}
	else {
		Serial.println("Recorder: START STOP");
		this->_ctrl->stop();
	}

	this->_isRecording = true;
}

void StepRecorder::finishRecordPiece(){
	Serial.print("Recorder: STOP ");
	if (this->_currentDirection != NULL) {
		Serial.println(this->_currentDirection->name);
	}
	else {
		Serial.println("STOP");
	}

	// add step
	unsigned long currentTime = millis();

	Step s;
	s.duration = currentTime - this->_startTime;
	s.direction = this->_currentDirection;

	this->_steps->addItem(s);
}

// ----- StepPlayer
StepPlayer::StepPlayer(Led* lcd, HexbugCtrl* ctrl, StepCollection* steps) {
	Serial.print("Player: Initializing with ");
	Serial.print(steps->size());
	Serial.println(" steps");

	this->_steps = steps;
	this->_index = -1;
	this->_lcd = lcd;
	this->_ctrl = ctrl;

	// TODO: led
}

StepPlayer::~StepPlayer() {

}

bool StepPlayer::checkStepState() {
	if (this->_steps->size() == 0){
		return false;
	}

	// first piece
	if (this->_index == -1) {
		this->_index = 0;

		goto playCurrentPiece;
	}

	// determine piece completeness
	if (this->_currentStepTimer.isRunning() && !this->_currentStepTimer.isExpired()) {
		return true;
	}

	// determine play completeness
	this->_index++;
	if (this->_index >= this->_steps->size()) {
		return false;
	}

playCurrentPiece:
	// next piece
	this->_current = this->_steps->getItem(this->_index);

	if (this->_current.direction == NULL) {
		Serial.println("STOP");
		this->_ctrl->stop();
	}
	else {
		Serial.print("DIRECTION: ");
		Serial.println(this->_current.direction->name);
		this->_current.direction->execute(this->_ctrl);
	}

	this->_currentStepTimer.start(this->_current.duration);

	return true;
}

void StepPlayer::play() {
	if (this->_steps->size() == 0){
		return;
	}

	while (this->_currentStepTimer.isRunning() && !this->_currentStepTimer.isExpired());

	if (!this->checkStepState()) {
		this->reset();
	}
}

void StepPlayer::reset() {
	// restart piece
	if (this->_index >= 0) {
		if (!this->_timer.isRunning()) {
			Serial.println("Player: Playing done");
			this->_timer.start(2000);
			return;
		}

		// isRunning
		if (!this->_timer.isExpired()) {
			return;
		}

		// TODO: output

		this->_index = -1;
		this->_timer.stop();
	}
}