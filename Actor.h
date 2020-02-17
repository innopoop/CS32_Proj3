#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class GameWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
	Actor(int imageID, double startX, double startY, int dir = 0 , int depth = 0);
	virtual ~Actor();
	virtual void doSomething() = 0;
	bool isAlive() const;
	void isDead();
	void setWorld(GameWorld* gw);
	GameWorld* getWorld() const;
private:
	bool m_alive;
	GameWorld* m_gw;
};

class Socrates : public Actor {
public:
	Socrates(double startX, double startY);
	virtual ~Socrates();
	virtual void doSomething();
private:
	int m_sprayCharge;
	int m_flameCharge;
	int m_health;
};

//fungus (?)
//regular salmonella
//aggressive salmonella
//e.coli
//class Enemy : public Actor {
//public:
//	Enemy(int startX, int startY, int dir);
//private:
//};
//
////holds bacterias
//class Pit : public Actor {
//public:
//private:
//};
//
////disinfectant spray
////flame
//class Projectile : public Actor {
//public:
//private:
//};
//
////health goodie
////flame thrower goodie
////extra life goodie
//class Goodies : public Actor {
//public:
//private:
//};

//holds food & dirt
class Misc : public Actor {
public:
	Misc(int imageID, double startX, double startY, Direction dir = 0, int depth = 1);

	virtual void doSomething() = 0;
private:
};

class Dirt : public Misc {
public:
	Dirt(double startX, double startY);
	virtual void doSomething();
private:
};
#endif // ACTOR_H_
