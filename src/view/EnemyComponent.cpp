#include "view/EnemyComponent.h"

using namespace std;

EnemyComponent::EnemyComponent(AnimationManager& a,AnimationManager& af,TileMap* tm,int x, int y,vector<float> s):EntityComponent(a,af,tm,x,y)
{
    Enemy* e = new Enemy(60,true,s);
    option("Enemy",e,0.05,"move");
    getAnim().set("move");
    setFire(false);
    setTimerFire(0);
}

EnemyComponent::~EnemyComponent()
{
    //dtor
}

EnemyComponent::EnemyComponent(const EnemyComponent& other):EntityComponent(other)
{
    //option("Enemy",other.entity,10,"move");
    cout << "test";
}

vector<float> EnemyComponent::getSpawn(){
    Enemy* enemy = dynamic_cast<Enemy*>(getEntity());
    return enemy->getSpawn();
}

void EnemyComponent::swapDir(){
    if(getDir()){
        setDX( getDX() < 0 ? getDX() : getDX() * -1);
    }else{
        setDX( getDX() > 0 ? getDX() : getDX() * -1);
    }
    getAnim().flip(getDir());

}

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

void EnemyComponent::Collision(int num){
    TileMap& tileMap = *getTileMap();

//    int nbBM = tileMap.getNbBlockMined();

    int posX = getX()/tileMap.getTileSize();
    int posY = getY()/tileMap.getTileSize();
//    int width = tileMap.getWidth();
    int pos = posX + posY * tileMap.getWidth();

//    std::map<int,Tile>* tiles = tileMap.getTiles();
//
//    int start = pos - (width * 2) - nbBM  < 0 ? 0 : pos - (width * 2) - nbBM;
//    int limit = pos + width * 2 > tiles->size() ? tiles->size() : pos+width*2;

//    map<int,Tile>::iterator it = tiles->begin(), itFinish = tiles->begin();
//    advance(it,start);
//    advance(itFinish,limit);
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
