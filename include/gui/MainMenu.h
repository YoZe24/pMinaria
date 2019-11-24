#ifndef MAINMENU_H
#define MAINMENU_H
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class MainMenu
{
    public:

        MainMenu();
        MainMenu(Texture& title,Texture& textureBG,Texture& textureBTN,Font& font,RenderWindow& window);
        virtual ~MainMenu();

        void draw(RenderWindow& window);
        void update(RenderWindow& window);
        void handleInput(RenderWindow& window);


    protected:

    private:

        Sprite background,title;
        Button playButton,connectionButton,optionButton,quitButton,adminButton,scoreBoardButton;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);


};

#endif // MAINMENU_H
