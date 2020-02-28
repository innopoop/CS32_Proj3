#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
double toRadians(int degrees);
int toDegrees(int radians);
double findAngleRadians(double x1, double y1, double x2, double y2, int add = 0);

//ACTOR===========================================
Actor::Actor(int imageID, double startX, double startY, StudentWorld* sw, int dir, int depth, int health)
	:GraphObject(imageID, startX, startY, dir, depth) {
	m_health = health;
	m_gw = sw;
}

Actor::~Actor() {
}

void Actor::updateHealth(int health) {
	m_health += health;
}

int Actor::getHealth() const {
	return m_health;
}

StudentWorld* Actor::getWorld() const {
	return m_gw;
}

bool Actor::isAlive() const {
	return m_health > 0;
}

//SOCRATES=======================================
Socrates::Socrates(StudentWorld* sw)
	:Actor(IID_PLAYER, 0, VIEW_HEIGHT / 2, sw, 0, 0, 100) {
	m_sprayCharge = 20;
	m_flameCharge = 5;
	m_didNothing = false;
}

//SOCRATES=========
Socrates::~Socrates() {
}

void Socrates::doSomething() {
	if (!this->isAlive()) {
		return;
	}
	int ch;
	if (getWorld()->getKey(ch)) {
		m_didNothing = false;
		//double x = 0;
		//double y = 0;
		//double angle = 0;
		//switch (ch) {
		//case 'a':
		//case 'w':
		//case KEY_PRESS_UP:
		//case KEY_PRESS_LEFT:
		//	angle = findAngleRadians(getX(), getY(), VIEW_WIDTH / 2, VIEW_HEIGHT / 2, 5);
		//	x = VIEW_WIDTH / 2 + 128 * cos(angle);
		//	y = VIEW_HEIGHT / 2 + 128 * sin(toRadians(angle));
		//	cout << x << " " << y << endl;
		//	if (getDirection() == 0) {
		//		setDirection(359);
		//	}
		//	else {
		//		setDirection(getDirection() + 5);
		//	}
		//	moveTo(x, y);
		//	break;
		//case 'd':
		//case 's':
		//case KEY_PRESS_DOWN:
		//case KEY_PRESS_RIGHT:
		//	findAngleRadians(getX(), getY(), VIEW_WIDTH / 2, VIEW_HEIGHT / 2, -5);
		//	x = VIEW_WIDTH / 2 + 128 * cos(toRadians(angle));
		//	y = VIEW_HEIGHT / 2 + 128 * sin(toRadians(angle));
		//	if (getDirection() == 359) {
		//		setDirection(0);
		//	}
		//	else {
		//		setDirection(getDirection() - 5);
		//	}
		//	moveTo(x, y);
		double xDis = getX() - VIEW_RADIUS;
		double yDis = getY() - (VIEW_HEIGHT / 2);
		double angleFromPosXaxis = toRadians(90);
		if (xDis != 0)
			angleFromPosXaxis = atan(yDis / xDis);
		//quadrant to angle determination
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
		double newX = 0;
		double newY = 0;
		switch (ch) {
		case 'a':
		case 'w':
		case KEY_PRESS_UP:
		case KEY_PRESS_LEFT:
			//(getDirection() < toRadians(90)) ? GraphObject::moveAngle(toRadians(359 - (90 - getDirection()))) : GraphObject::moveAngle(toRadians(getDirection() - 90));
			//cout << (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 - 1)))) << endl;
			newX = VIEW_WIDTH / 2 + (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 + 5))));
			newY = VIEW_HEIGHT / 2 + (128 * sin((angleFromPosXaxis + toRadians(quad * 90.0 + 5))));
			if (getDirection() == 0) {
				setDirection(359);
			}
			else {
				setDirection(getDirection() + 5);
			}
			moveTo(newX, newY);
			break;
		case 'd':
		case 's':
		case KEY_PRESS_DOWN:
		case KEY_PRESS_RIGHT:
			newX = VIEW_WIDTH / 2 + (128 * (cos(angleFromPosXaxis + toRadians(quad * 90.0 - 5))));
			newY = VIEW_HEIGHT / 2 + (128 * sin((angleFromPosXaxis + toRadians(quad * 90.0 - 5))));
			if (getDirection() == 359) {
				setDirection(0);
			}
			else {
				setDirection(getDirection() - 5);
			}
			moveTo(newX, newY);
			break;
		case KEY_PRESS_SPACE:
			if (m_sprayCharge > 0) {
				Actor* temp = new Spray(getX(), getY(), getWorld(), getDirection());
				getWorld()->addActor(temp);
				getWorld()->playSound(SOUND_PLAYER_SPRAY);
				m_sprayCharge--;
			}
			break;
		case KEY_PRESS_ENTER:
			if (m_flameCharge > 0) {
				for (int i = -7; i < 8; i++) {
					int angle = getDirection() + 22 * i;
					if (angle < 0) {
						angle += 359;
					}
					else if (angle > 359) {
						angle -= 359;
					}
					Actor* temp = new Flames(getX(), getY(), getWorld(), angle);
					getWorld()->addActor(temp);
				}
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				m_flameCharge--;
			}
			break;
		}
	}
	else if (m_didNothing) {
		if (m_sprayCharge < 20) {
			m_sprayCharge++;
		}
	}
	else {
		m_didNothing = true;
	}
}

int Socrates::getSpray() const {
	return m_sprayCharge;
}

int Socrates::getFlames() const {
	return m_flameCharge;
}

void Socrates::addFlames() {
	m_flameCharge += 5;
}
//BACTERIA===========
Bacteria::Bacteria(int id, double startX, double startY, StudentWorld* sw, int health)
	: Actor(id, startX, startY, sw, 90, 0, health) {

}

int Bacteria::getFood() const {
	return m_foodEaten;
}

int Bacteria::getMove() const {
	return m_ovementPlan;
}

void Bacteria::newAngle() {

}

void Bacteria::setFood(int change) {
	m_foodEaten += change;
}

void Bacteria::move(int change) {
	m_ovementPlan += change;
}

RegSalmon::RegSalmon(double startX, double startY, StudentWorld* sw)
	: Bacteria(IID_SALMONELLA, startX, startY, sw, 4) {

}

void RegSalmon::doSomething() {
	if (!isAlive()) {
		return;
	}
	if (getWorld()->interact(this) == 1) {

	}
	else if (getFood() == 3) {
		int newX = getX() + (getX() < VIEW_WIDTH / 2) ? SPRITE_RADIUS : getX() == VIEW_WIDTH / 2 ? 0 : -SPRITE_RADIUS;
		int newY = getY() + (getY() < VIEW_HEIGHT / 2) ? SPRITE_RADIUS : getY() == VIEW_HEIGHT / 2 ? 0 : -SPRITE_RADIUS;
		getWorld()->addActor(new RegSalmon(newX, newY, getWorld()));
		setFood(-3);
	}
	else if (getWorld()->interact(this) == 0) {
		setFood(-1);
	}
	if (getMove() > 0) {
		move(-1);
		if (getWorld()->interact(this) == 2) {
			newAngle();
			return;
		}
		cout << "new angle" << endl;
		moveAngle(getDirection(), 1);
	}
	else {
		int x = -1;
		int y = -1;
		getWorld()->findFood(this, x, y);
		if (x == -1 || y == -1) {
			cout << "yes" << endl;
			newAngle();
			return;
		}
		else {
			if (getWorld()->interact(this) == 2) {
				cout << " no" << endl;
				newAngle();
			}
		}
	}
}

AggSalmon::AggSalmon(double startX, double startY, StudentWorld* sw)
	: Bacteria(IID_SALMONELLA, startX, startY, sw, 10) {

}

void AggSalmon::doSomething() {
	return;
}

Ecoli::Ecoli(double startX, double startY, StudentWorld* sw)
	: Bacteria(IID_SALMONELLA, startX, startY, sw, 5) {

}

void Ecoli::doSomething() {}

//PIT================
Pit::Pit(double startX, double startY, StudentWorld* sw)
	: Actor(IID_PIT, startX, startY, sw, 0, 1, 1) {
	m_aggroSalmon = 3;
	m_regSalmon = 5;
	m_Ecoli = 2;
	m_total = m_aggroSalmon + m_regSalmon + m_Ecoli;
}

void Pit::doSomething() {
}

//PROJECTILES==========
Projectile::Projectile(int imageID, double startX, double startY, StudentWorld* sw, int dir)
	:Actor(imageID, startX, startY, sw, dir, 1, 1) {
	m_distance = 1;
}

void Projectile::doSomething() {
	if (!isAlive()) {
		return;
	}
	if (getDistance() > 0 && getHealth() > 0) {
		if (getWorld()->interact(this) == 1) {
			updateHealth(-1);
		}
		setDistance(getDistance() - 1);
		moveAngle(getDirection(), 1);
	}
	else if (getDistance() == 0) {
		updateHealth(-1);
	}
	return;
}

void Projectile::setDistance(int dist) {
	m_distance = dist;
}

int Projectile::getDistance() const {
	return m_distance;
}
//spray
Spray::Spray(double startX, double startY, StudentWorld* sw, int dir)
	:Projectile(IID_SPRAY, startX, startY, sw, dir) {
	setDistance(120);
}

//flames
Flames::Flames(double startX, double startY, StudentWorld* sw, int dir) 
	:Projectile(IID_FLAME,startX,startY, sw, dir) {
	setDistance(32);
}


//Goodie
Goodie::Goodie(int ID, double startX, double startY, StudentWorld* sw, int life, int score)
	: Actor(ID, startX, startY, sw, 0, 1, life) {
	m_score = score;
}

void Goodie::doSomething() {
	if (!isAlive())
		return;
	if (getWorld()->interact(this) == 1) {
		if (score() != -50) {
			getWorld()->playSound(SOUND_GOT_GOODIE);
		}
		else if (score() == -50 && getWorld()->getScore() < 50) {
			updateHealth(-getHealth());
		}
		else {
			getWorld()->increaseScore(score());
			updateHealth(-getHealth());
		}
	}
	if (getHealth() > 0) {
		updateHealth(-1);
	}
}

int Goodie::score() const {
	return m_score;
}

//Health goodie
HealthGoodie::HealthGoodie(double startX, double startY, StudentWorld* sw, int life)
	: Goodie(IID_RESTORE_HEALTH_GOODIE, startX, startY, sw, life, 250) {

}

//Flame
FlameGoodie::FlameGoodie(double startX, double startY, StudentWorld* sw, int life)
	: Goodie(IID_FLAME_THROWER_GOODIE, startX, startY, sw, life, 300) {

}

//Extra Life
ExtraLife::ExtraLife(double startX, double startY, StudentWorld* sw, int life)
	: Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, sw, life, 500) {

}

//Fungus
Fungus::Fungus(double startX, double startY, StudentWorld* sw, int life)
	: Goodie(IID_FUNGUS, startX, startY, sw, life, -50) {

}

//FOOD======================
Food::Food(double startX, double startY, StudentWorld* sw)
	: Actor(IID_FOOD, startX, startY, sw, 0 , 1, 1) {

}

void Food::doSomething() {
	return;
}

//DIRT==========================
Dirt::Dirt(double startX, double startY, StudentWorld* sw)
	:Actor(IID_DIRT, startX, startY, sw, 0, 1, 1) {

}

void Dirt::doSomething() {
	return;
}
//HELPER FUNCTIONS =========================

double toRadians(int degrees) {
	const double PI = 4 * atan(1);
	return degrees * (PI / 180);
}

int toDegrees(int radians) {
	const double PI = 4 * atan(1);
	return round(radians * (180.0 / PI));
}

double findAngleRadians(double x1, double y1, double x2, double y2, int add) {
	double xDis = x2-x1;
	double yDis = y2 - y1;
	double angleFromPosXaxis = toRadians(90);
	if (xDis != 0)
		angleFromPosXaxis = atan(yDis / xDis);
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
	return angleFromPosXaxis + toRadians(quad * 90.0 + add);
}

