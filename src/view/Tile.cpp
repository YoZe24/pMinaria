#include "view/Tile.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;
Tile::Tile(Block block,AnimationManager anim,int x,int y, int w,int h):block(block),animManager(anim),x(x),y(y),w(w),h(h)
{
    animManager.set("stay");
    this->time = 0.0;
}

Tile::~Tile()
{
    //dtor
}

Tile::Tile(const Tile& other):block(other.block),animManager(other.animManager),x(other.x),y(other.y),w(other.w),h(other.h)
{
    //copy ctor
    this->animManager.set("stay");
    this->time = other.time;
}

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

void Tile::load(Block block,AnimationManager anim,int x,int y, int w,int h){
    this->block = block;
    this->animManager = anim;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

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

void Tile::updateTime(float timeMS){
    this->time += timeMS;
}
