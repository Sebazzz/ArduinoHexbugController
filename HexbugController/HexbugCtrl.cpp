// 
// 
// 

#include "HexbugCtrl.h"

// Constant IR code defs
const unsigned int HexbugCtrl::CODE_FORWARD[HexbugCtrl::CODES_LENGTH] = { 1962, 490, 1962, 959, 383, 1535, 383, 575, 383, 575, 383, 575, 383, 575, 383, 575, 383, 1514, 383, 1535, 383, 1535, 362, 1535, 383 };
const unsigned int HexbugCtrl::CODE_BACK[HexbugCtrl::CODES_LENGTH] = { 1962, 490, 1962, 959, 383, 575, 383, 1514, 383, 575, 383, 575, 383, 575, 383, 1535, 383, 575, 383, 1514, 383, 1514, 383, 1514, 383 };
const unsigned int HexbugCtrl::CODE_LEFT[HexbugCtrl::CODES_LENGTH] = { 1962, 490, 1962, 959, 383, 1514, 383, 1535, 362, 575, 383, 575, 383, 575, 383, 575, 383, 575, 383, 1514, 383, 1514, 383, 1514, 383 };
const unsigned int HexbugCtrl::CODE_RIGHT[HexbugCtrl::CODES_LENGTH] = { 1962, 490, 1962, 959, 383, 575, 383, 575, 383, 1514, 383, 575, 383, 575, 383, 1535, 383, 1514, 383, 575, 383, 1514, 383, 1514, 383 };

// Class impl
HexbugCtrl::HexbugCtrl() {
	this->_currentDirection = NULL;
}

void HexbugCtrl::sendCode(const unsigned int code[]) {
	this->_irSend.sendRaw(code, HexbugCtrl::CODES_LENGTH, HexbugCtrl::CODES_FREQ);
}

void HexbugCtrl::run() {
	if (this->_currentDirection) {
		this->sendCode((unsigned int*) this->_currentDirection);
	}
}

void HexbugCtrl::stop() {
	this->_currentDirection = NULL;
}

void HexbugCtrl::setup() {
	pinMode(3, OUTPUT);
	digitalWrite(3, LOW);
}

void HexbugCtrl::forward() {
	this->setCode(HexbugCtrl::CODE_FORWARD);
}

void HexbugCtrl::left() {
	this->setCode(HexbugCtrl::CODE_LEFT);
}

void HexbugCtrl::right() {
	this->setCode(HexbugCtrl::CODE_RIGHT);
}

void HexbugCtrl::backwards() {
	this->setCode(HexbugCtrl::CODE_BACK);
}

void HexbugCtrl::setCode(const unsigned int code[]) {
	this->_currentDirection = code;
}
