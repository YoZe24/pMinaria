#ifndef GAMESTATEADMIN_H
#define GAMESTATEADMIN_H
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


class GameStateAdmin : public GameState
{
    public:
        GameStateAdmin(Game* game);
        virtual ~GameStateAdmin();
        GameStateAdmin(const GameStateAdmin& other);
        GameStateAdmin& operator=(const GameStateAdmin& other);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void loadTextures();

        void initListName(RenderWindow& window, Texture& textureTXT);
        void initListScores(RenderWindow& window, Texture& textureTXT);
        void Delete(RenderWindow& window);
        void getTextFieldSelected(RenderWindow& window);
        int getPositionSelected();
        void setPositionSelected(int newPosition);

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        Font font;

        Sprite background,title;
        TextField* text;
        vector <TextField*> listName;
        vector <TextField*> listScores;
        vector<User*> users;
        Button btnDelete;
        Button btnBack;
        int positionSelected = -1;
        TextField textfieldSelected;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex, RenderWindow& window);
};

#endif // GAMESTATEADMIN_H
