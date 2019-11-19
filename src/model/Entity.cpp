#include "model/Entity.h"

Entity::Entity(int health,bool life):health(health),life(life)
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

Entity::Entity(const Entity& other):health(other.health),life(other.life),fire(other.fire),timeFire(other.fire)
{
    //copy ctor
}

Entity& Entity::operator=(const Entity& other){
    if(this != &other){
        this->health = other.health;
        this->life = other.life;
        this->fire = other.fire;
        this->timeFire = other.timeFire;
    }
    return *this;
}

bool Entity::getLife(){
    if(health <= 0)
        life = false;
    return life;
}
