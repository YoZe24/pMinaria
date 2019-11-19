#ifndef ENEMY_H
#define ENEMY_H

#include "model/Entity.h"

class Enemy : public Entity
{
    public:
        Enemy();
        Enemy(int health = 100,bool life = true,std::vector<float> s = {});
        virtual ~Enemy();
        Enemy(const Enemy& other);
        Enemy& operator=(const Enemy& e);

        virtual Enemy* clone(){return new Enemy(*this);}
        std::vector<float> getSpawn(){return spawn;}

    protected:

    private:
        std::vector<float> spawn;

};

#endif // ENEMY_H
