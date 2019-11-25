#include "GameStateTableScore.h"
#include <algorithm>
#include "model/GestionUser.h"
#include "gamestate/GameStateMainMenu.h"

using namespace sf;
using namespace std;

/**
*   Main constructor
*
*   We used 2 functions to create and initialize our table score interface(avoid big code in the constructor).
*   We used one function init the "table" -> 2 vector (all login/ all best score)
*/
GameStateTableScore::GameStateTableScore(Game* game)
{
    this->game = game;
    loadTextures();
    initBackGround(textureTitle,textureBG,this->game->window);
    createButton(font,textureBTN,this->game->window);
    initListScores(this->game->window, textureTXT);
    View viewChange(sf::FloatRect(0,0,screen_w,screen_h));
    this->game->window.setView(viewChange);
}
/**
*   Destructor
*   Destruction of 2 textfields created in constructor (pointer agregation)
*/
GameStateTableScore::~GameStateTableScore()
{
    for(int i=0;i<listName.size();i++){
        delete listName[i];
        delete listScores[i];
    }
}
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void GameStateTableScore::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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
void GameStateTableScore::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    btnBack = Button(texture,font,"Back");

    btnBack.setPosition(Vector2f(windowW/14,windowH/1.3));
    btnBack.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnBack.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnBack.getText().setPosition(22,22);
}

GameStateTableScore::GameStateTableScore(const GameStateTableScore& other)
{
    //copy ctor
}

GameStateTableScore& GameStateTableScore::operator=(const GameStateTableScore& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
/**
*   Function to initialize 2 texfield's vectors, listName -> all logins/ listScores -> all best score of each user
*   For all users, we recup all these scores from instance (GestionUser) and we create a texfield with the value. Call Textfield constructor

*   For all user, we recup  his names and the best score of his scores.
*   After, we do a sort by descending order
*   Finally, we create all textfields for login and score -> 2 vector of textfields
*
*   @param window : a RenderWindow object (Reference)
*   @param TextureTXT : Texture textfield
*/
void GameStateTableScore::initListScores(RenderWindow& window, Texture& TextureTXT){
    int windowW = this->game->window.getSize().x;
    int windowH = this->game->window.getSize().y;
    int sep = 100;
    vector<int>maximum;
    vector<string>names;
    int tmpInt;
    string tmpString;
    users = GestionUser::getInstance()->getUsers();
    for(int i = 0; i<users.size();i++){
        vector<int> scoresI = users[i]->getScores();
        if(scoresI.size()==0){
            maximum.push_back(0);
        }else{
            int maxUser = *max_element(begin(scoresI),end(scoresI));
            maximum.push_back(maxUser);
        }
        string name = users[i]->getLogin();
        names.push_back(name);
    }
    for(int i = 0; i < maximum.size() - 1; i++ ){
		for(int j = (i+1); j < maximum.size(); j++ ){
			if( maximum[i] < maximum[j] ){
				tmpInt=maximum[i];
				maximum[i]=maximum[j];
				maximum[j]=tmpInt;
				tmpString=names[i];
				names[i]=names[j];
				names[j]=tmpString;
			}
		}
	}
	for(int i= 0;i<maximum.size();i++){
        stringstream st;
        st<<maximum[i];
        string score = st.str();
        text = new TextField(Vector2f((windowW/6)+400, (windowH/5)+sep),TextureTXT,score);
        listScores.push_back(text);
        string name = names[i];
        text = new TextField(Vector2f(windowW/6, (windowH/5)+sep),TextureTXT,name);
        listName.push_back(text);
        sep = sep+50;

	}
}
void GameStateTableScore::draw(const float dt){
    this->game->window.draw(background);
    this->game->window.draw(title);
    for(int i =0; i<listName.size(); i++){
        listName[i]->draw(this->game->window);
        listScores[i]->draw(this->game->window);
        if(i == 10){
            return;
        }
    }
    btnBack.draw(this->game->window);
}
void GameStateTableScore::update(const float dt){
    if(btnBack.isClicked(this->game->window))
    {
        this->game->pushState(new GameStateMainMenu(this->game));
    }
}
void GameStateTableScore::handleInput(){
    Event event;
    while (this->game->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            this->game->window.close();

    }
    draw(0.0);
}

void GameStateTableScore::loadTextures(){
    textureBTN.loadFromFile("btnSkin.png");
    textureBG.loadFromFile("background.png");
    textureTXT.loadFromFile("inputText.png");
    font.loadFromFile("gameFont.ttf");
    textureTitle.loadFromFile("title.png");
}

