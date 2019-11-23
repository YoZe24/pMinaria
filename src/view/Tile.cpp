#include "view/Tile.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

/**
*   Default constructor
*/
Tile::Tile(){
    this->block = Block({},0.0,EnumBlock::VOID);
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

/**
*   Main constructor
*
*   @param block : Set the tile's type block
*   @param anim : AnimationManager of the tile, contains all animations
*   @param x : X's position of the tile
*   @param y : Y's position of the tile
*   @param w : Width of the tile
*   @param h : Height of the tile
*/
Tile::Tile(Block block,AnimationManager anim,int x,int y, int w,int h):block(block),animManager(anim),x(x),y(y),w(w),h(h)
{
    animManager.set("stay");
    this->time = 0.0;
}

/**
*   Destructor
*/
Tile::~Tile()
{
    //dtor
}

/**
*   Copy constructor
*/
Tile::Tile(const Tile& other):block(other.block),animManager(other.animManager),x(other.x),y(other.y),w(other.w),h(other.h)
{
    //copy ctor
    this->animManager.set("stay");
    this->time = other.time;
}

/**
*   Operator= to compare 2 tiles
*/
Tile& Tile::operator=(const Tile& other){
    if(this != &other){
        this->block = other.block;
        this->animManager = other.animManager;
        this->x = other.x;
        this->y = other.y;
        this->w = other.w;
        this->h = other.h;
        this->time = other.time;
    }
    return *this;
}

/**
*   Load function to set the tile
*
*   @param block : Tile's type block
*   @param anim : AnimationManager of the tile, contains all animations
*   @param x : X's position of the tile
*   @param y : Y's position of the tile
*   @param w : Width of the tile
*   @param h : Height of the tile
*/
void Tile::load(Block block,AnimationManager anim,int x,int y, int w,int h){
    this->block = block;
    this->animManager = anim;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

/**
*
*   Update animations when the player hit a block or lava
*/
void Tile::updateAnimation(){
    if(time/1000 <= 0.05 || block.getType() == EnumBlock::LAVA)
        animManager.set("stay");
    else if(time/1000 <= block.getDuration()/3)
        animManager.set("mining1");
    else if(time/1000 <= (block.getDuration()/3) * 2 )
        animManager.set("mining2");
    else
        animManager.set("mining3");

}

/**
*   Update and draw the tile
*/
void Tile::draw(RenderWindow& window,float dt){
    updateAnimation();
    animManager.tick(dt);
    animManager.draw(window,this->x,this->y);
}

FloatRect Tile::getRect() const{
    return FloatRect(x,y,w,w);
}

string Tile::str()const{
    stringstream sstr;
    sstr << "(" << this->x << "," << this->y << ")" << this->animManager.getCurrentAnim();
    return sstr.str();
}

/**
*   Update the tile's time animation
*/
void Tile::updateTime(float timeMS){
    this->time += timeMS;
}
