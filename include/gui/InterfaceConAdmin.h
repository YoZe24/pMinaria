#ifndef INTERFACECONADMIN_H
#define INTERFACECONADMIN_H
#include "Button.h"
#include "TextField.h"
#include "GestionUser.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class InterfaceConAdmin
{
    public:
        InterfaceConAdmin(Texture& title,Texture& textureBG,Texture& textureBTN,Texture& textureTXT,Font& font,RenderWindow& window);
        friend void voo();
        virtual ~InterfaceConAdmin();
        InterfaceConAdmin(const InterfaceConAdmin& other);
        InterfaceConAdmin& operator=(const InterfaceConAdmin& other);
        void InputTextRecup(RenderWindow& window, Event event);
        void Confirm(RenderWindow& window);
        void draw(RenderWindow& window);

    protected:

    private:
        Sprite background,title;
        Button btnConfirm, btnBack;

        TextField* textMdp;
        TextField* inputMdp;

        void initBackGround(Texture& title,Texture& tex,RenderWindow& window);
        void createButton(Font& font,Texture& tex,RenderWindow& window);

        int COUNT_CHAR = 0;
        sf::String mdpInput;
};

#endif // INTERFACECONADMIN_H
