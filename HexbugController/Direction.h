#pragma once
#include "HexbugCtrl.h"

typedef void (HexbugCtrl::*DirectionExec) ();

class Direction
{
private:
	const int _pin;
	const DirectionExec _exec;

public:
	Direction(const char* name, int inputPin, DirectionExec exec);
	~Direction();

	void setup() const;
	bool isPressed() const;
	void execute(HexbugCtrl* ctrl) const;

	const char* name;

	static const Direction LEFT;
	static const Direction RIGHT;
	static const Direction FORWARD;
	static const Direction BACK;
	
	static const size_t COUNT = 4;
	static const Direction ALL[Direction::COUNT];
};

