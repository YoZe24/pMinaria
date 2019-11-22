#ifndef OPTIONMENU_H
#define OPTIONMENU_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "SliderSFML.h"
#include <iostream>

using namespace std;
using namespace sf;

class OptionMenu
{
    public:

        OptionMenu();
        OptionMenu(Texture& title,Texture& textureBG,Texture& textureBTN,Font& font,RenderWindow& window);
        virtual ~OptionMenu();
        OptionMenu(const OptionMenu& other);
        OptionMenu& operator=(const OptionMenu& other);

        void draw(RenderWindow& window);
        void update(RenderWindow& window);
        void handleInput(RenderWindow& window);

    protected:

    private:

        Sprite background;
        Button easyModeButton,mediumModeButton,hardModeButton,backMainMenuButton;
        SliderSFML sliderTime, sliderDurability;
        Sprite title;


        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
        void initSliders(RenderWindow& window);

        void updateSliders(int time,int durability);

        /** Recois en param l'instance unique de jeu et modifie les attributs de gameplay (le time et la durability des blocs)*/
        void saveOptions();
};

#endif
