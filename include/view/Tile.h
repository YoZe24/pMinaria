#ifndef TILE_H
#define TILE_H

#include <model/Block.h>
#include <view/AnimationManager.h>
#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile(){}
        Tile(Block block,AnimationManager anim,int x,int y ,int w,int h);
        virtual ~Tile();
        Tile(const Tile& other);
        Tile& operator=(const Tile&);

        void load(Block block,AnimationManager anim,int x,int y, int w,int h);
        void draw(sf::RenderWindow& window,float dt);
        sf::FloatRect getRect() const;
        std::string str() const;

        int getX()const{return x;}
        int getY()const{return y;}
        float getTime(){return time;}
        float getDuration(){return block.getDuration();}
        Block& getBlock(){return block;}

        void updateTime(float timeMS);
        void updateAnimation();
    protected:

    private:
        Block block;
        AnimationManager animManager;
        int x,y,w,h;
        float time;

};

#endif // TILE_H
