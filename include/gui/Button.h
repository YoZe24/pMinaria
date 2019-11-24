#ifndef BUTTON_H
#define BUTTON_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "ButtonState.h"
#include <string>

using namespace std;
using namespace sf;

class Button
{
    public:

        Button();
        Button(Texture& texture,Font& font,string str);
        virtual ~Button();

        void draw(RenderWindow& window);
        bool isClicked(RenderWindow& window);

        void setPosition(Vector2f position);
        Vector2f getPosition();
        Text getText();

        void addSpriteFullSize(IntRect,ButtonState state);
        void addSpriteResized(IntRect,ButtonState state,float valueX,float valueY);
        Sprite getSprite(ButtonState state);

    protected:

    private:

        vector<Sprite> sprites;
        ButtonState state;
        Texture texture;
        Vector2f position;
        Text text;


        bool isHovered(RenderWindow& window);
};

#endif // BUTTON_H
