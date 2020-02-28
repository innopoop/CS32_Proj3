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
    m_nPits = 0;
    m_nDirt = 0;
    m_nFood = 0;
    m_count = 0;
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init()
{
    //intialization of socrates and the world variables
    m_socrates = new Socrates(this);
    m_nPits = getLevel();
    m_nDirt = max(180 - 20 * getLevel(), 20);
    m_nFood = min(5 * getLevel(), 25);
    m_chanceFungus = min(510 - getLevel() * 10, 200);
    m_chanceGoodie = min(510 - getLevel() * 10, 250);

    //temp variables to hold x and y coordinates
    double x = 0;
    double y = 0;

    //Create pits first
    for (int i = 0; i< m_nPits; i++) {
        if (i == 0) {
            while (!inDish(x, y)) {
                x = randInt(0, VIEW_WIDTH);
                y = randInt(0, VIEW_HEIGHT);
            }
        }
        else {
            getValidPoints(x, y);
        }
        m_actors.push_back(new Pit(x, y, this));
    }
    //create foods next
    for (int i = 0; i < m_nFood; i++) {
        getValidPoints(x, y);
        m_actors.push_back(new Food(x, y, this));
    }
    //dirt
    for (int i = 0; i < m_nDirt; i++) {
        getValidPoints(x, y, m_nFood + m_nPits);
        m_actors.push_back(new Dirt(x, y, this));
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    if (m_nPits == 0) {
        return GWSTATUS_FINISHED_LEVEL;
    }
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    Actor* temp;
    while (it != m_actors.end()) {
        if (!(*it)->isAlive()) {
            temp = *it;
            it = m_actors.erase(it);
            delete temp;
        }
        else {
            (*it)->doSomething();
            it++;
        }
    }
    if (!m_socrates->isAlive()) {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    m_socrates->doSomething();
    if (randInt(0, m_chanceFungus) == 0) {
        int angle = randInt(0, 359);
        m_actors.push_back(new Fungus(128 * cos(toRadians(angle)) + VIEW_WIDTH / 2, 128 * sin(toRadians(angle)) + VIEW_HEIGHT / 2, this, max(rand() % (300 - 10 * getLevel()), 50)));
    }
    if (randInt(0, m_chanceGoodie) == 0) {
        int angle = randInt(0, 359);
        if (angle < 6 * 36) {
            m_actors.push_back(new HealthGoodie(128 * cos(toRadians(angle)) + VIEW_WIDTH / 2, 128 * sin(toRadians(angle)) + VIEW_HEIGHT / 2, this, max(rand() % (300 - 10 * getLevel()), 50)));
        }
        else if (angle < 9 * 36) {
            m_actors.push_back(new FlameGoodie(128 * cos(toRadians(angle)) + VIEW_WIDTH / 2, 128 * sin(toRadians(angle)) + VIEW_HEIGHT / 2, this, max(rand() % (300 - 10 * getLevel()), 50)));
        }
        else {
            m_actors.push_back(new FlameGoodie(128 * cos(toRadians(angle)) + VIEW_WIDTH / 2, 128 * sin(toRadians(angle)) + VIEW_HEIGHT / 2, this, max(rand() % (300 - 10 * getLevel()), 50)));
        }
    }
    for (int i = 0; i < m_actors.size(); i++) {
        m_actors[i]->doSomething();
    }
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    for (; it != m_actors.end();) {
        delete* it;
        it = m_actors.erase(it);
    }
    //DON'T FORGET TO DEALLOCATE THE PLAYER
    delete m_socrates;
}
//public functions
void StudentWorld::addActor(Actor* actor) {
    m_actors.push_back(actor);
}

int StudentWorld::interact(Actor* actor) {
    //socrates touches goodies
    if (actor->score() != 0 && actor->isEdible() && overlap(actor->getX(), actor->getY(), m_socrates->getX(), m_socrates->getY())) {
        switch (actor->score()) {
        case -50:
            m_socrates->updateHealth(-20);
        case 250:
            m_socrates->updateHealth((-m_socrates->getHealth()) + 100);
            break;
        case 300:
            m_socrates->addFlames();
            break;
        case 500:
            incLives();
            break;
        }
        return 1;
    }
    //projectiles hit
    else if (!actor->canBeHit()) {
        for (int i = getLevel(); i < m_actors.size(); i++) {
            if (m_actors[i]->canBeHit())
                //goodies
                if (m_actors[i]->isEdible() && overlap(actor->getX(), actor->getY(), m_actors[i]->getX(), m_actors[i]->getY())) {
                    actor->updateHealth(-actor->getHealth());
                    m_actors[i]->updateHealth(-m_actors[i]->getHealth());
                    return 0;
                }
            //dirt
                else if (overlap(actor->getX(), actor->getY(), m_actors[i]->getX(), m_actors[i]->getY())) {
                    m_actors[i]->updateHealth(actor->damage());
                    return 1;
                }
            //bacteria
                else if (!m_actors[i]->isEdible() && !m_actors[i]->canBlock()) {
                    m_actors[i]->updateHealth(-m_actors[i]->getHealth());
                }
        }
    }
    //bacteria hits socrates
    else if (!actor->canBlock() && actor->canBeHit() && overlap(actor->getX(), actor->getY(), m_socrates->getX(), m_socrates->getY())) {
        cout << "bacteria hits socrates" << endl;
        m_socrates->updateHealth(m_socrates->getHealth() + actor->damage());
        if (m_socrates->isAlive()) {
            playSound(SOUND_PLAYER_HURT);
        }
        else {
            playSound(SOUND_PLAYER_DIE);
        }
        return 1;
    }
    //bacteria hits food
    else if (!actor->canBlock() && actor->canBeHit()) {
        for (int i = getLevel(); i < m_actors.size(); i++) {
            if (m_actors[i]->isEdible() && !m_actors[i]->canBeHit() && overlap(actor->getX(), actor->getY(), m_actors[i]->getX(), m_actors[i]->getY())) {
                m_actors[i]->updateHealth(-1);
                return 0;
            }
        }
    }
    //bacteria hits dirt
    else if (!actor->canBlock()) {
        for (int i = getLevel(); i < m_actors.size(); i++) {
            if (m_actors[i]->canBlock()) {
                int newX = actor->getX() + 3 * cos(toRadians(actor->getDirection()));
                int newY = actor->getY() + 3 * sin(toRadians(actor->getDirection()));
                if (findDistance(m_actors[i]->getX(), m_actors[i]->getY(), newX, newY) < SPRITE_WIDTH || findDistance(newX, newY, VIEW_WIDTH / 2, VIEW_HEIGHT / 2) >= VIEW_RADIUS - SPRITE_WIDTH) {
                    return 2;
                }
            }
        }
    }
    return -1;
}

void StudentWorld::pitCleared() {
    m_nPits--;
}

void StudentWorld::findFood(Actor* actor, int& x, int& y) {
    int smallest = 128;
    for (int i = getLevel(); i < m_actors.size(); i++) {
        if (m_actors[i]->isEdible() && !m_actors[i]->canBeHit()) {
            if (findDistance(m_actors[i]->getX(), m_actors[i]->getY(), actor->getX(), actor->getY() <= smallest)) {
                x = m_actors[i]->getX();
                y = m_actors[i]->getY();
            }
        }
    }
}
//HELPER FUNCTIONS

bool StudentWorld::overlap(double x1, double y1, double x2, double y2) {
    return findDistance(x1, y1, x2, y2) < SPRITE_WIDTH;
}

int StudentWorld::findDistance(double x1, double y1, double x2, double y2 ) {
    return pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
}

bool StudentWorld::inDish(double x1, double y1) {
    return findDistance(x1, y1, VIEW_WIDTH / 2, VIEW_HEIGHT / 2) < VIEW_RADIUS - SPRITE_WIDTH;
}

void StudentWorld::getValidPoints(double& x1, double& y1, int end) {
    x1 = randInt(0, VIEW_WIDTH);
    y1 = randInt(0, VIEW_HEIGHT);
    if (end == 0) {
        end = m_actors.size();
    }
    while (true) {
        for (int j = 0; j < end; j++) {
            //if distance between center and location >= 120 or overlaps with others find new coordinates
            if (!inDish(x1, y1) || overlap(x1, y1, m_actors[j]->getX(), m_actors[j]->getY())) {
                x1 = randInt(0, VIEW_WIDTH);
                y1 = randInt(0, VIEW_HEIGHT);
                j = 0;
            }
            //otherwise valid location
        }
        if (inDish(x1, y1))
            return;
    }
}

double StudentWorld::toRadians(int degrees) {
    const double PI = 4 * atan(1);
    return degrees * (PI / 180);
}
