#ifndef BUTTON_H
#define BUTTON_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "gui/ButtonState.h"
#include <string>

class Button
{
    public:

        Button();
        Button(sf::Texture& texture,sf::Font& font,std::string str);
        virtual ~Button();

        void draw(sf::RenderWindow& window);
        bool isClicked(sf::RenderWindow& window);

        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        sf::Text getText();

        void addSpriteFullSize(sf::IntRect,ButtonState state);
        void addSpriteResized(sf::IntRect,ButtonState state,float valueX,float valueY);
        sf::Sprite getSprite(ButtonState state);

    protected:

    private:

        std::vector<sf::Sprite> sprites;
        ButtonState state;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Text text;

        bool isHovered(sf::RenderWindow& window);
};

#endif // BUTTON_H
