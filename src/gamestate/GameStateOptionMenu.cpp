#include "gamestate/GameStateOptionMenu.h"
#include "gamestate/GameStateMainMenu.h"
using namespace sf;
using namespace std;

/**
*   Main constructor
*
*   We used 3 functions to create and initialize our menu (avoid big code in the constructor).
*/
GameStateOptionMenu::GameStateOptionMenu(Game* game)
{
    this->game = game;
    loadTextures();
    initSliders(this->game->window);
    initBackGround(textureTitle,textureBG,this->game->window);
    createButton(font,textureBTN,this->game->window);
}

GameStateOptionMenu::~GameStateOptionMenu()
{
    //dtor
}

GameStateOptionMenu::GameStateOptionMenu(const GameStateOptionMenu& other)
{
    //copy ctor
}

GameStateOptionMenu& GameStateOptionMenu::operator=(const GameStateOptionMenu& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
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
void GameStateOptionMenu::createButton(Font& font, Texture& tex, RenderWindow& window)
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

    //easyModeButton.setPosition(Vector2f((float) (windowW*0.15) - texture.getSize().x/2,windowH*0.20));
    easyModeButton.setPosition(Vector2f(100,125));
    easyModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    easyModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    //mediumModeButton.setPosition(Vector2f((float) (easyModeButton.getPosition().x + easyModeButton.getSprite(NORMAL).getGlobalBounds().width*2) - texture.getSize().x/2,windowH*0.20));
    mediumModeButton.setPosition(Vector2f(500,125));
    mediumModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    mediumModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    //hardModeButton.setPosition(Vector2f((float) (mediumModeButton.getPosition().x + mediumModeButton.getSprite(NORMAL).getGlobalBounds().width*2) - texture.getSize().x/2,windowH*0.20));
    hardModeButton.setPosition(Vector2f(900,125));
    hardModeButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,1,1);
    hardModeButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,1,1);

    //backMainMenuButton.setPosition(Vector2f(easyModeButton.getPosition().x,windowH - 150));
    backMainMenuButton.setPosition(Vector2f(100,550));
    backMainMenuButton.addSpriteResized(IntRect(0,0,buttonW,buttonH/2),NORMAL,0.75,1);
    backMainMenuButton.addSpriteResized(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED,0.75,1);
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
void GameStateOptionMenu::initSliders(RenderWindow& window)
{
    sliderTime = SliderSFML(200,350);
    sliderTime.create(1,5);
    sliderTime.setSliderValue(2);

    sliderDurability = SliderSFML(700,350);
    sliderDurability.create(0.5,2);
    sliderDurability.setSliderValue(1);
}
/**
*
*   Drawing all elements of menu
*
*   @param st : const float
*
*/
void GameStateOptionMenu::draw(const float dt){
    this->game->window.draw(background);
    this->game->window.draw(title);
    easyModeButton.draw(this->game->window);
    mediumModeButton.draw(this->game->window);
    hardModeButton.draw(this->game->window);
    backMainMenuButton.draw(this->game->window);
    sliderTime.draw(this->game->window);
    sliderDurability.draw(this->game->window);
}
/**
*
*   Change sliders' values
*
*   @param time : Game's time's value
*   @param durability : Blocks' durability's value
*
**/
void GameStateOptionMenu::updateSliders(int time, float durability)
{
    sliderDurability.setSliderValue(durability);
    sliderTime.setSliderValue(time);
}


/**
*
*   Save game options to play with selected values
*
*/
void GameStateOptionMenu::saveOptions(Game* game)
{
    game->TIME_TIMER = sliderTime.getSliderValue();
    game->DURABILITY = sliderDurability.getSliderValue();
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
void GameStateOptionMenu::initBackGround(Texture& title,Texture& tex, RenderWindow& window)
{
    Texture& texture = tex;
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = texture.getSize();

    this->title.setTexture(title);
    background.setTexture(texture);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    //this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
    this->title.setPosition(450,0);
}
void GameStateOptionMenu::update(const float dt){
    if(easyModeButton.isClicked(this->game->window))
    {
        updateSliders(5,0.5);
    }
    else if(mediumModeButton.isClicked(this->game->window))
    {

        updateSliders(2,1);
    }
    else if(hardModeButton.isClicked(this->game->window))
    {
        updateSliders(1,2);
    }
    else if(backMainMenuButton.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
        saveOptions(game);
    }
}
void GameStateOptionMenu::handleInput(){
    Event event;
    while (this->game->window.pollEvent(event))
    {

        if (event.type == Event::Closed)
            this->game->window.close();

    }
    draw(0.0);
}

void GameStateOptionMenu::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}
