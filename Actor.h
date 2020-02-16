#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
	Actor(int imageID, double startX, double startY, int dir = 0 , int depth = 0);
	virtual void doSomething() = 0;
	virtual bool isAlive();
private:
	bool m_alive;
};
class HealthActor : public Actor {
public:
	HealthActor(int imageID, double startX, double startY, int dir = 0, int depth = 0);
private:
	int m_health;
};
class Socrates : public HealthActor {
public:
	Socrates(int startX, int startY, int dir) :HealthActor(IID_PLAYER, startX, startY, dir){}
private:
	int m_sprayCharge;
	int m_flameCharge;
};

//fungus (?)
//regular salmonella
//aggressive salmonella
//e.coli
class Enemy : public HealthActor {
public:
private:
};

//holds bacterias
class Pit : public Actor {
public:
private:
};

//disinfectant spray
//flame
class Projectile : public Actor {
public:
private:
};

//health goodie
//flame thrower goodie
//extra life goodie
class Goodies : public Actor {
public:
private:
};

//holds food & dirt
class Misc : public Actor {
public:
private:
};
#endif // ACTOR_H_
