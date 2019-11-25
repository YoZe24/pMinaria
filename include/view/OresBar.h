#ifndef ORESBAR_H
#define ORESBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "view/Pickaxe.h"

class OresBar
{
    public:
        OresBar();
        virtual ~OresBar();
        OresBar(const OresBar& other);

        void draw(sf::RenderWindow& window);
        void update(int nbOresCraft,int nbOres, int currentPickaxe);
    protected:

    private:
        sf::RectangleShape oreBar,oreBorder,spriteBorder;
        sf::Text oreText;
        sf::Font font;
        sf::Texture textureBlock;
        sf::Sprite spriteBlock;
        int sizeX, currentPickaxe;
};

#endif // ORESBAR_H
