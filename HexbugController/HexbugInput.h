#pragma once

#include "Direction.h"
#include "HexbugCtrl.h"

class HexbugInput
{
private:
	HexbugInput();
	~HexbugInput();

public:
	static const Direction* getCurrentDirection();

	static void setup();
	static void forwardCurrentInput(HexbugCtrl* ctrl);
};

