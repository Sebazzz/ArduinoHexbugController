#include "HexbugInput.h"
#include "Direction.h"

HexbugInput::HexbugInput()
{
}


HexbugInput::~HexbugInput()
{
}

const Direction* HexbugInput::getCurrentDirection() {
	const Direction* ref = NULL;

	for (size_t i = 0; i < Direction::COUNT; i++)
	{
		ref = &Direction::ALL[i];

		if (ref->isPressed()) {
			return ref;
		}
	}

	return NULL;
}

void HexbugInput::setup() {
	// set-up input
	for (size_t i = 0; i < Direction::COUNT; i++)
	{
		Direction::ALL[i].setup();
	}
}

void HexbugInput::forwardCurrentInput(HexbugCtrl* ctrl) {
	const Direction* dir = HexbugInput::getCurrentDirection();

	if (dir == NULL) {
		ctrl->stop();
	}
	else {
		dir->execute(ctrl);
	}
}