#include "GameStateMainMenu.h"

GameStateMainMenu::GameStateMainMenu(Game* game)
{
    this->game = game;
    loadTextures();
    initBackGround(textureTitle,textureBG,this->game->window);
    createButton(font,textureBTN,this->game->window);
}

GameStateMainMenu::~GameStateMainMenu()
{
    //dtor
}

GameStateMainMenu::GameStateMainMenu(const GameStateMainMenu& other)
{
    //copy ctor
}

GameStateMainMenu& GameStateMainMenu::operator=(const GameStateMainMenu& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
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
void GameStateMainMenu::update(const float dt)
{
    if(playButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateGame(this->game));
    }
    else if(connectionButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateCon(this->game));
    }
    else if(optionButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateOptionMenu(this->game));
    }
    else if(quitButton.isClicked(this->game->window))
    {
        this->game->window.close();
    }
    else if(adminButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateConAdmin(this->game));
    }
    else if(scoreBoardButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateTableScore(this->game));
    }
}
/**
*
*   Check user's interactions and draw our menu
*
*   @param window : Game's window to draw our components and check the interactions with the game
*
*/
void GameStateMainMenu::handleInput()
{
    Event event;
    while (this->game->window.pollEvent(event))
    {
        update(0.0);
        if (event.type == Event::Closed)
            this->game->window.close();

    }
    draw(0.0);

}


void GameStateMainMenu::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}

/**
*
*   Drawing all elements of menu
*
*   @param window : @param window : Window of the game to draw our menu
*
*/
void GameStateMainMenu::draw(const float dt)
{
    this->game->window.draw(background);
    this->game->window.draw(title);
    playButton.draw(this->game->window);
    connectionButton.draw(this->game->window);
    optionButton.draw(this->game->window);
    quitButton.draw(this->game->window);
    adminButton.draw(this->game->window);
    scoreBoardButton.draw(this->game->window);
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
void GameStateMainMenu::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
{
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = tex.getSize();

    this->title.setTexture(title);
    background.setTexture(tex);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    //this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
    this->title.setPosition(450,0);
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
void GameStateMainMenu::createButton(Font& font,Texture& tex,RenderWindow& window)
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


    //playButton.setPosition(Vector2f((float)(windowW-windowW/2) - buttonW/2,title.getPosition().y + 125));
    playButton.setPosition(Vector2f(470,125));
    playButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    playButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    //connectionButton.setPosition(Vector2f((float)(windowW-windowW/2) - buttonW/2,playButton.getPosition().y + 125));
    connectionButton.setPosition(Vector2f(470,250));
    connectionButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    connectionButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    //optionButton.setPosition(Vector2f((float) (windowW-windowW/2) - buttonW/2,connectionButton.getPosition().y + 125));
    optionButton.setPosition(Vector2f(470,375));
    optionButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    optionButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);


    //quitButton.setPosition(Vector2f((float)windowW/1.65 - buttonW,optionButton.getPosition().y + 125));
    quitButton.setPosition(Vector2f(470,500));
    quitButton.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    quitButton.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);

    //adminButton.setPosition(Vector2f((float)windowW - buttonW + 50,windowH - 100));
    adminButton.setPosition(Vector2f(1000,575));
    adminButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL, 0.75,0.75);
    adminButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED, 0.75,0.75);

    //scoreBoardButton.setPosition(Vector2f(0,windowH - 100));
    scoreBoardButton.setPosition(Vector2f(15,575));
    scoreBoardButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL, 0.75,0.75);
    scoreBoardButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED, 0.75,0.75);

}
