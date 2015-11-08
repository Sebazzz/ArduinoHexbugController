#pragma once

#include "Direction.h"
#include "Vector.h"

struct Step {
	unsigned int duration;

	const Direction* direction;
};

typedef Vector<Step> StepCollection;

class Storage
{
private:
	StepCollection _steps;

public:
	Storage();
	~Storage();

	StepCollection* getTemp();
};

