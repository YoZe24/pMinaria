#include "gui/Button.h"
#include <iostream>

/**
*   Default constructor
*/
Button::Button() {}

/**
*
*   Main constructor to build a button
*
*   We set our button state and text.
*   State is used to describe if the button is hovered or not, we set the default value "NORMAL"
*
*   @param texture : Texture of our button
*   @param font : Font for our text in button
*   @param : str : Text of our button
*
*/
Button::Button(Texture& texture,Font& font,string str):texture(texture)
{
    state = NORMAL;
    text = Text(str,font,25);
}

/**
*
*   Button's destructor
*
*   /\Not implemented/\
*
*/
Button::~Button()
{
    //dtor
}

/**
*
*   Set the texture on the button
*
*   Based on button's state, we set the texture.
*   This method fit the button with the full size texture.
*   The button has a vector with sprite and we add sprites as he has states.
*   NB: we could used a map.
*
*   @param intRect : Rect to define the button's size and his texture
*   @param state : State of the button ("NORMAL" or "PRESSED")
*
*/
void Button::addSpriteFullSize(IntRect intRect, ButtonState state)
{
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(intRect);
    sprites.push_back(sprite);
}

/**
*
*   Set the texture on the button
*
*   Based on button's state, we set the texture.
*   This method fit the button with the texture and we resize the sprite to have bigger/smaller button with setScale()
*   The button has a vector with sprite and we add sprites as he has states.
*   NB: we could used a map.
*
*   @param : intRect : Rect to define the button's size and his texture
*   @param : state : State of the button ("NORMAL" or "PRESSED")
*   @param : valueX : Value to expand on X the sprite's size
*   @param : valueY : Value to expand on Y the sprite's size
*/
void Button::addSpriteResized(IntRect intRect, ButtonState state, float valueX, float valueY)
{
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(intRect);
    sprite.setScale(valueX,valueY);
    text.setScale(valueX,valueY);
    sprites.push_back(sprite);
}

/**
*
*   Drawing all elements of button
*
*   We set the text's position to center our text in the button.
*   We test if we have our mouse hover the button to change his state and therefor change his sprite.
*
*   @param window : @param window : Window of the game to draw our button
*
*/
void Button::draw(RenderWindow& window)
{
    Sprite tmpSprite = sprites[state];
    tmpSprite.setPosition(position);
    text.setPosition(position.x + tmpSprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + tmpSprite.getGlobalBounds().height/2 - text.getGlobalBounds().height/1.2);

    if(isHovered(window))
    {
        state = PRESSED;
        text.setPosition(position.x + tmpSprite.getGlobalBounds().width/2 - text.getGlobalBounds().width/2, position.y + 5 + tmpSprite.getGlobalBounds().height/2 - text.getGlobalBounds().height/1.2);

    }
    else
    {
        state = NORMAL;
    }

    window.draw(tmpSprite);
    window.draw(text);
}


/**
*
*   Check if the user clicked on the button
*
*   We used the methode isHovered() to check if the mouse is in the button's area and therefor if we press the left click.
*
*   @param window : Window of the game to check the mouse
*   @return value : Left click pressed and mouse hovered the button
*
*/
bool Button::isClicked(RenderWindow& window)
{
    bool mousePressed = Mouse::isButtonPressed(Mouse::Left);
    return (mousePressed && isHovered(window));
}


/**
*
*   Set the position our or button
*
*   @param position : Vector2f to set our button's position
*/
void Button::setPosition(Vector2f position)
{
    this->position = position;
}

/**
*
*   Return the button's position
*
*   @return sliderValue : Return button's position
*
*/
Vector2f Button::getPosition()
{
    return position;
}

/**
*
*   Return the button's text
*
*   @return sliderValue : Return button's text
*
*/
Text Button::getText()
{
    return text;
}



/**
*
*   Check if the mouse is in the button's area
*
*   We get the sprite's bounds to fix the button's area.
*   We used mapPixelToCoords() to have the good coordinates of our mouse and if we resize the window, the button is always functional.
*
*   @param window : Window of the game to check the mouse
*   @return value : Mouse is in the button's area
*
**/
bool Button::isHovered(RenderWindow& window)
{
    Sprite tmpSprite = sprites[state];
    tmpSprite.setPosition(position);

    FloatRect spriteRect = tmpSprite.getGlobalBounds();
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    return spriteRect.contains(mousePos);
}

/**
*
*   Return the sprite based on state
*
*   @param state : Button's state ("NORMAL" or "PRESSED")
*   @return value : Corresponding sprite
*
**/
Sprite Button::getSprite(ButtonState state)
{
    return sprites[state];
}



