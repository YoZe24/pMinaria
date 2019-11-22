#include "gui/OptionMenu.h"
#include <iostream>

/**
*   Default constructor
*/
OptionMenu::OptionMenu(){}

/**
*   Main constructor
*
*   We used 3 functions to create and initialize our menu (avoid big code in the constructor).
*
*   @param title : Title's sprite
*   @param textureBG : Background's texture
*   @param textureBTN : Buttons' texture
*   @param font : Buttons' font
*   @param window : Game's window to send to our initializing functions
*
*/
OptionMenu::OptionMenu(Texture& title,Texture& textureBG,Texture& textureBTN,Font& font,RenderWindow& window)
{
    initSliders(window);
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
}

/**
*
*   Menu's destructor
*
*   /\Not implemented/\
*
*/
OptionMenu::~OptionMenu()
{
    //dtor
}

/**
*
*   Menu's copy constructor
*
*   /\Not implemented/\
*
*/
OptionMenu::OptionMenu(const OptionMenu& other)
{
    //copy ctor
}

/**
*
*   Operator= menu
*
*   /\Not implemented/\
*
*/
OptionMenu& OptionMenu::operator=(const OptionMenu& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


/**
*
*   Drawing all elements of menu
*
*   @param window : @param window : Window of the game to draw our menu
*
*/
void OptionMenu::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    easyModeButton.draw(window);
    mediumModeButton.draw(window);
    hardModeButton.draw(window);
    backMainMenuButton.draw(window);
    sliderTime.draw(window);
    sliderDurability.draw(window);
}

/**
*
*   Check on which button the user clicked
*
*   We used the isClicked() function from Button class to check if we click on it.
*   We set default values for the slider.
*
*   @param window : Game's window to check if we click on the button's area
*
*/
void OptionMenu::update(RenderWindow& window)
{
    if(easyModeButton.isClicked(window))
    {
        //cout << "EASY BUTTON CLICKED" << endl;
        updateSliders(8,0);
    }
    else if(mediumModeButton.isClicked(window))
    {
        //cout << "NORMAL BUTTON CLICKED" << endl;
        updateSliders(6,1);
    }
    else if(hardModeButton.isClicked(window))
    {
        //cout << "HARD BUTTON CLICKED" << endl;
        updateSliders(3,2);
    }
    else if(backMainMenuButton.isClicked(window))
    {
        //cout << "BACK BUTTON CLICKED" << endl;
        saveOptions();
    }
}

/**
*
*   Check user's interactions and draw our menu
*
*   @param window : Game's window to draw our components and check the interactions with the game
*
*/
void OptionMenu::handleInput(RenderWindow& window)
{
    draw(window);
    update(window);
}

/**
*
*   Initialize buttons from menu
*
*   We initialize all buttons and set their texture and position.
*   We use the window's size to place correctly buttons.
*
*   @param font : Button's font
*   @param tex : Buttons' texture
*   @param window : Game's window to get size and set position of elements
*
*/
void OptionMenu::createButton(Font& font, Texture& tex, RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    easyModeButton = Button(texture,font,"EASY");
    mediumModeButton = Button(texture,font,"NORMAL");
    hardModeButton = Button(texture,font,"HARD");
    backMainMenuButton = Button(texture,font,"BACK");

    easyModeButton.setPosition(Vector2f((float) (windowW*0.15) - texture.getSize().x/2,windowH*0.20));
    easyModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    easyModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    mediumModeButton.setPosition(Vector2f((float) (easyModeButton.getPosition().x + easyModeButton.getSprite(NORMAL).getGlobalBounds().width*2) - texture.getSize().x/2,windowH*0.20));
    mediumModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    mediumModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    hardModeButton.setPosition(Vector2f((float) (mediumModeButton.getPosition().x + mediumModeButton.getSprite(NORMAL).getGlobalBounds().width*2) - texture.getSize().x/2,windowH*0.20));
    hardModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    hardModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    backMainMenuButton.setPosition(Vector2f(easyModeButton.getPosition().x,windowH - 150));
    backMainMenuButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,0.75,1);
    backMainMenuButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,0.75,1);
}

/**
*
*   Initialize our background and set the title
*
*   We set scale with the window's size and background's sprite's size.
*   We define the ratio and set the background's size.
*
*   @param title : Texture of the game's title
*   @param tex : Background's texture
*   @param window : Game's window to get size and set the components' position
*
*/
void OptionMenu::initBackGround(Texture& title,Texture& tex, RenderWindow& window)
{
    Texture& texture = tex;
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = texture.getSize();

    this->title.setTexture(title);
    background.setTexture(texture);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
}

/**
*
*   Initialize sliders from menu
*
*   We initialize all sliders and set their values and position.
*   We use the window's size to place correctly sliders.
*
*   @param window : Game's window to get size and set position of elements
*
*/
void OptionMenu::initSliders(RenderWindow& window)
{
    sliderTime = SliderSFML(window.getSize().x*0.20,window.getSize().y*0.60);
    sliderTime.create(3,10);
    sliderTime.setSliderValue(6);

    sliderDurability = SliderSFML(window.getSize().x*0.60,window.getSize().y*0.60);
    sliderDurability.create(0.5,2);
    sliderDurability.setSliderValue(1);
}


/**
*
*   Change sliders' values
*
*   @param time : Game's time's value
*   @param durability : Blocks' durability's value
*
**/
void OptionMenu::updateSliders(int time, int durability)
{
    sliderDurability.setSliderValue(durability);
    sliderTime.setSliderValue(time);
}


/**
*
*   Save game options to play with selected values
*
*/
void OptionMenu::saveOptions()
{
    /*

        game::getInstance().setFactDurability(sliderDurability.getSliderValue());
        game::getInstance().setTimer(sliderTime.getSliderValue());


    */

    std::cout << sliderTime.getSliderValue() << endl;
    std::cout << sliderDurability.getSliderValue() << endl;
    system("pause");
}





