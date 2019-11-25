#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>


class TextField
{
    public:
        TextField();
        TextField(sf::Vector2f position, sf::Texture& texture, std::string str);
        TextField(sf::Vector2f position,std::string textStr,std::string strFile);
        virtual ~TextField();
        TextField(const TextField& other);
        TextField& operator=(const TextField& other);
        void draw(sf::RenderWindow& window);
        void setTextInput(sf::String);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void setSelected(bool newSelect);
        bool getSelected();
        sf::Text getText();
        bool isClicked(sf::RenderWindow& window);
        void setTexture(sf::Texture text);
        bool isHovered(sf::RenderWindow& window);

    protected:

    private:
        sf::Texture texture;
        sf::Text text;
        sf::Sprite sprite;
        sf::Font font;
        sf::Vector2f position;
        bool select;
};

#endif // TEXTFIELD_H
