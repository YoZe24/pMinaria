#include "model/Enemy.h"
using namespace std;
Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(int health,bool life,vector<float> s):Entity(health,life),spawn(s)
{}

Enemy::~Enemy()
{
    //dtor
}

Enemy::Enemy(const Enemy& other):Entity(other),spawn(other.spawn)
{
    //copy ctor
}

Enemy& Enemy::operator=(const Enemy& other){
    if(this != &other){
        Entity::operator=(other);
        this->spawn = other.spawn;
    }
    return *this;
}
