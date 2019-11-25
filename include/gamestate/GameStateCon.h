#ifndef GAMESTATECON_H
#define GAMESTATECON_H

#include "gamestate/GameState.h"
#include "gui/TextField.h"
#include "gui/Button.h"
#include "gui/SliderSFML.h"
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

        void InputTextRecup(sf::RenderWindow& window, sf::Event event);
        void Confirm(sf::RenderWindow& window);

        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        sf::Font font;

        sf::Sprite background,title;
        Button btnConfirm, btnBack;

        TextField* textLogin;
        TextField* inputLogin;

        void initBackGround(sf::Texture& title,sf::Texture& tex,sf::RenderWindow& window);
        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);

        int COUNT_CHAR = 0;
        sf::String loginInput;
};

#endif // GAMESTATECON_H
