#ifndef GAMESTATEGAME_H
#define GAMESTATEGAME_H

#include "gamestate/GameState.h"
#include "gamestate/GameStateMainMenu.h"
#include "gamestate/GameStateTableScore.h"
#include <SFML/Graphics.hpp>
#include "view/AnimationManager.h"
#include <vector>
#include <list>
#include <ctime>
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
#include "model/BlockObsidian.h"
#include "model/Pickaxe.h"
#include "model/GestionUser.h"
#include <map>
#include <cmath>
#include "view/EnemyComponent.h"
#include "view/HealthBar.h"
#include "view/Timer.h"
#include "OresBar.h"

class GameStateGame : public GameState
{
    public:
        GameStateGame(Game* game);
        virtual ~GameStateGame();
        GameStateGame(const GameStateGame& other);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

        void loadTextures();
        void loadTileMap();
        void loadAnimations();
        void loadBlocks();
        void setScore(int newScore);
    protected:

    private:
        TileMap* tileMap;
        sf::View view;
        sf::Texture miner_t,bg,bgCaverne,blocks_sheet,enemy_t;
        sf::Sprite background,background_caverne;
        Timer* timer;
        OresBar oreBar;
        int score;
        vector<Block> blocks;
        vector<float> spawnEnemy;
        vector<EnemyComponent*> enemies;
        PlayerComponent* miner;
        const int tileMap_height = 400,tileMap_width = 50,tile_size = 32,h_miner = 24,w_miner = 16;
        const int screen_h = 700,screen_w = 1200;
        const static int nbBlock = 10,posLava = 9;
        AnimationManager animMinerFire,animMiner,animEnemy,animBlock[nbBlock];
};

#endif // GAMESTATEGAME_H
