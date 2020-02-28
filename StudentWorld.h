#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

    //SELF-DEFINED FUNCTIONS
    void addActor(Actor* actor);
    int interact(Actor* actor);
    void pitCleared();
    void findFood(Actor* actor, int& x, int& y);
private:
    int findDistance(double x1, double y1, double x2, double y2);
    bool inDish(double x1, double y1);
    bool overlap(double x1, double y1, double x2, double y2);
    void getValidPoints(double& x1, double& y1, int end = 0);
    double toRadians(int degrees);

    std::vector<Actor*> m_actors;
    Socrates* m_socrates;

    int m_nPits;
    int m_nDirt;
    int m_nFood;
    int m_count;
    int m_chanceFungus;
    int m_chanceGoodie;
};

#endif // STUDENTWORLD_H_
