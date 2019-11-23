#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace sf;

//Classe qui me permet créer des zones de texte

class TextField
{
    public:
        TextField();
        TextField(Vector2f position, Texture& texture, string str);
        TextField(Vector2f position,string textStr,string strFile);
        virtual ~TextField();
        TextField(const TextField& other);
        TextField& operator=(const TextField& other);
        void draw(RenderWindow& window);
        void setTextInput(sf::String);
        void setPosition(Vector2f position);
        Vector2f getPosition();
        void setSelected(bool newSelect);
        bool getSelected();
        Text getText();
        bool isClicked(RenderWindow& window);
        void setTexture(Texture text);
        bool isHovered(RenderWindow& window);

    protected:

    private:
        Texture texture;
        Text text;
        Sprite sprite;
        Font font;
        Vector2f position;
        bool select;
};

#endif // TEXTFIELD_H
