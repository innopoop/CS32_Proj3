#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath)
{   
    m_level = 1;
}

int StudentWorld::init()
{
    m_socrates = new Socrates(0, VIEW_HEIGHT / 2);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    list<Actor*>::iterator it;
    it = m_actors.begin();
    m_socrates->doSomething();
    while (it != m_actors.end()) {
        (*it)->doSomething();
        it++;
    }
    decLives();
    if(!m_socrates->isAlive())
        return GWSTATUS_PLAYER_DIED;

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}
