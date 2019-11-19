#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <ctime>
#include "view/AnimationManager.h"
#include "model/Entity.h"
#include "model/Player.h"
#include "view/EntityComponent.h"
#include "view/PlayerComponent.h"
#include "view/TileMap.h"
#include "model/BlockDirt.h"
#include "model/BlockStone.h"
#include "model/BlockIron.h"
#include "model/BlockGold.h"
#include "model/BlockDiamond.h"
#include "model/BlockEmerald.h"
#include "model/LavaBlock.h"
#include "model/Pickaxe.h"
#include <map>
#include <cmath>
#include "view/EnemyComponent.h"


using namespace sf;
using namespace std;

const int tileMap_height = 200,tileMap_width = 50,tile_size = 32,h_miner = 24,w_miner = 16;
const int screen_h = 600,screen_w = 1200;
int level[tileMap_width * tileMap_height];
TileMap tileMap(tileMap_width,tileMap_height,tile_size,screen_w,screen_h);


int main()
{
    srand(time(NULL));
//    RenderWindow window(VideoMode(1920, 1080), "Minaria",sf::Style::Fullscreen);
    RenderWindow window(VideoMode(screen_w,screen_h), "Minaria");

	View view( FloatRect(0, 0, screen_w, screen_h) );

	Texture miner_t,bg,bgCaverne,blocks_sheet,enemy_t;
	miner_t.loadFromFile("miner2.png");
	bg.loadFromFile("background.png");
	bgCaverne.loadFromFile("background_caverne.png");
	blocks_sheet.loadFromFile("blocks_sheet.png");
    enemy_t.loadFromFile("enemyWalk.png");

    AnimationManager animEnemy;
    animEnemy.create("move",enemy_t,1,0,12,24,13,0.005,16);

    BlockDirt bDirt(        {0.90,0.596,0.34,0.106,0.00,0.00});
    BlockStone bStone(      {0.10,0.30,0.50,0.690,0.828,0.78});
    BlockIron bIron(        {0.00,0.10,0.10,0.10,0.055,0.07});
    BlockGold bGold(        {0.00,0.00,0.05,0.07,0.05,0.06});
    BlockDiamond bDiamond(  {0.00,0.00,0.00,0.02,0.03,0.04});
    BlockEmerald bEmerald(  {0.00,0.00,0.00,0.00,0.015,0.03});
    LavaBlock bLava(        {0.00,0.002,0.006,0.008,0.014,0.012});
    vector<float> spawnEnemy = {0.00,0.002,0.004,0.006,0.008,0.008};

    vector<Block> blocks = {bDirt,bStone,bIron,bGold,bDiamond,bEmerald,bLava};

//    BlockDirt bDirt(        {0.90,0.598,0.304,0.106,0.00});
//    BlockStone bStone(      {0.10,0.30,0.491,0.684,0.828});
//    BlockIron bIron(        {0.00,0.10,0.15,0.10,0.07});
//    BlockGold bGold(        {0.00,0.00,0.04,0.08,0.06});
//    BlockDiamond bDiamond(  {0.00,0.00,0.01,0.02,0.03});
//    LavaBlock bLava(        {0.00,0.002,0.005,0.008,0.012});
//    vector<float> spawnEnemy = {0.00,0.002,0.004,0.006,0.010};
//
//    vector<Block> blocks = {bDirt,bStone,bIron,bGold,bDiamond,bLava};

    int nbBlock = 10,posLava = 9;
    AnimationManager animBlock[nbBlock];
    string animations[4] = {"stay","mining1","mining2","mining3"};
    for(int i = 0 ; i < nbBlock-3 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            animBlock[i].create(animations[j],blocks_sheet,j * tile_size, tile_size * i,tile_size,tile_size,1,0.0,tile_size);
        }
    }

    animBlock[posLava].create("stay",blocks_sheet,0,1+tile_size*posLava ,tile_size,tile_size,4,0.001,tile_size);


	AnimationManager animMiner;
    for(int i = 0 ; i < 6 ; i++){
        animMiner.create("walk"+to_string(i),miner_t,0,(h_miner+1)*i,w_miner-2,h_miner,3,0.005,w_miner);
        animMiner.create("mining"+to_string(i),miner_t,w_miner,(h_miner+1)*i,w_miner-2,h_miner,4,0.01,w_miner);
        animMiner.create("stay"+to_string(i),miner_t,0,(h_miner+1)*i,w_miner-2,h_miner,1,0.005,w_miner);
        animMiner.create("jump"+to_string(i),miner_t,64,(h_miner+1)*i,w_miner-2,h_miner,1,0.005,w_miner);
    }

	AnimationManager animMinerFire;
    animMinerFire.create("fire",miner_t,0,150,14,19,6,0.005,14);

    bg.setRepeated(true);

    Sprite background(bg),background_caverne(bgCaverne);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);
    background_caverne.setOrigin(bgCaverne.getSize().x/2,bgCaverne.getSize().y/2);
    background.setTextureRect(sf::IntRect(0,0,screen_w,12*tile_size - 7));

    vector<EnemyComponent*> enemies;
    TileMap* temp;

    int pallier = 0,nbVoid = 0;
    float rf = 0.;
    for(int y = 0 ; y < tileMap_height ; y++){
        for(int x = 0 ; x < tileMap_width ; x++){
                Tile t;
                if(y < 1){
                    t.load(bDirt,animBlock[0],x*32, (y*32) + h_miner,tile_size,tile_size);
                    tileMap.add(t);
                }
                else{
                    pallier = y/16 > 4 ? 4 : y/16;
                    rf = round(rand()%1000) /1000.;
                    float fSpawn = 0;
                    for(int i = blocks.size() ; i >= 0  ; i--){
                        vector<float> spawn;
                        if(i == blocks.size())
                            spawn = spawnEnemy;
                        else
                            spawn = blocks[i].getSpawn();

                        fSpawn += spawn[pallier];

                        if(rf < fSpawn){
                            if(i == blocks.size()){
                                int rand2 = rand()%7 + 3;
                                for(int j = 0 ; j < rand2 ; j++){
                                    if(++x == tileMap_width){ x = 0;  y++;}
                                    nbVoid++;
                                }
                                enemies.push_back(new EnemyComponent(animEnemy,animMinerFire,temp,x*tile_size,(y*tile_size)+h_miner,spawnEnemy));
                                x--;
                            }
                            else if(i == blocks.size()-1){
                                int rand2 = rand()%7 + 3;
                                for(int j = 0 ; j < rand2 ; j++){
                                    t.load(blocks[i],animBlock[posLava],x*tile_size,(y*tile_size)+h_miner,tile_size,tile_size);
                                    if(++x == tileMap_width){ x = 0;  y++;}
                                    tileMap.add(t);
                                }
                                x--;
                            }else{
                                t.load(blocks[i],animBlock[i+1],x*tile_size,(y*tile_size)+h_miner,tile_size,tile_size);
                                tileMap.add(t);
                            }
                            break;
                        }
                    }
                }

        }
    }
    tileMap.setNbBlockMined(nbVoid);
    PlayerComponent miner(animMiner,animMinerFire,&tileMap,0,0);
    for(EnemyComponent* ec: enemies){
        ec->setTileMap(&tileMap);
    }

    Clock clock;


    while(window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time/500;
		if (time > 40) time = 40;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}


		if (Keyboard::isKeyPressed(Keyboard::Left)) miner.setKey("Q",true);
		if (Keyboard::isKeyPressed(Keyboard::Right)) miner.setKey("D",true);
		if (Keyboard::isKeyPressed(Keyboard::Up)) miner.setKey("Z",true);
		if (Keyboard::isKeyPressed(Keyboard::Down)) miner.setKey("S",true);

        window.clear();
        miner.update(time);
//        cout << miner.getX() << ", "<<miner.getY()<<endl;
        int toDisplay = (screen_h+tile_size*2)/2;

        for(auto it = enemies.begin();it!=enemies.end() ;){
            EnemyComponent* ec = *it;
            if(ec->getY() >= miner.getY() - toDisplay && ec->getY() <= miner.getY() + toDisplay){
                ec->update(time);
                if(!ec->getEntity()->getLife()){
                    it = enemies.erase(it);
//                    delete ec;
                    continue;
                }
            }
            it++;
        }

        for(auto it = enemies.begin() ; it != enemies.end() ; it++){
            if((*it)->getName() == "Enemy"){
                EntityComponent* ec = *it;
                if(!ec->getEntity()->getLife())continue;

                if(miner.getRect().intersects(ec->getRect())){
                    if(!miner.getHitByMob()){
                        miner.getEntity()->updateHealth(-10);
                        miner.setHitByMob(true);
                        miner.setDY(-0.17);
                        if(miner.getDir())
                            miner.updateX(10);
                        else
                            miner.updateX(-10);
                    }
                }
            }
        }

        int xView,yView;
        xView = miner.getX() - screen_w/2;
        yView = miner.getY() - screen_h/2;
        if(miner.getX() + miner.getW()/2 - screen_w/2 < 0)
            xView = 0;
        else if(miner.getX() + miner.getW()/2 + screen_w/2 > tileMap_width * tile_size)
            xView = tileMap_width * tile_size - screen_w;

        view.reset(sf::FloatRect(xView,yView,screen_w,screen_h));
        window.setView(view);
        background.setPosition(sf::Vector2f(view.getCenter().x,-32));
        background_caverne.setPosition(view.getCenter());

        window.draw(background_caverne);
        window.draw(background);
        tileMap.draw(window,time,sf::Vector2f(miner.getX(),miner.getY()));
        miner.draw(window);

        for(EnemyComponent* ec:enemies){
           if(ec->getY() >= miner.getY() - toDisplay && ec->getY() <= miner.getY() + toDisplay)
                ec->draw(window);
        }

        window.display();
    }

    return 0;
}
