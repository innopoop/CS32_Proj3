#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
class Actor;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();

private:
    bool findDistance(Actor* actor, int x, int y);
    std::list<Actor*> m_actors;
    Actor* m_socrates;

    bool invalid_location;
    int m_level;
};

#endif // STUDENTWORLD_H_
