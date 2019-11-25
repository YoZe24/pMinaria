#ifndef GAMESTATEMAINMENU_H
#define GAMESTATEMAINMENU_H


#include "gamestate/GameState.h"
#include "gui/TextField.h"
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
        sf::Font font;

        sf::Sprite background,title;
        Button playButton,connectionButton,optionButton,quitButton,adminButton,scoreBoardButton;

        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);
        void initBackGround(sf::Texture& title,sf::Texture& tex,sf::RenderWindow& window);
};

#endif // GAMESTATEMAINMENU_H
