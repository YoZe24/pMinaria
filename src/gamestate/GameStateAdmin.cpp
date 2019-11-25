#include "GameStateAdmin.h"
/**
*   Main constructor
*
*   We used 2 functions to create and initialize our admin interface (avoid big code in the constructor).
*   We used 2 functions to initialize 2 vectors of textefield (login user - score user).
*/
GameStateAdmin::GameStateAdmin(Game* game)
{
    this->game = game;
    loadTextures();
    initBackGround(textureTitle,textureBG,this->game->window);
    initListName(this->game->window, textureTXT);
    createButton(font,textureBTN,this->game->window);
    initListScores(this->game->window, textureTXT);
}

/**
*   Desctructor
*   We liberate the both texfields's vector (AIP)
*/
GameStateAdmin::~GameStateAdmin()
{
    for(int i=0;i<listName.size();i++){
        delete listName[i];
        delete listScores[i];
    }
}
/**
*   Function to initialize texfield's vector, he contains all logins user
*   For all users, we recup his login from instance (GestionUser) and we create a texfield with the value. Call Textfield constructor
*
*   @param window : a RenderWindow object (Reference)
*   @param TextureTXT : Texture textfield
*/
void GameStateAdmin::initListName(RenderWindow& window, Texture& TextureTXT){
    int windowW = window.getSize().x;
    int windowH = window.getSize().y;
    int sep = 100;
    int countG = 1;

    users = GestionUser::getInstance()->getUsers();

    for(User* user : users){
        string name = user->getLogin();
        text = new TextField(Vector2f(200, 140+sep),TextureTXT,name);
        listName.push_back(text);
        sep = sep+50;
    }
}
/**
*   Function to initialize texfield's vector, he contains all scores user
*   For all users, we recup all these scores from instance (GestionUser) and we create a texfield with the value. Call Textfield constructor
*
*   @param window : a RenderWindow object (Reference)
*   @param TextureTXT : Texture textfield
*/
void GameStateAdmin::initListScores(RenderWindow& window, Texture& TextureTXT){
    int windowW = window.getSize().x;
    int windowH = window.getSize().y;
    int sep = 100;
    int countG = 1;

    users = GestionUser::getInstance()->getUsers();

    for(User* user : users){
        vector<int> scores = user->getScores();
        stringstream st;
        for(int i=0; i<scores.size();i++){
            if(i>4){
                st<<"";
            } else {
                st<<scores[i]<<", ";
            }
        }
        string score = st.str();
        text = new TextField(Vector2f(650, 140+sep),TextureTXT,score);
        listScores.push_back(text);
        sep = sep+50;
    }
}
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void GameStateAdmin::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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

GameStateAdmin::GameStateAdmin(const GameStateAdmin& other)
{
    //copy ctor
}
/**
*   Function to delete a user from instance of GestionUser
*   If a textfield is selected and the delete button is clicked -> we remove user selected from instance (GestionUser) and from the texfield of this user.
*   @param window : a RenderWindow object
*/
void GameStateAdmin::Delete(RenderWindow& window){
    if(btnDelete.isClicked(window) && getPositionSelected() != -1){
        int pos = getPositionSelected();
        //cout<<pos;
        User* tmp = *(users.begin()+pos);
        User& u = *tmp;
        GestionUser::getInstance()->removeUser(u);
        listName.erase(listName.begin()+pos);
        listScores.erase(listScores.begin()+pos);
        free(tmp);
        GestionUser::getInstance()->writeFromFile("User.txt");
        return;

    }
}
/**
*   Function who permet to know wich textfield is selected (to delete)
*   For all textfield in listName -> call of "isClicked()" from TextField
*   If is clicked -> modif texture of textfield and "setPositionSelected()" to know wich one is selected in the listName
*   Condition to know if he changes of textfield selected -> setTexture()
*   @param window : a RenderWindow object
*/
void GameStateAdmin::getTextFieldSelected(RenderWindow& window){
    Texture textClicked;
    for(int i = 0; i<listName.size(); i++){
        if(listName[i]->isClicked(window)){
            setPositionSelected(i);
            textClicked.loadFromFile("inputText2.png");
            listName[i]->setTexture(textClicked);
            listScores[i]->setTexture(textClicked);

        }
        if (i != getPositionSelected()) {
            textClicked.loadFromFile("inputText.png");
            listName[i]->setTexture(textClicked);
            listScores[i]->setTexture(textClicked);
        }
    }
}
/**
*   Function who permet to create buttons of interface
*   initialisation of different buttons (position, texture, font)-> call in constructor
*   @param font : an object Font (represent the font of text into button)
*   @param tex : an object Texture (represent the texture of button)
*   @param window : a RenderWindow object (represent the window)
*/
void GameStateAdmin::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    btnDelete = Button(texture,font,"Delete");

    //btnDelete.setPosition(Vector2f((windowW-windowW/3),windowH/1.3));
    btnDelete.setPosition(Vector2f(800,550));
    btnDelete.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnDelete.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnDelete.getText().setPosition(22,22);

    btnBack = Button(texture,font,"Back");

    //btnBack.setPosition(Vector2f(windowW/14,windowH/1.3));
    btnBack.setPosition(Vector2f(150,550));
    btnBack.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnBack.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnBack.getText().setPosition(22,22);
}
/**
*   Function who permet to return attibut positionSelected;
*/
int GameStateAdmin::getPositionSelected(){
    return positionSelected;
}
/**
*   Function who permet to modif attibut positionSelected;
*   @param newPosition : integer
*/
void GameStateAdmin::setPositionSelected(int newPosition){
    this->positionSelected = newPosition;
}

GameStateAdmin& GameStateAdmin::operator=(const GameStateAdmin& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
/**
*   Function who permet to add component in window
*   call of draw methods (SFML class)
*   For all users, draw on listNames (all logins) and listScores(all scores)
*   @param window : a RenderWindow object
*/
void GameStateAdmin::draw(const float dt){
    this->game->window.draw(background);
    this->game->window.draw(title);
    for(int i=0;i<listName.size();i++){
        listName[i]->draw(this->game->window);
        listScores[i]->draw(this->game->window);
    }
    btnDelete.draw(this->game->window);
    btnBack.draw(this->game->window);
}
void GameStateAdmin::update(const float dt){
    if(btnBack.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
    }
}

void GameStateAdmin::handleInput(){
    Event event;
    while (this->game->window.pollEvent(event))
    {
        getTextFieldSelected(this->game->window);
        Delete(this->game->window);
        if (event.type == Event::Closed)
            this->game->window.close();

    }
    draw(0.0);
}

void GameStateAdmin::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}
