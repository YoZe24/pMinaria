#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "view/EntityComponent.h"
#include <iostream>
#include "HealthBar.h"
#include "model/GestionUser.h"

class PlayerComponent: public EntityComponent
{
    public:
        PlayerComponent():EntityComponent(){}
        enum{stay,walk,jump,mining} STATE;
        PlayerComponent(AnimationManager &a,AnimationManager& animFire,TileMap* tileMap,int x,int y);
        virtual ~PlayerComponent();
        PlayerComponent& operator=(const PlayerComponent& other);

        void updateStrAnimation(std::string i);
        void keyboard();
        void Animation(float time);
        void update(float time);
        void Collision(int num);
        void hittedByMob();

        void draw(sf::RenderWindow& window);

        void setHitByMob(bool b){hitByMob = b;}

        bool isMinable(int x,int y);
        bool tryToDeleteAt(int x,int y);
        bool getHitByMob()const{return hitByMob;}
        bool getHit()const{return hit;}
        std::map<std::string,bool> getKey(){return key;}

        void setKey(std::string key,bool state);
    protected:

    private:
        float power,time;
        bool hit,miningDown,hitByMob;
        EnumBlock lastBlockMined;
        HealthBar healthBar;
        std::map<std::string,bool> key;
        std::string walkStr,stayStr,jumpStr,miningStr;

};

#endif // PLAYERCOMPONENT_H
