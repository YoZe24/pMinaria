#ifndef INTERFACETABLESCORE_H
#define INTERFACETABLESCORE_H
#include "GestionUser.h"
#include "TextField.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include <sstream>
using namespace std;
using namespace sf;

class InterfaceTableScore
{
    public:
        InterfaceTableScore(Texture& title,Texture& textureBG,Texture& textureBTN, Texture& TextureTXT,Font& font,RenderWindow& window);
        InterfaceTableScore();
        virtual ~InterfaceTableScore();
        InterfaceTableScore(const InterfaceTableScore& other);
        InterfaceTableScore& operator=(const InterfaceTableScore& other);
        void draw(RenderWindow& window);
        void initListScores(RenderWindow& window, Texture& textureTXT);
        void handleInput(RenderWindow& window);

    protected:

    private:
        Sprite background,title;
        TextField* text;
        vector <TextField*> listName;
        vector <TextField*> listScores;
        vector<User*> users;
        Button btnBack;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex, RenderWindow& window);
};

#endif // INTERFACETABLESCORE_H
