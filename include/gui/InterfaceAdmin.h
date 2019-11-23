#ifndef INTERFACEADMIN_H
#define INTERFACEADMIN_H
#include "model/GestionUser.h"
#include "TextField.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

#include <string>
#include <sstream>
using namespace std;
using namespace sf;

class InterfaceAdmin
{
    public:
        InterfaceAdmin(Texture& title,Texture& textureBG,Texture& textureBTN, Texture& TextureTXT,Font& font,RenderWindow& window);
        InterfaceAdmin();
        virtual ~InterfaceAdmin();
        InterfaceAdmin(const InterfaceAdmin& other);
        InterfaceAdmin& operator=(const InterfaceAdmin& other);
        void draw(RenderWindow& window);
        void initListName(RenderWindow& window, Texture& textureTXT);
        void initListScores(RenderWindow& window, Texture& textureTXT);
        void Delete(RenderWindow& window);
        void getTextFieldSelected(RenderWindow& window);
        int getPositionSelected();
        void setPositionSelected(int newPosition);
        void handleInput(RenderWindow& window);

    protected:

    private:
        Sprite background,title;
        TextField* text;
        vector <TextField*> listName;
        vector <TextField*> listScores;
        vector<User*> users;
        Button btnDelete;
        Button btnBack;
        int positionSelected = -1;
        TextField textfieldSelected;

        void createButton(Font& font,Texture& tex,RenderWindow& window);
        void initBackGround(Texture& title,Texture& tex, RenderWindow& window);
};

#endif // INTERFACEADMIN_H
