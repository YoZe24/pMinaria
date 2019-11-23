#include "gui/InterfaceCon.h"

#include "gui/TextField.h"
#include "model/GestionUser.h"

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
InterfaceCon::InterfaceCon(Texture& title,Texture& textureBG,Texture& textureBTN,Texture& textureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
    textLogin = new TextField(Vector2f(200,350),textureTXT,"Nom Utilisateur :");
    inputLogin = new TextField(Vector2f(600,350),textureTXT," 'Ecrivez' ");

}
/**
*   Default constructor
*/
InterfaceCon::InterfaceCon(){}
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
void InterfaceCon::InputTextRecup(RenderWindow& window, sf::Event event){
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
*   Destructor
*   Destruction of 2 textfields created in constructor (pointer agregation)
*/
InterfaceCon::~InterfaceCon()
{
    delete textLogin;
    delete inputLogin;
}

/**
*   Copy Constructor
*   Recup all attributes
*   @param other : Reference constant of InterfaceCon object
*
*/
InterfaceCon::InterfaceCon(const InterfaceCon& other)
{
    this->title = other.title;
    this->btnBack = other.btnBack;
    this->btnConfirm = other.btnConfirm;
    this->background = other.background;
    this->textLogin = other.textLogin;
    this->inputLogin = other.inputLogin;
}
/**
*   Operator= overloading
*   Recup all attributes from rhs if not equals of current object
*   @param other : Reference constant of InterfaceCon object
*
*/
InterfaceCon& InterfaceCon::operator=(const InterfaceCon& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->title = rhs.title;
    this->btnBack = rhs.btnBack;
    this->btnConfirm = rhs.btnConfirm;
    this->background = rhs.background;
    this->textLogin = rhs.textLogin;
    this->inputLogin = rhs.inputLogin;
    return *this;
}
/**
*   Function who permet creation of user (verficiation if exist -> addUser())
*   Recup text entered (login)
*   If not already in instance -> creation new user + add to instance of GestionUser
*   @param window : Reference of RenderWindow object
*
*/
void InterfaceCon::Confirm(RenderWindow& window){
    if(btnConfirm.isClicked(window)){
        sf::Text nameText = inputLogin->getText();
        sf::String nameString = nameText.getString();
        vector<int> scores;
        User* user = new User(nameString,scores);
        GestionUser::getInstance()->addUser(user);
        cout<<GestionUser::getInstance()->str()<<endl;

    }
}
/**
*   Function who permet to create background of window and title
*   initialisation of position (title) + texture' background
*   @param title : Texture' title
*   @param tex : Texture' background
*   @param window : a RenderWindow object
*/
void InterfaceCon::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
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
void InterfaceCon::createButton(Font& font,Texture& tex,RenderWindow& window)
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
/**
*   Function who permet to add component in window
*   call of draw method (SFML class)
*   @param window : a RenderWindow object
*/
void InterfaceCon::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    textLogin->draw(window);
    inputLogin->draw(window);
    btnConfirm.draw(window);
    btnBack.draw(window);


}

