#include "Arduino.h"
#include "Direction.h"
#include "HexbugCtrl.h"

const Direction Direction::FORWARD("FWD", 8, &HexbugCtrl::forward);
const Direction Direction::BACK("BACK", 5, &HexbugCtrl::backwards);
const Direction Direction::LEFT("LEFT", 6, &HexbugCtrl::left);
const Direction Direction::RIGHT("RIGHT", 7, &HexbugCtrl::right);

const Direction Direction::ALL[] = { Direction::FORWARD, Direction::BACK, Direction::LEFT, Direction::RIGHT };

Direction::Direction(const char* name, int pin, DirectionExec exec) : _pin(pin), _exec(exec), name(name)
{

}

Direction::~Direction()
{
}

void Direction::setup() const
{
	pinMode(this->_pin, INPUT);
}

bool Direction::isPressed() const {
	return digitalRead(this->_pin) == HIGH;
}

void Direction::execute(HexbugCtrl *ctrl) const {
	DirectionExec exec = this->_exec;
	(ctrl->*exec)();
}