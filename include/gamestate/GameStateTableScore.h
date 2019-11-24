#ifndef GAMESTATETABLESCORE_H
#define GAMESTATETABLESCORE_H
#include "gamestate/GameState.h"
#include "gamestate/GameStateGame.h"
#include "gamestate/GameStateMainMenu.h"
#include "gamestate/GameStateAdmin.h"
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
#include "model/User.h"
#include "model/GestionUser.h"
#include <map>
#include <cmath>
#include "view/EnemyComponent.h"
#include "view/HealthBar.h"
#include "view/Timer.h"
#include "OresBar.h"
#include "gui/Button.h"
#include "gui/TextField.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class GameStateTableScore : public GameState
{
    public:
        GameStateTableScore(Game* game);
        virtual ~GameStateTableScore();
        GameStateTableScore(const GameStateTableScore& other);
        GameStateTableScore& operator=(const GameStateTableScore& other);

        void initListScores(RenderWindow& window, Texture& textureTXT);
        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        Font font;
        Sprite background,title;
        TextField* text;
        vector <TextField*> listName;
        vector <TextField*> listScores;
        vector<User*> users;
        Button btnBack;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex, RenderWindow& window);
};

#endif // GAMESTATETABLESCORE_H
