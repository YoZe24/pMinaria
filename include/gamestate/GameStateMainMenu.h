#ifndef GAMESTATEMAINMENU_H
#define GAMESTATEMAINMENU_H


#include "gamestate/GameState.h"
#include "gamestate/GameStateGame.h"
#include "gamestate/GameStateCon.h"
#include "gamestate/GameStateAdmin.h"
#include "gamestate/GameStateConAdmin.h"
#include "gamestate/GameStateTableScore.h"
#include "gamestate/GameStateOptionMenu.h"
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
#include <map>
#include <cmath>
#include "view/EnemyComponent.h"
#include "view/HealthBar.h"
#include "view/Timer.h"
#include "OresBar.h"
#include "gui/Button.h"
#include "gui/SliderSFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class GameStateMainMenu : public GameState
{
    public:
        GameStateMainMenu(Game* game);
        virtual ~GameStateMainMenu();
        GameStateMainMenu(const GameStateMainMenu& other);
        GameStateMainMenu& operator=(const GameStateMainMenu& other);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

        void loadTextures();
    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        Font font;

        Sprite background,title;
        Button playButton,connectionButton,optionButton,quitButton,adminButton,scoreBoardButton;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
};

#endif // GAMESTATEMAINMENU_H
