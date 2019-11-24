#ifndef PLAYER_H
#define PLAYER_H

#include "model/Entity.h"
#include "model/Pickaxe.h"
#include <map>

class Player : public Entity
{
    public:
        Player(int health = 0,bool life = true);
        virtual ~Player();
        Player(const Player& other);
        Player& operator=(const Player&);

        virtual Player* clone(){return new Player(*this);}
        virtual void reset();

        float updatePickaxe();
        EnumPickaxe getType()const;

        std::map<int,int> getOres()const{return ores;}
        Pickaxe getPickaxe()const{return pickaxe;}
        bool isBreakable(EnumBlock eb){return pickaxe.isBreakable(eb);}
        int getNbOresCraftCurrentPickaxe();
        int getNbOresCurrentPickaxe();

        void setOres(int key){ores[key-1]++;};
    protected:

    private:
        Pickaxe pickaxe;
        std::map<int,int> ores;
};

#endif // PLAYER_H
