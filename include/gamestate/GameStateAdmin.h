#ifndef GAMESTATEADMIN_H
#define GAMESTATEADMIN_H

#include "gamestate/GameState.h"
#include "gui/TextField.h"
#include "gui/Button.h"
#include "gui/SliderSFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "model/User.h"

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

        void initListName(sf::RenderWindow& window, sf::Texture& textureTXT);
        void initListScores(sf::RenderWindow& window, sf::Texture& textureTXT);
        void Delete(sf::RenderWindow& window);
        void getTextFieldSelected(sf::RenderWindow& window);
        int getPositionSelected();
        void setPositionSelected(int newPosition);

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        sf::Font font;

        sf::Sprite background,title;
        TextField* text;
        std::vector <TextField*> listName;
        std::vector <TextField*> listScores;
        std::vector<User*> users;
        Button btnDelete;
        Button btnBack;
        int positionSelected = -1;
        TextField textfieldSelected;

        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);
        void initBackGround(sf::Texture& title,sf::Texture& tex, sf::RenderWindow& window);
};

#endif // GAMESTATEADMIN_H
