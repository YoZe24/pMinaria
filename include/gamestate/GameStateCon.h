#ifndef GAMESTATECON_H
#define GAMESTATECON_H
#include "gamestate/GameState.h"
#include "gamestate/GameStateGame.h"
#include "gamestate/GameStateMainMenu.h"
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


class GameStateCon : public GameState
{
    public:
        GameStateCon(Game* game);
        virtual ~GameStateCon();
        GameStateCon(const GameStateCon& other);
        GameStateCon& operator=(const GameStateCon& other);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

        void InputTextRecup(RenderWindow& window, sf::Event event);
        void Confirm(RenderWindow& window);

        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        Font font;

        Sprite background,title;
        Button btnConfirm, btnBack;

        TextField* textLogin;
        TextField* inputLogin;

        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
        void createButton(Font& font,Texture& tex,RenderWindow& window);

        int COUNT_CHAR = 0;
        sf::String loginInput;
};

#endif // GAMESTATECON_H