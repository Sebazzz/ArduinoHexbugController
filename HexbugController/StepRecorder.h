#pragma once

#include "Arduino.h"
#include "DebugLog.h"
#include "Timer.h"
#include "Storage.h"
#include "HexbugCtrl.h"
#include "Led.h"
#include "Vector.h"

class StepPlayer {
private:
	StepCollection* _steps;
	Led* _lcd;

	Step _current;
	int _index;
	Timer _timer;
	Timer _currentStepTimer;
	HexbugCtrl* _ctrl;

	bool checkStepState();

public:
	void play();
	void reset();

	StepPlayer(Led* lcd, HexbugCtrl* ctrl, StepCollection* steps);
	~StepPlayer();
};

class StepRecorder
{
private:
	StepCollection* _steps;
	Led* _lcd;

	unsigned long _startTime;
	const Direction* _currentDirection;
	bool _isRecording;
	HexbugCtrl* _ctrl;

private:
	void initRecordPiece(const Direction* direction);
	void finishRecordPiece();

public:
	StepRecorder(Led* lcd, HexbugCtrl* ctrl, StepCollection* steps);
	~StepRecorder();

	void record();
	void reset();
};


