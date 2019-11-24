#include "GameStateCon.h"
/**
*   Main constructor
*
*   We used 2 functions to create and initialize our connexion interface (avoid big code in the constructor).
*   Creation 2 textfields (pointer declaration)
*
*   @param title : Title's sprite
*   @param textureBG : Background's texture
*   @param textureBTN : Buttons' texture
*   @param textureTXT : Textfield' texture
*   @param font : Buttons' font
*   @param window : Game's window to send to our initializing functions
*
*/
GameStateCon::GameStateCon(Game* game)
{
    this->game = game;
    loadTextures();
    initBackGround(textureTitle,textureBG,this->game->window);
    createButton(font,textureBTN,this->game->window);
    textLogin = new TextField(Vector2f(200,350),textureTXT,"Nom Utilisateur :");
    inputLogin = new TextField(Vector2f(600,350),textureTXT," 'Ecrivez' ");
}
/**
*   Destructor
*   Destruction of 2 textfields created in constructor (pointer agregation)
*/
GameStateCon::~GameStateCon()
{
    delete textLogin;
    delete inputLogin;
}

GameStateCon::GameStateCon(const GameStateCon& other)
{
    //copy ctor
}

GameStateCon& GameStateCon::operator=(const GameStateCon& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
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
void GameStateCon::InputTextRecup(RenderWindow& window, sf::Event event){
    if (event.type == sf::Event::TextEntered)
    {
        if(event.text.unicode < 128 && event.text.unicode !=8 && loginInput.getSize() <= 15)
        {
            loginInput +=event.text.unicode;
            inputLogin->setTextInput(loginInput);
            COUNT_CHAR++;
            //cout<<COUNT_CHAR<<endl;
        }
        if(event.text.unicode == 8)
        {
            if(COUNT_CHAR >= 0){
                loginInput.erase(COUNT_CHAR,1);
                inputLogin->setTextInput(loginInput);
                COUNT_CHAR--;
            }
        }
    }
}
/**
*   Function who permet creation of user (verficiation if exist -> addUser())
*   Recup text entered (login)
*   If not already in instance -> creation new user + add to instance of GestionUser
*   @param window : Reference of RenderWindow object
*
*/
void GameStateCon::Confirm(RenderWindow& window){
    if(btnConfirm.isClicked(window)){
        sf::Text nameText = inputLogin->getText();
        sf::String nameString = nameText.getString();
        vector<int> scores;
        User* user = new User(nameString,scores);
        GestionUser::getInstance()->addUser(user);
        for(int i =0; i<GestionUser::getInstance()->getUsers().size();i++){
            if(GestionUser::getInstance()->getUsers()[i]->getLogin() == nameString){
                GestionUser::getInstance()->setUserCurrent(GestionUser::getInstance()->getUsers()[i]);
                cout<<GestionUser::getInstance()->getUserCurrent()->str();
            }
        }
    }
}
/**
*   Function who permet to add component in window
*   call of draw method (SFML class)
*   @param st : a const float
*/
void GameStateCon::draw(const float dt){
    this->game->window.draw(background);
    this->game->window.draw(title);
    textLogin->draw(this->game->window);
    inputLogin->draw(this->game->window);
    btnConfirm.draw(this->game->window);
    btnBack.draw(this->game->window);
}
void GameStateCon::update(const float dt){
    if(btnConfirm.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
    }
    else if(btnBack.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
    }
}
void GameStateCon::handleInput(){
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
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void GameStateCon::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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
*   Function who permet to create buttons of interface
*   initialisation of different buttons (position, texture, font)-> call in constructor
*   @param font : an object Font (represent the font of text into button)
*   @param tex : an object Texture (represent the texture of button)
*   @param window : a RenderWindow object (represent the window)
*/
void GameStateCon::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    btnConfirm = Button(texture,font,"Confirm");

    btnConfirm.setPosition(Vector2f((windowW-windowW/3),windowH/1.3));
    btnConfirm.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnConfirm.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnConfirm.getText().setPosition(22,22);

    btnBack = Button(texture,font,"Back");

    btnBack.setPosition(Vector2f(windowW/14,windowH/1.3));
    btnBack.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnBack.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnBack.getText().setPosition(22,22);

}

void GameStateCon::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}
