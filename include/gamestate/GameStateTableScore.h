#ifndef GAMESTATETABLESCORE_H
#define GAMESTATETABLESCORE_H

#include "gamestate/GameState.h"
#include "gui/TextField.h"
#include "gui/Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "model/User.h"


class GameStateTableScore : public GameState
{
    public:
        GameStateTableScore(Game* game);
        virtual ~GameStateTableScore();
        GameStateTableScore(const GameStateTableScore& other);
        GameStateTableScore& operator=(const GameStateTableScore& other);

        void initListScores(sf::RenderWindow& window, sf::Texture& textureTXT);
        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        sf::Font font;
        sf::Sprite background,title;
        TextField* text;
        std::vector <TextField*> listName;
        std::vector <TextField*> listScores;
        std::vector<User*> users;
        Button btnBack;
        const int screen_h = 700,screen_w = 1200;
        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);
        void initBackGround(sf::Texture& title,sf::Texture& tex, sf::RenderWindow& window);
};

#endif // GAMESTATETABLESCORE_H
