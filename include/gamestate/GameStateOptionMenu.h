#ifndef GAMESTATEOPTIONMENU_H
#define GAMESTATEOPTIONMENU_H

#include "gamestate/GameState.h"
#include "gui/TextField.h"
#include "gui/Button.h"
#include "gui/SliderSFML.h"
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
        sf::Font font;
        sf::Sprite background;
        Button easyModeButton,mediumModeButton,hardModeButton,backMainMenuButton;
        SliderSFML sliderTime, sliderDurability;
        sf::Sprite title;


        void createButton(sf::Font& font,sf::Texture& tex,sf::RenderWindow& window);
        void initBackGround(sf::Texture& title,sf::Texture& tex,sf::RenderWindow& window);
        void initSliders(sf::RenderWindow& window);

        void updateSliders(int time,float durability);

        /** Recois en param l'instance unique de jeu et modifie les attributs de gameplay (le time et la durability des blocs)*/
        void saveOptions(Game* game);
};

#endif // GAMESTATEOPTIONMENU_H
