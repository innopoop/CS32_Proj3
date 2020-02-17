#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, double startX, double startY, int dir, int depth) : GraphObject(imageID, startX, startY, dir, depth) {
	m_alive = true;
}

Actor::~Actor() {
}

bool Actor::isAlive() const{
	return m_alive;
}

void Actor::isDead() {
	m_alive = false;
}

void Actor::setWorld(GameWorld* gw) {
	m_gw = gw;
}

GameWorld* Actor::getWorld() const {
	return m_gw;
}

Socrates::Socrates(double startX, double startY):Actor(IID_PLAYER, startX, startY) {
	m_health = 100;
	m_sprayCharge = 20;
	m_flameCharge = 5;
}

Socrates::~Socrates() {

}
void Socrates::doSomething() {
	if (!this->isAlive())
		return;
	//int ch;
	//if (getWorld()->getKey(ch)) {
	//	switch (ch) {
	//	case KEY_PRESS_LEFT:
	//		getDirection() < 90 ? GraphObject::moveAngle(359 - (90 - getDirection())) : GraphObject::moveAngle(getDirection() - 90);

	//		break;
	//	case KEY_PRESS_RIGHT:
	//		break;
	//	case KEY_PRESS_DOWN:
	//		break;
	//	case KEY_PRESS_SPACE:
	//		if (m_sprayCharge > 0)
	//			m_sprayCharge--;
	//		break;
	//	default:
	//	}
	//}
}

Misc::Misc(int imageID, double startX, double startY, Direction dir, int depth) :Actor(imageID, startX, startY, dir, depth) {

}
Dirt::Dirt(double startX, double startY) : Misc(IID_DIRT, startX, startY) {

}

void Dirt::doSomething() {
	return;
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
