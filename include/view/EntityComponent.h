#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include "view/AnimationManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "view/Tile.h"
#include "view/TileMap.h"
#include <vector>
#include "model/Player.h"
#include "model/Entity.h"

class EntityComponent
{
    public:
        EntityComponent(){}
        EntityComponent(AnimationManager& a,AnimationManager& aF,TileMap* tileMap,int X, int Y);

        virtual ~EntityComponent();
        EntityComponent& operator=(const EntityComponent& other);

        virtual void update(float time)=0;

        void draw(sf::RenderWindow& window);

        sf::FloatRect getRect()
        {
            return sf::FloatRect(x,y,w,h);
        }

        void reset();

        void updateX(float X){x += X;}
        void updateY(float Y){y += Y;}
        void updateDX(float DX){dx += DX;}
        void updateDY(float DY){dy += DY;}
        void updateTimer(float t){timer += t;}

        void setX(float X){x = X;}
        void setY(float Y){y = Y;}
        void setDX(float DX){dx = DX;}
        void setDY(float DY){dy = DY;}
        void setW(float W){w = W;}
        void setH(float H){h = H;}
        void setDir(bool b){dir = b;}
        void setEntity(Entity* e){entity = e;}
        void setTimer(float t){timer = t;}
        void setTileMap(TileMap* tm){tileMap = tm;}
        void setFire(bool b);
        void setTimerFire(float f);

        float getTimeFire()const;
        bool getFire()const;
        float getX()const{return x;}
        float getY()const{return y;}
        float getDX()const{return dx;}
        float getDY()const{return dy;}
        float getW()const{return w;}
        float getH()const{return h;}
        AnimationManager& getAnim(){return anim;}
        AnimationManager& getAnimFire(){return animFire;}
        TileMap* getTileMap(){return tileMap;}
        bool getDir()const{return dir;}
        float getTimer()const{return timer;}
        Entity* getEntity(){return entity;}
        std::string getName()const{return name;}

        void Animation(float time);
        void Fire(float time);

        void CollisionBord();
        void option(std::string NAME,Entity* e, float SPEED=0,std::string FIRST_ANIM="");


    protected:

    private:
        Entity* entity;
        float x,y,dx,dy,w,h;
        AnimationManager anim,animFire;
        TileMap* tileMap;
        bool  dir;
        float timer,timer_end;
        std::string name;
};

#endif // ENTITYCOMPONENT_H
