#include "view/PlayerComponent.h"
#include <cmath>

using namespace std;

const float GRAVITY = 0.0005;

PlayerComponent::PlayerComponent(AnimationManager &a,AnimationManager& animFire, TileMap* tileMap,int x,int y):EntityComponent(a,animFire,tileMap,x,y){
    Player* p = new Player(100,true);
    updateStrAnimation("0");
    option("Player",p,0,stayStr);

    STATE=stay;
    miningDown = false;
    hit=false;
    setFire(false);
    setTimerFire(0);

}

PlayerComponent::~PlayerComponent()
{

}

PlayerComponent& PlayerComponent::operator=(const PlayerComponent& other){
    if(this != &other){
        EntityComponent::operator=(other);
        Player* p = new Player(100,true);
        updateStrAnimation("0");
        option("Player",p,0,stayStr);

        STATE=stay;
        miningDown = false;
        hit=false;
        setFire(false);
        setTimerFire(0);
    }
    return *this;
}

void PlayerComponent::updateStrAnimation(string i){
    walkStr = "walk"+i;
    stayStr = "stay"+i;
    jumpStr = "jump"+i;
    miningStr = "mining"+i;
}

void PlayerComponent::setKey(string strKey,bool state){
    key[strKey]=state;
}

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

void PlayerComponent::draw(sf::RenderWindow& window){
    EntityComponent::draw(window);
}

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

void PlayerComponent::update(float time){
    cout << "Miner : " << getTileMap() << endl;
    sf::Clock c;
    if(!getEntity()->getLife()){
        reset(100);
    }
    Player* player = dynamic_cast<Player*>(getEntity());
    power = player->updatePickaxe();
    updateStrAnimation(to_string(player->getType()));

    Fire(time);
    keyboard();

    Animation(time);

    updateDY(GRAVITY * time);

    updateX(getDX() * time);
    Collision(0);

    updateY(getDY() * time);
    Collision(1);
}

void PlayerComponent::Collision(int num){
    TileMap& tileMap = *getTileMap();
    int width = tileMap.getWidth();
    int pos = tileMap.getPos(getX(),getY());
    int xD,yD;

    EnumBlock blockCollide;
    map<int,Tile>::iterator itFinish = tileMap.getItFinish(pos);
    for(auto i = tileMap.getItStart(pos) ; i != itFinish ; i++){
            blockCollide = i->second.getBlock().getType();
            sf::FloatRect fr = i->second.getRect();
            if(getRect().intersects(fr)){

                if(i->second.getBlock().getType() == EnumBlock::LAVA){
                    setFire(true);
                    getAnimFire().play();
                }else{
                    if (getDY()>0 && num==1){
                        setY(fr.top -  getH());
                        setDY(0);
                        STATE=stay;
                        xD = getX() + getW() / 2;       yD = getY() + getH();

                        if(isMinable(xD,yD,blockCollide) && miningDown){
                            if(tryToDeleteAt(xD,yD)) break;
                        }
                    }
                    if (getDY()<0 && num==1){
                        setY(fr.top + fr.height);
                        setDY(0);
                        xD = getX() + getW() / 2;       yD = getY() - getH();

                        if(isMinable(xD,yD,blockCollide))
                            if(tryToDeleteAt(xD,yD)) break;

                    }
                    if (getDX()>0 && num==0)	{
                        setX(fr.left -  getW());
                        xD = getX() + getW() ;          yD = getY() - 4;
                        if(isMinable(xD,yD,blockCollide))
                            if(tryToDeleteAt(xD,yD)) break;

                    }

                    if (getDX()<0 && num==0){
                        setX(fr.left + fr.width);
                        xD = getX() - getW() ;          yD = getY() - 4;
                        if(isMinable(xD,yD,blockCollide))
                            if(tryToDeleteAt(xD,yD)) break;

                    }
                }
            }
    }
    CollisionBord();
}


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

bool PlayerComponent::isMinable(int x,int y,EnumBlock blockCollide){
    EnumBlock blockToMine = getTileMap()->getEnumBlockAt(x,y);
    return getEntity()->isBreakable(blockToMine);
}
