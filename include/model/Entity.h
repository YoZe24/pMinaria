#ifndef ENTITY_H
#define ENTITY_H

#include "model/Block.h"
#include <iostream>

class Entity
{
    public:
        Entity(int health = 100,bool life = true);
        virtual ~Entity();
        Entity(const Entity& other);
        Entity& operator=(const Entity&);
//        virtual Entity* clone(){return new Entity(*this);}
        virtual Entity* clone() = 0;

        void updateHealth(int Health){health += Health;}
        void updateTimeFire(float t){timeFire += t;}

        void setHealth(int Health){health = Health;}
        void setLife(bool b){life = b;}
        void setFire(bool b){fire = b;}
        void setTimeFire(float f){timeFire = f;}

        virtual void setOres(int key){};
        virtual bool isBreakable(EnumBlock eb){};

        float getTimeFire()const{return timeFire;}
        bool getFire()const{return fire;}
        int getHealth()const{return health;}
        bool getLife();
        virtual void reset();

    protected:

    private:
        bool life,fire;
        int health;
        float timeFire;
};

#endif // ENTITY_H
