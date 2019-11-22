#include "gui/MainMenu.h"


/**
*   Default constructor
*/
MainMenu::MainMenu(){}

/**
*   Main constructor
*
*   We used 2 functions to create and initialize our menu (avoid big code in the constructor).
*
*   @param title : Title's sprite
*   @param textureBG : Background's texture
*   @param textureBTN : Buttons' texture
*   @param font : Buttons' font
*   @param window : Game's window to send to our initializing functions
*
*/
MainMenu::MainMenu(Texture& title,Texture& textureBG,Texture& textureBTN,Font& font,RenderWindow& window)
{
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
MainMenu::~MainMenu()
{
    //dtor
}


/**
*
*   Drawing all elements of menu
*
*   @param window : @param window : Window of the game to draw our menu
*
*/
void MainMenu::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    playButton.draw(window);
    connectionButton.draw(window);
    optionButton.draw(window);
    quitButton.draw(window);
    adminButton.draw(window);
    scoreBoardButton.draw(window);
}

/**
*
*   Check on which button the user clicked
*
*   We used the isClicked() function from Button class to check if we click on it.
*
*   @param window : Game's window to check if we click on the button's area
*
*/
void MainMenu::update(RenderWindow& window)
{
    if(playButton.isClicked(window))
    {
        cout << "PLAY BUTTON CLICKED" << endl;
    }
    else if(connectionButton.isClicked(window))
    {
        cout << "CONNECTION BUTTON CLICKED" << endl;
    }
    else if(optionButton.isClicked(window))
    {
        cout << "OPTION BUTTON CLICKED" << endl;
    }
    else if(quitButton.isClicked(window))
    {
        cout << "QUIT BUTTON CLICKED" << endl;
    }
    else if(adminButton.isClicked(window))
    {
        cout << "ADMIN BUTTON CLICKED" << endl;
    }
    else if(scoreBoardButton.isClicked(window))
    {
        cout << "SCORE BUTTON CLICKED" << endl;
    }
}


/**
*
*   Check user's interactions and draw our menu
*
*   @param window : Game's window to draw our components and check the interactions with the game
*
*/
void MainMenu::handleInput(RenderWindow& window)
{
    draw(window);
    update(window);
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
void MainMenu::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
{
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = tex.getSize();

    this->title.setTexture(title);
    background.setTexture(tex);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
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
void MainMenu::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    int buttonW = tex.getSize().x;
    int buttonH = tex.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    playButton = Button(tex,font,"Play");
    connectionButton = Button(tex,font,"Connection");
    optionButton = Button(tex,font,"Option");
    quitButton = Button(tex,font,"Quit");
    adminButton = Button(tex,font,"Admin");
    scoreBoardButton = Button(tex,font,"Scoreboard");


    playButton.setPosition(Vector2f((float)(windowW-windowW/2) - buttonW/2,title.getPosition().y + 125));
    playButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    playButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    connectionButton.setPosition(Vector2f((float)(windowW-windowW/2) - buttonW/2,playButton.getPosition().y + 125));
    connectionButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    connectionButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    optionButton.setPosition(Vector2f((float) (windowW-windowW/2) - buttonW/2,connectionButton.getPosition().y + 125));
    optionButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    optionButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);


    quitButton.setPosition(Vector2f((float)windowW/1.65 - buttonW,optionButton.getPosition().y + 125));
    quitButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    quitButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    adminButton.setPosition(Vector2f((float)windowW - buttonW + 50,windowH - 100));
    adminButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL, 0.75,0.75);
    adminButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED, 0.75,0.75);

    scoreBoardButton.setPosition(Vector2f(0,windowH - 100));
    scoreBoardButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL, 0.75,0.75);
    scoreBoardButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED, 0.75,0.75);

}
