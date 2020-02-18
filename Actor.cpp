#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cmath>
using namespace std;
double toRadians(int degrees);

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
	int ch;
	if (getWorld()->getKey(ch)) {
		double xDis = getX() - VIEW_RADIUS;
		double yDis = getY() - (VIEW_HEIGHT/2);
		cout << "X: " << xDis << " Y: " << yDis << endl;
		double angleFromPosXaxis = toRadians(90);
		if(xDis != 0)
			angleFromPosXaxis = atan(yDis / xDis);
		//quadrant
		int quad = 0;
		if (xDis == 0) {
			if (yDis >= 0) {
				quad = 2;
			}
			else {
				quad = 4;
			}
		}
		if ((yDis / xDis) >= 0) {
			if (xDis >= 0) {
				quad = 0;
			}
			else {
				quad = 2;
			}
		}
		else {
			if (xDis > 0) {
				quad = 4;
			}
			else {
				quad = 2;
			}
		}
		cout << "Angle: " << angleFromPosXaxis << endl;
		cout << "Quad: " << quad << endl;
		double newX = 0;
		double newY = 0;
		switch (ch) {
		case 'a':
		case 'w':
		case KEY_PRESS_UP:
		case KEY_PRESS_LEFT:
			//(getDirection() < toRadians(90)) ? GraphObject::moveAngle(toRadians(359 - (90 - getDirection()))) : GraphObject::moveAngle(toRadians(getDirection() - 90));
			//cout << (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 - 1)))) << endl;
			newX = VIEW_RADIUS + (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 -1))));
			newY = (VIEW_HEIGHT / 2) + (128 * sin((angleFromPosXaxis + toRadians(quad * 90.0 - 1))));
			if (getDirection() == 0) {
				setDirection(359);
			}
			else {
				setDirection(getDirection() - 1);
			}
			cout << "New X: " << newX << " New Y: " << newY << endl;
			moveTo(newX, newY);
			break;
		case 'd':
		case 's':
		case KEY_PRESS_DOWN:
		case KEY_PRESS_RIGHT:
			newX = VIEW_RADIUS + (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 + 1))));
			newY = (VIEW_HEIGHT / 2) + (128 * sin((angleFromPosXaxis + toRadians(quad * 90.0 + 1))));
			if (getDirection() == 359) {
				setDirection(0);
			}
			else {
				setDirection(getDirection() + 1);
			}
			cout << "New X: " << newX << " New Y: " << newY << endl;
			moveTo(newX, newY);
			break;
		case KEY_PRESS_SPACE:
			if (m_sprayCharge > 0)
				m_sprayCharge--;
			break;
		}
	}
}

Misc::Misc(int imageID, double startX, double startY, Direction dir, int depth) :Actor(imageID, startX, startY, dir, depth) {

}
Dirt::Dirt(double startX, double startY) : Misc(IID_DIRT, startX, startY) {
}

void Dirt::doSomething() {
	return;
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

double toRadians(int degrees) {
	const double PI = 4 * atan(1);
	return degrees * (PI / 180);
}
