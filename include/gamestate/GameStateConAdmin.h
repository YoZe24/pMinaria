#ifndef GAMESTATECONADMIN_H
#define GAMESTATECONADMIN_H

#include "gamestate/GameState.h"
#include "gui/TextField.h"
#include "gui/Button.h"
#include "gui/SliderSFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameStateConAdmin : public GameState
{
    public:
        GameStateConAdmin(Game* game);
        virtual ~GameStateConAdmin();
        GameStateConAdmin(const GameStateConAdmin& other);
        GameStateConAdmin& operator=(const GameStateConAdmin& other);

        void InputTextRecup(sf::RenderWindow& window, sf::Event event);
        void Confirm(sf::RenderWindow& window);
        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void loadTextures();

    protected:

    private:
        sf::Texture textureBG, textureBTN, textureTXT, textureTitle;
        sf::Font font;

        sf::Sprite background,title;
        Button btnConfirm, btnBack;

        TextField* textMdp;
        TextField* inputMdp;

        void initBackGround(sf::Texture& title,sf::Texture& tex,sf::RenderWindow& window);
        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);

        int COUNT_CHAR = 0;
        sf::String mdpInput;
};

#endif // GAMESTATECONADMIN_H
