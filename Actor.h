#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
	//base
	Actor(int imageID, double startX, double startY, StudentWorld* sw, int dir, int depth, int health);
	virtual ~Actor();
	virtual void doSomething() = 0;

	//virtual functions
	virtual bool canBlock() const { return false; }
	virtual bool canBeHit() const { return false; }
	virtual bool isEdible() const { return false; }
	virtual int damage() { return 0; }
	virtual int score() const { return 0; }

	//non virtual functions
	void updateHealth(int health);
	int getHealth() const;
	bool isAlive() const;
	StudentWorld* getWorld() const;

private:
	StudentWorld* m_gw;
	int m_health;
};

class Socrates : public Actor {
public:
	Socrates(StudentWorld* sw);
	virtual ~Socrates();
	virtual void doSomething();

	int getSpray() const;
	int getFlames() const;
	void addFlames();
private:
	int m_sprayCharge;
	int m_flameCharge;

	bool m_didNothing;
};
class Bacteria : public Actor {
public:
	Bacteria(int id, double startX, double startY, StudentWorld* sw, int health);
	bool canBeHit() const { return true; }
	int getFood() const;
	int getMove() const;

	void newAngle();
	void setFood(int change);
	void move(int change);
private:
	int m_foodEaten;
	int m_ovementPlan;

	Pit* m_dad;
};

class RegSalmon : public Bacteria {
public:
	RegSalmon(double startX, double startY, StudentWorld* sw);
	void doSomething();
	int damage() const { return -1; }
};

class AggSalmon : public Bacteria {
public:
	AggSalmon(double startX, double startY, StudentWorld* sw);
	void doSomething();
	int damage() const { return -2; }
};

class Ecoli : public Bacteria {
public:
	Ecoli(double startX, double startY, StudentWorld* sw);
	void doSomething();
	int damage() const { return -4; }
};

////holds bacterias
class Pit : public Actor {
public:
	Pit(double startX, double startY, StudentWorld* sw);
	void doSomething();
private:
	int m_aggroSalmon;
	int m_regSalmon;
	int m_Ecoli;
	int m_total;
};
//
////disinfectant spray
////flame
class Projectile : public Actor {
public:
	Projectile(int imageID, double startX, double startY, StudentWorld* sw, int dir);
	void doSomething();
	void setDistance(int dist);
	int getDistance() const;

private:
	int m_distance;
};

class Spray : public Projectile {
public:
	Spray(double startX, double startY, StudentWorld* sw, int dir);
	virtual int damage() { return -2; }
private:
};

class Flames : public Projectile {
public:
	Flames(double startX, double startY, StudentWorld* sw, int dir);
	virtual int damage() { return -5; }
private:
};
//
////health goodie
////flame thrower goodie
////extra life goodie
class Goodie : public Actor {
public:
	Goodie(int ID, double startX, double startY, StudentWorld* sw, int life, int score);
	virtual void doSomething();
	virtual bool isEdible() const { return true; }
	virtual bool canBeHit() const { return true; }
	int score() const;
private:
	int m_score;
};

class HealthGoodie : public Goodie {
public:
	HealthGoodie(double startX, double startY, StudentWorld* sw, int life);
private:
};

class FlameGoodie : public Goodie {
public:
	FlameGoodie(double startX, double startY, StudentWorld* sw, int life);
};

class ExtraLife : public Goodie {
public:
	ExtraLife(double startX, double startY, StudentWorld* sw, int life);
};

class Fungus : public Goodie {
public:
	Fungus(double startX, double startY, StudentWorld* sw, int life);
};

class Food : public Actor {
public:
	Food(double startX, double startY, StudentWorld* sw);
	virtual bool isEdible() const { return true; }
	void doSomething();
private:
};

class Dirt : public Actor {
public:
	Dirt(double startX, double startY, StudentWorld* sw);
	virtual void doSomething();
	virtual bool canBeHit() const { return true; }
	virtual bool canBlock() const { return true; }
private:
};


#endif // ACTOR_H_
