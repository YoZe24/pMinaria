#ifndef GAMESTATEOPTIONMENU_H
#define GAMESTATEOPTIONMENU_H

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
#include "gui/SliderSFML.h"
#include "gui/TextField.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class GameStateOptionMenu : public GameState
{
    public:
        GameStateOptionMenu(Game* game);
        virtual ~GameStateOptionMenu();
        GameStateOptionMenu(const GameStateOptionMenu& other);
        GameStateOptionMenu& operator=(const GameStateOptionMenu& other);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        Font font;
        Sprite background;
        Button easyModeButton,mediumModeButton,hardModeButton,backMainMenuButton;
        SliderSFML sliderTime, sliderDurability;
        Sprite title;


        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
        void initSliders(RenderWindow& window);

        void updateSliders(int time,int durability);

        /** Recois en param l'instance unique de jeu et modifie les attributs de gameplay (le time et la durability des blocs)*/
        void saveOptions(Game* game);
};

#endif // GAMESTATEOPTIONMENU_H
