#include "view/EnemyComponent.h"

using namespace std;

/**
*
*   Main constructor
*
*   @param a : AnimationManager to set the animations
*   @param af : AnimationManager for the fire's animations (superimpose the fire animation and the player animation)
*   @param tm : The game map with tiles (blocks)
*   @param x : X position to set the entity's animation
*   @param y : Y position to set the entity's animation
*   @param s : Spawning vector to set the enemy's position
*/
EnemyComponent::EnemyComponent(AnimationManager& a,AnimationManager& af,TileMap* tm,int x, int y,vector<float> s):EntityComponent(a,af,tm,x,y)
{
    Enemy* e = new Enemy(60,true,s);
    load("Enemy",e,0.05,"move");
    getAnim().set("move");
    setFire(false);
    setTimerFire(0);
}

/**
*
*   Destructor
*/
EnemyComponent::~EnemyComponent()
{
    //dtor
}

/**
*
*   Copy constructor
*/
EnemyComponent::EnemyComponent(const EnemyComponent& other):EntityComponent(other)
{
    //option("Enemy",other.entity,10,"move");
    cout << "test";
}

vector<float> EnemyComponent::getSpawn(){
    Enemy* enemy = dynamic_cast<Enemy*>(getEntity());
    return enemy->getSpawn();
}

/**
*
*   Change direction function
*
*   We change the enemy's direction and flip his animation
*/
void EnemyComponent::swapDir(){
    if(getDir()){
        setDX( getDX() < 0 ? getDX() : getDX() * -1);
    }else{
        setDX( getDX() > 0 ? getDX() : getDX() * -1);
    }
    getAnim().flip(getDir());

}

/**
*
*   Update the entity's movement and his animation
*
*   We call the collision function to set the interactions between the entity and map's blocks.
*
*   @param time : Value's time animation
*/
void EnemyComponent::update(float time){
    swapDir();

    Fire(time);
    EntityComponent::Animation(time);
    getAnim().tick(time);

    updateDY(0.0005 *time);

    updateX(getDX() * time);
    Collision(0);

    updateY(getDY() * time);
    Collision(1);
}

/**
*   Test if the entity is colliding with one block situated between his position minus
*   2 * tilemap_width and plus 2 * tilemap_width => If width is 50 and the entity is at
*   the position 250 the method will test from tile 150 to tile 350
*   @param int num: index to know if we test colliding on X (num = 0) or Y (num = 1) axis
*/
void EnemyComponent::Collision(int num){
    TileMap& tileMap = *getTileMap();

    int posX = getX()/tileMap.getTileSize();
    int posY = getY()/tileMap.getTileSize();
    int pos = posX + posY * tileMap.getWidth();

    map<int,Tile>::iterator itFinish = tileMap.getItFinish(pos);
    for(auto i = tileMap.getItStart(pos); i != itFinish; i++){

        sf::FloatRect fr = i->second.getRect();
        if(getRect().intersects(fr)){
            EnumBlock block = i->second.getBlock().getType();

            if(block == EnumBlock::LAVA){
                    setFire(true);
                    getAnimFire().play();
            }else{
                if (getDY()>0 && num==1){
                    setY(fr.top -  getH());
                    setDY(0);
                }
                if (getDY()<0 && num==1){
                    setY(fr.top + fr.height);
                    setDY(0);
                }
                if (getDX()>0 && num==0){
                    setX(fr.left -  getW());
                    setDir(true);
                }
                if (getDX()<0 && num==0){
                    setX(fr.left + fr.width);
                    setDir(false);
                }
            }
        }
    }
    CollisionBord();
}
