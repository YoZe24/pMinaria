#include "view/EntityComponent.h"

using namespace std;

EntityComponent::~EntityComponent()
{
    //dtor
    delete tileMap;
}

EntityComponent::EntityComponent(AnimationManager& a,AnimationManager& af,TileMap* tileMap,int X, int Y):anim(a),animFire(af),tileMap(tileMap){
    x = X;
    y = Y;
    dir = 0;
    dx=dy=0;
    timer = 0;
}

EntityComponent& EntityComponent::operator=(const EntityComponent& other){
    if(this != &other){
        this->anim = other.anim;
        this->animFire = other.animFire;
        this->tileMap = other.tileMap;
        this->x = x;
        this->y = y;
        this->dir = other.dir;
        this->dx = other.dx;
        this->dy = other.dy;
        this->timer = other.timer;
    }
    return *this;
}

void EntityComponent::option(std::string NAME, Entity* e, float SPEED, std::string FIRST_ANIM)
{
    entity = e->clone();
    name = NAME;
    if (FIRST_ANIM!="") anim.set(FIRST_ANIM);
    w = anim.getW();
    h = anim.getH();
    dx = SPEED;
}

void EntityComponent::reset(int Health){
    x = 0;
    y = 0;
    entity->setHealth(Health);
    entity->setLife(true);
}

void EntityComponent::draw(sf::RenderWindow &window)
{
    anim.draw(window,x,y - 6);
    if(getFire())
        animFire.draw(window,getX(),getY()-getH()/3);
}

void EntityComponent::CollisionBord(){
    TileMap& tileMap = *getTileMap();
    if(getX() <= 0){
        setX(0);
        dir = false;
    }
    else if(getX() >= tileMap.getWidth() * tileMap.getTileSize() - getW()){
        setX(tileMap.getWidth() * tileMap.getTileSize() - getW());
        dir = true;
    }
    if(getY() <= -100)
        setY(-100);
    else if(getY() >= tileMap.getHeight() * tileMap.getTileSize())
        setY(tileMap.getHeight() * tileMap.getTileSize());
}

void EntityComponent::setFire(bool b){
    entity->setFire(b);
}

void EntityComponent::setTimerFire(float f){
    entity->setTimeFire(f);
}

bool EntityComponent::getFire()const{
    return entity->getFire();
}

float EntityComponent::getTimeFire()const{
    return entity->getTimeFire();
}

void EntityComponent::Animation(float time){
    if(getFire()) animFire.set("fire"); setFire(false);
    animFire.tick(time);
}

void EntityComponent::Fire(float time){
    if(getFire()){
        if(getTimeFire() == 0.0) entity->updateHealth(-20);
            entity->updateTimeFire(time);
        if(getTimeFire()/2000 >= 1.00) {
            entity->updateHealth(-20);
            entity->setTimeFire(0);
        }
    }else{
        entity->setTimeFire(0);
    }
}
