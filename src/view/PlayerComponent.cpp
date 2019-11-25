#include "view/PlayerComponent.h"
#include <cmath>

using namespace std;

/**
*   Constant variable to set the gravity for the entity's fall
*/
const float GRAVITY = 0.0005;

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
PlayerComponent::PlayerComponent(AnimationManager &a,AnimationManager& animFire, TileMap* tileMap,int x,int y):EntityComponent(a,animFire,tileMap,x,y){
    Player* p = new Player(100,true);
    updateStrAnimation("0");
    load("Player",p,0,stayStr);

    STATE=stay;
    miningDown = false;
    hit=false;
    setFire(false);
    setTimerFire(0);


}

/**
*
*   Destructor
*/
PlayerComponent::~PlayerComponent()
{

}

/**
*   Operator= to compare 2 entities
*/
PlayerComponent& PlayerComponent::operator=(const PlayerComponent& other){
    if(this != &other){
        EntityComponent::operator=(other);
        Player* p = new Player(100,true);
        updateStrAnimation("0");
        load("Player",p,0,stayStr);

        STATE=stay;
        miningDown = false;
        hit=false;
        setFire(false);
        setTimerFire(0);

    }
    return *this;
}

/**
*   Update variables player's actions for his animations
*
*   We define the value with the action and the position number from the sprite sheet
*
*   @param i : The animation's position in the sprite sheet
*/
void PlayerComponent::updateStrAnimation(string i){
    walkStr = "walk"+i;
    stayStr = "stay"+i;
    jumpStr = "jump"+i;
    miningStr = "mining"+i;
}

/***/
void PlayerComponent::setKey(string strKey,bool state){
    key[strKey]=state;
}

/**
*
*   User's interactions with the keyboard
*
*   We set the direction when the user uses the keyboard.
*   We update the player's state and adapt the animation (in the function Animation)
*/
void PlayerComponent::keyboard(){
    if(key["Q"]){
        setDir(1);
        setDX(-0.1);
        if(STATE == stay) STATE = walk;
    }
    if(key["D"]){
        setDir(0);
        setDX(0.1);
        if(STATE == stay) STATE = walk;
    }
    if(key["Z"]){
        if(STATE == stay || STATE == walk){
            setDY(-0.27);
            STATE = jump;
            //anim.play("jump");
        }
    }
    if(key["S"]){
        if(STATE == stay || STATE == walk){
            setDX(0);
            //STATE = mining;
            miningDown = true;

        }
    }else
        miningDown = false;


    if (!(key["Q"] || key["D"]))
    {
        setDX(0);
        if (STATE==walk) STATE=stay;
    }

    key["Z"]=key["Q"]=key["D"]=key["S"]=false;
}

/**
*   Draw function
*/
void PlayerComponent::draw(sf::RenderWindow& window){
    EntityComponent::draw(window);
    healthBar.draw(window);
}

/**
*
*   Update the player's animation in function user's interactions(keyboard function)
*
*   @param time : Value's time animation
*/
void PlayerComponent::Animation(float time){
    AnimationManager& anim = getAnim();
    if(STATE == stay) anim.set(stayStr);
    if(STATE == walk) anim.set(walkStr);
    if(STATE == jump) anim.set(jumpStr);
    if(STATE == mining) anim.set(miningStr);

    if(hitByMob) {
        updateTimer(time);
        if(getTimer()>1000){
            hitByMob = false;
            setTimer(0);
        }
        anim.set(jumpStr);
    }
    if(hit) anim.set(miningStr); hit = false;
    if(getDir()) anim.flip();

    EntityComponent::Animation(time);
    anim.tick(time);
}

void PlayerComponent::hittedByMob(){
    getEntity()->updateHealth(-25);
    setDY(-0.17);
    if(getDir())
       updateX(10);
    else
        updateX(-10);
}

/**
*
*   Update all player's values
*
*   We check the player's life and reset his life.
*   We update his animation and texture when he gains a level.
*   The player gets power in function of this level.
*   We call the collision function to set the interactions between the entity and map's blocks.
*
*   @param time : Value's time animation
*/
void PlayerComponent::update(float time){
    sf::Clock c;
    if(!getEntity()->getLife()){
        //reset();
    }

    Player* player = dynamic_cast<Player*>(getEntity());
    power = player->updatePickaxe();
    updateStrAnimation(to_string(player->getType()));

    Fire(time);
    keyboard();
    healthBar.update(getEntity()->getHealth());

    Animation(time);

    updateDY(GRAVITY * time);

    updateX(getDX() * time);
    Collision(0);

    updateY(getDY() * time);
    Collision(1);

}

/**
*
*/
void PlayerComponent::Collision(int num){
    TileMap& tileMap = *getTileMap();
    int pos = tileMap.getPos(getX(),getY());
    int xD,yD;
    map<int,Tile>::iterator itFinish = tileMap.getItFinish(pos);
    for(auto i = tileMap.getItStart(pos) ; i != itFinish ; i++){
            sf::FloatRect fr = i->second.getRect();
            if(getRect().intersects(fr)){

                //If i'm colliding with LavaBlock
                if(i->second.getBlock().getType() == EnumBlock::LAVA){
                    //If i'm in LavaBlock (don't trigger if i'm above)
                    if(getY() > i->second.getY()){
                        setFire(true);
                        getAnimFire().play();
                    }
                }else{
                    if (getDY()>0 && num==1){
                        setY(fr.top -  getH());
                        setDY(0);
                        STATE=stay;
                        xD = getX() + getW() / 2;       yD = getY() + getH();

                        if(isMinable(xD,yD) && miningDown){
                            if(tryToDeleteAt(xD,yD)) break;
                        }
                    }
                    if (getDY()<0 && num==1){
                        setY(fr.top + fr.height);
                        setDY(0);
                        xD = getX() + getW() / 2;       yD = getY() - getH();

                        if(isMinable(xD,yD))
                            if(tryToDeleteAt(xD,yD)) break;

                    }
                    if (getDX()>0 && num==0)	{
                        setX(fr.left -  getW());
                        xD = getX() + getW() ;          yD = getY() - 4;
                        if(isMinable(xD,yD))
                            if(tryToDeleteAt(xD,yD)) break;

                    }

                    if (getDX()<0 && num==0){
                        setX(fr.left + fr.width);
                        xD = getX() - getW() ;          yD = getY() - 4;
                        if(isMinable(xD,yD))
                            if(tryToDeleteAt(xD,yD)) break;

                    }
                }
            }
    }
    CollisionBord();
}

/**
*
*   Test function to check if the block can be deleted from the tile map
*
*   @param x : X's position of the block
*   @param y : Y's position of the block
*
*   @return value : Return if the block at the position x,y can be removed from the tile map
*/
bool PlayerComponent::tryToDeleteAt(int x,int y){

    EnumBlock blockMined = getTileMap()->deleteTileAt(x,y,power);
    hit = blockMined == EnumBlock::VOID;
    if(!hit){
        if(blockMined != EnumBlock::DIRT)
            getEntity()->setOres(blockMined);
        return true;
    }
    return false;
}

/**
*
*   Test function to check if the block is destroyable by the player
*
*   @param x : X's position of the block
*   @param y : Y's position of the block
*
*   @return value : Return if the block is breakable by the player
*/
bool PlayerComponent::isMinable(int x,int y){
    EnumBlock blockToMine = getTileMap()->getEnumBlockAt(x,y);
    return getEntity()->isBreakable(blockToMine);
}
