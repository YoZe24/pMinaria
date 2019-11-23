#include "gui/InterfaceTableScore.h"
#include <algorithm>

/**
*   Main constructor
*
*   We used 2 functions to create and initialize our table score interface(avoid big code in the constructor).
*   We used one function init the "table" -> 2 vector (all login/ all best score)
*
*   @param title : Title's sprite
*   @param textureBG : Background's texture
*   @param textureBTN : Buttons' texture
*   @param textureTXT : Textfield' texture
*   @param font : Buttons' font
*   @param window : Game's window to send to our initializing functions
*
*/
InterfaceTableScore::InterfaceTableScore(Texture& title,Texture& textureBG,Texture& textureBTN, Texture& TextureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
    initListScores(window, TextureTXT);
}
/**
*   Default Constructor
*/
InterfaceTableScore::InterfaceTableScore(){}

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
void InterfaceTableScore::initListScores(RenderWindow& window, Texture& TextureTXT){
    int windowW = window.getSize().x;
    int windowH = window.getSize().y;
    int sep = 100;
    vector<int>maximum;
    vector<string>names;
    int tmpInt;
    string tmpString;
    users = GestionUser::getInstance()->getUsers();
    for(int i = 0; i<users.size();i++){
        vector<int> scoresI = users[i]->getScores();
        int maxUser = *max_element(begin(scoresI),end(scoresI));
        maximum.push_back(maxUser);
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
/**
*   Destructor
*   Destruction of 2 textfields created in constructor (pointer agregation)
*/
InterfaceTableScore::~InterfaceTableScore()
{
    for(int i=0;i<listName.size();i++){
        delete listName[i];
        delete listScores[i];
    }
}
/**
*   Copy Constructor
*   Recup all attributes from other
*   @param other : Reference constant of InterfaceTableScore object
*
*/
InterfaceTableScore::InterfaceTableScore(const InterfaceTableScore& other)
{
    this->title = other.title;
    this->background = other.background;
    this->btnBack = other.btnBack;
    this->listName = other.listName;
    this->listScores = other.listScores;
}
/**
*   Operator= overloading
*   Recup all attributes
*   @param other : Reference constant of InterfaceTableScore object
*
*/
InterfaceTableScore& InterfaceTableScore::operator=(const InterfaceTableScore& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->title = rhs.title;
    this->background = rhs.background;
    this->btnBack = rhs.btnBack;
    this->listName = rhs.listName;
    this->listScores = rhs.listScores;
    return *this;
}
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void InterfaceTableScore::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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
void InterfaceTableScore::createButton(Font& font,Texture& tex,RenderWindow& window)
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
/**
*   Function who permet to add component in window
*   call of draw methods (SFML class)
*   For all user -> draw() of listNames (Textfield) and listScores(Textfield) --> Only the first 10
*   @param window : a RenderWindow object
*/
void InterfaceTableScore::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    int i = 0;
    for(User* user : users){
        listName[i]->draw(window);
        listScores[i]->draw(window);
        i++;
        if(i == 10){
            return;
        }
    }
    btnBack.draw(window);
}
