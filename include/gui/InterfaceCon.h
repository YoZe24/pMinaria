#ifndef INTERFACECON_H
#define INTERFACECON_H
#include "Button.h"
#include "TextField.h"
#include "GestionUser.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;



class InterfaceCon
{
    public:
        InterfaceCon(Texture& title,Texture& textureBG,Texture& textureBTN,Texture& textureTXT,Font& font,RenderWindow& window);
        friend void voo();
        virtual ~InterfaceCon();
        InterfaceCon(const InterfaceCon& other);
        InterfaceCon& operator=(const InterfaceCon& other);
        void InputTextRecup(RenderWindow& window, Event event);
        void Confirm(RenderWindow& window);
        void draw(RenderWindow& window);

    protected:

    private:
        Sprite background,title;
        Button btnConfirm, btnBack;

        TextField* textLogin;
        TextField* inputLogin;

        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
        void createButton(Font& font,Texture& tex,RenderWindow& window);

        int COUNT_CHAR = 0;
        sf::String loginInput;

};

#endif // INTERFACECON_H
