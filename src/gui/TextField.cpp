#include "gui/TextField.h"
#include <iostream>
using std::cout;

//Constructeur (Position, Texte à afficher, Le fichier de texture)
TextField::TextField(Vector2f position,string textStr,string strFile)
{
    this->select = false;

    texture.loadFromFile(strFile);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,sprite.getGlobalBounds().width,sprite.getGlobalBounds().height/2));
    sprite.setPosition(position);

    font.loadFromFile("PixelEmulator-xq08.ttf");

    text.setString(textStr);
    text.setColor(Color::Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(position.x + sprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + sprite.getGlobalBounds().height/2 - text.getGlobalBounds().height/1.2);
}

Text TextField::getText(){
    return text;
}
//Constructeur (Position, Objet Texture, texte à afficher)
TextField::TextField(Vector2f position, Texture& tex, string textStr){
    this->select = false;

    texture = tex;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,sprite.getGlobalBounds().width,sprite.getGlobalBounds().height/2));
    sprite.setPosition(position);

    font.loadFromFile("PixelEmulator-xq08.ttf");

    text.setString(textStr);
    text.setColor(Color::Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(position.x + sprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + sprite.getGlobalBounds().height/2 - text.getGlobalBounds().height/1.2);
}


TextField::TextField(){
}

TextField::~TextField()
{
    //dtor
}
//Permet de modifier le texte contenu
void TextField::setTextInput(sf::String str){
    text.setString(str);
}



TextField::TextField(const TextField& other)
{
    this->position = other.position;
}

TextField& TextField::operator=(const TextField& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void TextField::draw(RenderWindow& window)
{
    onHover(window);
    window.draw(sprite);
    window.draw(text);
}


bool TextField::onHover(RenderWindow& window)
{
    if(Mouse::getPosition(window).x >= sprite.getPosition().x &&
       Mouse::getPosition(window).x < sprite.getPosition().x + sprite.getGlobalBounds().width &&
       Mouse::getPosition(window).y >= sprite.getPosition().y &&
       Mouse::getPosition(window).y < sprite.getPosition().y + sprite.getGlobalBounds().height)
    {
        return true;
    }

    if(Mouse::getPosition(window).x < sprite.getPosition().x ||
       Mouse::getPosition(window).x > sprite.getPosition().x + sprite.getGlobalBounds().width ||
       Mouse::getPosition(window).y < sprite.getPosition().y ||
       Mouse::getPosition(window).y > sprite.getPosition().y + sprite.getGlobalBounds().height)
    {
        return false;
    }

}


bool TextField::isClicked(RenderWindow& window)
{
    bool mousePressed = Mouse::isButtonPressed(Mouse::Left);
    return (mousePressed && onHover(window));
}

void TextField::setPosition(Vector2f position)
{
    this->position = position;
}
Vector2f TextField::getPosition()
{
    return position;
}
bool TextField::getSelected(){
    return select;
}

void TextField::setSelected(bool newSel){
    this->select = newSel;
}
void TextField::setTexture(Texture text){
    this->texture = text;
}
