#include "gamestate/GameStateGame.h"


using namespace sf;
using namespace std;

const int TIME_TIMER = 120;

GameStateGame::GameStateGame(Game* game)
{
    this->game = game;
    View view( FloatRect(0, 0, screen_w, screen_h) );

    this->tileMap = new TileMap(tileMap_width,tileMap_height,tile_size,screen_w,screen_h);

    loadTextures();
    loadAnimations();
    loadTileMap();

    timer = new Timer(TIME_TIMER);
    timer->setTimeout([&](){
                GestionUser::getInstance()->addScoreCurrentUser(score);
                cout<<GestionUser::getInstance()->str();
                GestionUser::getInstance()->writeFromFile("User.txt");
                this->game->pushState(new GameStateTableScore(this->game));
                 },TIME_TIMER * 1000);
    timer->run();
}

GameStateGame::~GameStateGame()
{
    delete tileMap;
    delete miner;
    delete timer;
}

GameStateGame::GameStateGame(const GameStateGame& other)
{
    //copy ctor
}

void GameStateGame::draw(const float time)
{
    int toDisplay = (screen_h+tile_size*2)/2;
    int xView,yView;
    xView = miner->getX() - screen_w/2;
    yView = miner->getY() - screen_h/2;
    if(miner->getX() + miner->getW()/2 - screen_w/2 < 0)
        xView = 0;
    else if(miner->getX() + miner->getW()/2 + screen_w/2 > tileMap_width * tile_size)
        xView = tileMap_width * tile_size - screen_w;

    view.reset(sf::FloatRect(xView,yView,screen_w,screen_h));
    this->game->window.setView(view);

    background.setPosition(sf::Vector2f(view.getCenter().x,-32));
    background_caverne.setPosition(view.getCenter());
    this->game->window.draw(background_caverne);
    this->game->window.draw(background);

    tileMap->draw(this->game->window,time,sf::Vector2f(miner->getX(),miner->getY()));
    miner->draw(this->game->window);

    for(EnemyComponent* ec:enemies){
       if(ec->getY() >= miner->getY() - toDisplay && ec->getY() <= miner->getY() + toDisplay)
            ec->draw(this->game->window);
    }

    timer->draw(this->game->window);
    oreBar.draw(this->game->window);
}
void GameStateGame::setScore(int newScore){
    this->score = newScore;
}
void GameStateGame::update(const float time)
{
    miner->update(time);
    if(!miner->getEntity()->getLife()){
        View viewChange(sf::FloatRect(0,0,screen_w,screen_h));
        this->game->window.setView(viewChange);
        GestionUser::getInstance()->addScoreCurrentUser(score);
        cout<<GestionUser::getInstance()->str();
        GestionUser::getInstance()->writeFromFile("User.txt");
        this->game->pushState(new GameStateTableScore(this->game));
    }
    int toDisplay = (screen_h+tile_size*2)/2;

    for(auto it = enemies.begin();it!=enemies.end() ;){
        EnemyComponent* ec = *it;
        if(ec->getY() >= miner->getY() - toDisplay && ec->getY() <= miner->getY() + toDisplay){
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

            if(miner->getRect().intersects(ec->getRect())){
                if(!miner->getHitByMob()){
                    miner->setHitByMob(true);
                    miner->hittedByMob();
                }
            }
        }
    }

    timer->update(miner->getY()/tile_size);
    Player* player = dynamic_cast<Player*>(miner->getEntity());
    oreBar.update(player->getNbOresCraftCurrentPickaxe(),player->getNbOresCurrentPickaxe(),player->getType());
}

void GameStateGame::handleInput()
{
    Event event;
    while (this->game->window.pollEvent(event))
    {
        int scoreLvl =(int) miner->getY()/tile_size;
        setScore(scoreLvl);
        if (event.type == Event::Closed)
            this->game->window.close();

    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) miner->setKey("Q",true);
    if (Keyboard::isKeyPressed(Keyboard::Right)) miner->setKey("D",true);
    if (Keyboard::isKeyPressed(Keyboard::Up)) miner->setKey("Z",true);
    if (Keyboard::isKeyPressed(Keyboard::Down)) miner->setKey("S",true);

}


void GameStateGame::loadTextures(){
	miner_t.loadFromFile("miner.png");
	bg.loadFromFile("background.png");
	bgCaverne.loadFromFile("background_caverne.png");
	blocks_sheet.loadFromFile("blocks_sheet.png");
    enemy_t.loadFromFile("enemyWalk.png");

    bg.setRepeated(true);

    background.setTexture(bg);
    background_caverne.setTexture(bgCaverne);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);
    background_caverne.setOrigin(bgCaverne.getSize().x/2,bgCaverne.getSize().y/2);
    background.setScale(Vector2f(1.03,1.0));
    background.setTextureRect(sf::IntRect(0,0,screen_w,12*tile_size - 7));

}

void GameStateGame::loadTileMap(){
    BlockDirt bDirt(        {0.90,0.596,0.34,0.106,0.00,0.00});
    BlockStone bStone(      {0.10,0.30,0.45,0.590,0.628,0.48});
    BlockIron bIron(        {0.00,0.10,0.10,0.10,0.055,0.07});
    BlockGold bGold(        {0.00,0.00,0.05,0.07,0.05,0.06});
    BlockDiamond bDiamond(  {0.00,0.00,0.00,0.02,0.03,0.04});
    BlockEmerald bEmerald(  {0.00,0.00,0.00,0.00,0.015,0.03});
    BlockObsidian bObsidian({0.00,0.00,0.05,0.10,0.20,0.30});
    LavaBlock bLava(        {0.00,0.002,0.006,0.008,0.014,0.012});
    spawnEnemy =            {0.00,0.002,0.004,0.006,0.008,0.008};

    blocks = {bDirt,bStone,bIron,bGold,bDiamond,bEmerald,bObsidian,bLava};

    TileMap* temp;
    int pallier = 0,nbVoid = 0;
    float randF = 0.;
    for(int y = 0 ; y < tileMap_height ; y++){
        for(int x = 0 ; x < tileMap_width ; x++){
                Tile t;
                int pos = x + y * tileMap_width;
                if(y < 1){
                    t.load(bDirt,animBlock[0],x*32, (y*32) + h_miner,tile_size,tile_size);
                    tileMap->add(t,pos);
                }
                else{
                    pallier = y/20 > 5 ? 5 : y/20;
                    randF = round(rand()%1000) /1000.;
                    float fSpawn = 0;
                    for(int i = blocks.size() ; i >= 0  ; i--){
                        if(i == blocks.size())
                            fSpawn += spawnEnemy[pallier];
                        else
                            fSpawn += blocks[i].getSpawn()[pallier];

                        if(randF < fSpawn){
                            int rand2 = rand()%7 + 3;
                            if(i == blocks.size()){
                                y += (x + rand2) / tileMap_width;
                                x = (x + rand2) % tileMap_width;
                                nbVoid += rand2;
                                enemies.push_back(new EnemyComponent(animEnemy,animMinerFire,temp,x*tile_size,(y*tile_size)+h_miner,spawnEnemy));
                            }
                            else if(i == blocks.size()-1){
                                for(int j = 0 ; j < rand2 ; j++){
                                    t.load(blocks[i],animBlock[posLava],x*tile_size,(y*tile_size)+h_miner,tile_size,tile_size/2);
                                    tileMap->add(t,x+y*tileMap_width);
                                    if(++x == tileMap_width){ x = 0;  y++;}
                                }
                                x--;
                            }else{
                                t.load(blocks[i],animBlock[i+1],x*tile_size,(y*tile_size)+h_miner,tile_size,tile_size);
                                tileMap->add(t,pos);
                            }
                            break;
                        }
                    }
                }

        }
    }
    tileMap->setNbBlockMined(nbVoid);
    miner = new PlayerComponent(animMiner,animMinerFire,tileMap,0,0);
    for(EnemyComponent* ec: enemies){
        ec->setTileMap(tileMap);
    }
}

void GameStateGame::loadAnimations(){
    animEnemy.create("move",enemy_t,1,0,12,24,13,0.005,16);

    string animations[4] = {"stay","mining1","mining2","mining3"};
    for(int i = 0 ; i < nbBlock-2 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            animBlock[i].create(animations[j],blocks_sheet,j * tile_size, tile_size * i,tile_size,tile_size,1,0.0,tile_size);
        }
    }
    animBlock[posLava].create("stay",blocks_sheet,0,1+tile_size*posLava + tile_size/2 ,tile_size,tile_size/2,4,0.001,tile_size);


    for(int i = 0 ; i < 6 ; i++){
        animMiner.create("walk"+to_string(i),miner_t,0,(h_miner+1)*i,w_miner-2,h_miner,3,0.005,w_miner);
        animMiner.create("mining"+to_string(i),miner_t,w_miner,(h_miner+1)*i,w_miner-2,h_miner,4,0.01,w_miner);
        animMiner.create("stay"+to_string(i),miner_t,0,(h_miner+1)*i,w_miner-2,h_miner,1,0.005,w_miner);
        animMiner.create("jump"+to_string(i),miner_t,64,(h_miner+1)*i,w_miner-2,h_miner,1,0.005,w_miner);
    }

    animMinerFire.create("fire",miner_t,0,150,14,19,6,0.005,14);

}

void GameStateGame::loadBlocks(){

}
