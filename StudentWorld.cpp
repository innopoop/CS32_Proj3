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
    invalid_location = true;
    findNewLocation = true;
    m_level = 1;
}

int StudentWorld::init()
{
    //coordinates sent in as x, y (col, row)
    m_socrates = new Socrates(0, VIEW_HEIGHT / 2);
    m_socrates->setWorld(this);
    int dirt_piles = max(180 - 20 * m_level, 20);
    double x = 0;
    double y = 0;
    int distance = 0;
    for (int i = 0; i < dirt_piles; i++) {
        invalid_location = true;
        list<Actor*>::iterator it;
        it = m_actors.begin();
        x = randInt(0, 256);
        y = randInt(0, 256);
        while (invalid_location) {
            if (it == m_actors.end()) {
                invalid_location = false;
            }
            else if (findDistance(*it, x, y)) {
                it++;
            }
            else {
                it = m_actors.begin();
                x = randInt(0, 256);
                y = randInt(0, 256);
            } 
        }
        m_actors.push_back(new Dirt(x, y));
    }
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
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        Actor* temp = *it;
        it = m_actors.erase(it);
        delete temp;
    }
}

bool StudentWorld::findDistance(Actor* actor, int x, int y) {
    int actDist = pow(pow(actor->getX() - VIEW_RADIUS, 2) + pow(actor->getY() - VIEW_HEIGHT / 2, 2), 0.5);
    int newDist = pow(pow(x - VIEW_RADIUS, 2) + pow(y - VIEW_HEIGHT / 2, 2), 0.5);
    return abs(actDist-newDist) < 2 * SPRITE_RADIUS || newDist >= 126;
}

