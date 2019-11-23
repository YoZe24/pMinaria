#include "view/EntityComponent.h"

using namespace std;

/**
*
*   Destructor
*
*   We free memory from tilemap (dynamic allocation)
*/
EntityComponent::~EntityComponent()
{
    //dtor
    delete tileMap;
}

/**
*
*   Main constructor
*
*   @param a : AnimationManager to set the animations
*   @param af : AnimationManager for the fire's animations (superimpose the fire animation and the player animation)
*   @param tileMap : The game map with tiles (blocks)
*   @param x : X position to set the entity's animation
*   @param y : Y position to set the entity's animation
*/
EntityComponent::EntityComponent(AnimationManager& a,AnimationManager& af,TileMap* tileMap,int X, int Y):anim(a),animFire(af),tileMap(tileMap){
    x = X;
    y = Y;
    dir = 0;
    dx=dy=0;
    timer = 0;
}

/**
*   Operator= to compare 2 entities
*/
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

/**
*
*
*/
void EntityComponent::option(std::string NAME, Entity* e, float SPEED, std::string FIRST_ANIM)
{
    entity = e->clone();
    name = NAME;
    if (FIRST_ANIM!="") anim.set(FIRST_ANIM);
    w = anim.getW();
    h = anim.getH();
    dx = SPEED;
}

/**
*
*   Reset health function
*
*   When the player is dead, we reset his life and his position
*
*   @param health : Player's health
*/
void EntityComponent::reset(int Health){
    x = 0;
    y = 0;
    entity->setHealth(Health);
    entity->setLife(true);
}

/**
*
*   Draw the the entity
*
*   If the entity (player or enemies) is burning, we draw the animation with the fire's AnimationManager
*
*   @param window : Game's window to draw our entity
*/
void EntityComponent::draw(sf::RenderWindow &window)
{
    anim.draw(window,x,y - 6);
    if(getFire())
        animFire.draw(window,getX(),getY()-getH()/3);
}

/**
*
*   Function to set tileMap's border
*
*   We set the borders for the map and the entity can't walk out the game zone.
*   If the entities leave the map, they are teleported into the game zone
*
*/
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
//    else if(getY() >= tileMap.getHeight() * tileMap.getTileSize())
//        setY(tileMap.getHeight() * tileMap.getTileSize());
    else if(getY() >= tileMap.getHeight() * tileMap.getTileSize() + 2000)
        getEntity()->setHealth(0);
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

/**
*
*   Set fire on the entity
*
*   If the entity is in fire, we set the animation's fire to true.
*
*   @param time : Value time's animation
*/
void EntityComponent::Animation(float time){
    if(getFire()) animFire.set("fire"); setFire(false);
    animFire.tick(time);
}

/**
*
*   Logic function when entity's burning
*
*   If the entity is burning, he takes damages and looses life points
*
*   @param time : Value time's animation
*/
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
