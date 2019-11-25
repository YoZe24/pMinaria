#include "GameStateConAdmin.h"
#define MDP "123"
/**
*   Main constructor
*
*   We used 2 functions to create and initialize our admin connexion interface (avoid big code in the constructor).
*   Creation 2 textfields (pointer declaration)
*/
GameStateConAdmin::GameStateConAdmin(Game* game)
{
    this->game = game;
    loadTextures();
    initBackGround(textureTitle,textureBG,this->game->window);
    createButton(font,textureBTN,this->game->window);
    textMdp = new TextField(Vector2f(200,350),textureTXT,"Mot de passe :");
    inputMdp = new TextField(Vector2f(600,350),textureTXT," 'Ecrivez' ");
}

GameStateConAdmin::~GameStateConAdmin()
{
    delete textMdp;
    delete inputMdp;
}

GameStateConAdmin::GameStateConAdmin(const GameStateConAdmin& other)
{
    //copy ctor
}

GameStateConAdmin& GameStateConAdmin::operator=(const GameStateConAdmin& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    return *this;
}
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void GameStateConAdmin::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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
/**
*   Function who permet to create buttons of interface
*   initialisation of different buttons (position, texture, font)-> call in constructor
*   @param font : an object Font (represent the font of text into button)
*   @param tex : an object Texture (represent the texture of button)
*   @param window : a RenderWindow object (represent the window)
*/
void GameStateConAdmin::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    btnConfirm = Button(texture,font,"Confirm");

    //btnConfirm.setPosition(Vector2f((windowW-windowW/3),windowH/1.3));
    btnConfirm.setPosition(Vector2f(800,550));
    btnConfirm.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnConfirm.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnConfirm.getText().setPosition(22,22);

    btnBack = Button(texture,font,"Back");

    //btnBack.setPosition(Vector2f(windowW/14,windowH/1.3));
    btnBack.setPosition(Vector2f(150,550));
    btnBack.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnBack.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnBack.getText().setPosition(22,22);
}
/**
*   Function who permet to recup the text entered
*
*   Event text entered detect a keyboard entered
*   a condition to test unicode, different of 8 (backspace) and not too long
*   Recup text entered and call setTextInput() from textfield -> display on window
*   if "event.text.unicode == 8 -> remove last character from input text
*
*   @param window : Reference of RenderWindow
*   @param event : recup event from main
*
*/
void GameStateConAdmin::InputTextRecup(RenderWindow& window, sf::Event event){
    if (event.type == sf::Event::TextEntered)
    {
        if(event.text.unicode < 128 && event.text.unicode !=8 && mdpInput.getSize() <= 15)
        {
            mdpInput +=event.text.unicode;
            inputMdp->setTextInput(mdpInput);
            COUNT_CHAR++;
            cout<<COUNT_CHAR<<endl;
        }
        if(event.text.unicode == 8)
        {
            if(COUNT_CHAR >= 0){
                mdpInput.erase(COUNT_CHAR,1);
                inputMdp->setTextInput(mdpInput);
                COUNT_CHAR--;
            }
        }
    }
}
/**
*   Function who permet verification of password admin
*   Recup text entered (mdp) -> Compare to Constant MDP
*   If same -> access to "interfaceadmin"
*   @param window : Reference of RenderWindow object
*
*/
void GameStateConAdmin::Confirm(RenderWindow& window){
    if(btnConfirm.isClicked(window)){
        sf::Text mdpText = inputMdp->getText();
        string mdpString = mdpText.getString();
        if(mdpString.compare(MDP)==0){
            this->game->pushState(new GameStateAdmin(this->game));
        }else {
            cout<<"ACCES INVALIDE";
        }

    }
}
/**
*   Function who permet to add component in window
*   call of draw method (SFML class)
*   @param st : a const float
*/
void GameStateConAdmin::draw(const float dt){
    this->game->window.draw(background);
    this->game->window.draw(title);
    textMdp->draw(this->game->window);
    inputMdp->draw(this->game->window);
    btnConfirm.draw(this->game->window);
    btnBack.draw(this->game->window);
}
void GameStateConAdmin::update(const float dt){
    if(btnBack.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
    }
}
void GameStateConAdmin::handleInput(){
    Event event;
    while (this->game->window.pollEvent(event))
    {
        InputTextRecup(this->game->window, event);
        Confirm(this->game->window);
        if (event.type == Event::Closed)
            this->game->window.close();

    }
    draw(0.0);
}
void GameStateConAdmin::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}

