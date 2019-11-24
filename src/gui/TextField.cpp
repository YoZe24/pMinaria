#include "gui/TextField.h"
#include <iostream>
using std::cout;

/**
*   Constructor
*   Initialisation position, text into texfield, and texture's texfield
*   @param position : Vector2f who represent the position in window
*   @param textStr : a string who represent text into texfield
*   @param strFile : a string who represent the file name of a texture
*/
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
/**
*   Default constructor
*/
TextField::TextField(){}

/**
*   Function who return the attribute text
*/
Text TextField::getText(){
    return text;
}
/**
*   Constructor overloading
*   Initialisation of position, Texture and text into textfield
*   @param position : Vector2f who represent the position in window
*   @param tex : paramter passing by reference / a texture for textfield
*   @param textStr : a string who represent text into texfield
*/
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
/**
*   Destructor
*   Not implemented
*/
TextField::~TextField()
{
    //dtor
}
/**
*   Function who permet to modif the text into texfield
    @param str : a variable sf::String
*/
void TextField::setTextInput(sf::String str){
    text.setString(str);
}
/**
*   Copy Constructor
*   Parameter passing by reference
*   recup attribut from other object : position, text, texture
*   @param other : reference constant of a Textfield object
*/
TextField::TextField(const TextField& other)
{
    this->position = other.position;
    /*this->text = other.text;
    this->texture = other.texture;*/
}
/**
*   Operator= overloading
*   Parameter passing by reference
*   recup attribut from other object : position, text, texture
*   @param other : reference constant of a Textfield object
*/
TextField& TextField::operator=(const TextField& rhs)
{
    if (this == &rhs) return *this;
    /*this->position = rhs.position;
    this->text = rhs.text;
    this->texture = rhs.texture;*/
    return *this;
}
/**
*   Function who permet to put differente component of textfield
*   Parameter passing by reference
*   call function draw() from RenderWindow class
*   @param other : reference of a RenderWindow
*/
void TextField::draw(RenderWindow& window)
{
    isHovered(window);
    window.draw(sprite);
    window.draw(text);
}

/**
*   Function who can detect if the cursor mouse is on textfield
*   Parameter passing by reference
*   Return true or false according to the sprite position and mouse position
*   @param other : reference of RenderWindow object
*/
bool TextField::isHovered(RenderWindow& window)
{
    Sprite tmpSprite = sprite;
    FloatRect spriteRect = tmpSprite.getGlobalBounds();
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    return spriteRect.contains(mousePos);
}


/**
*   Function to know if textfield is clicked
*   Parameter passing by reference
*   if mouse button is pressed and function onHover() is true, return true
*   @param other : reference of RenderWindow object
*/
bool TextField::isClicked(RenderWindow& window)
{
    bool mousePressed = Mouse::isButtonPressed(Mouse::Left);
    return (mousePressed && isHovered(window));
}
/**
*   Function who permet to modif the text into texfield
    @param str : a variable Vector2f (new position)
*/
void TextField::setPosition(Vector2f position)
{
    this->position = position;
}
/**
*   Function who return the attribute position
*/
Vector2f TextField::getPosition()
{
    return position;
}
/**
*   Function who return the attribute select
*/
bool TextField::getSelected(){
    return select;
}
/**
*   Function who permet to modif the select attribute of texfield
    @param str : a variable bool (new select)
*/
void TextField::setSelected(bool newSel){
    this->select = newSel;
}
/**
*   Function who permet to modif the texture of texfield
    @param str : a variable Texture (new Texture)
*/
void TextField::setTexture(Texture text){
    this->texture = text;
}
