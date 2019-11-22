#include "gui/InterfaceCon.h"

#include "gui/TextField.h"
#include "model/GestionUser.h"


InterfaceCon::InterfaceCon(Texture& title,Texture& textureBG,Texture& textureBTN,Texture& textureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
    textLogin = new TextField(Vector2f(200,350),textureTXT,"Nom Utilisateur :");
    inputLogin = new TextField(Vector2f(600,350),textureTXT," 'Ecrivez' ");

}

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

InterfaceCon::~InterfaceCon()
{
    delete textLogin;
    delete inputLogin;
}

InterfaceCon::InterfaceCon(const InterfaceCon& other)
{
    //copy ctor
}

InterfaceCon& InterfaceCon::operator=(const InterfaceCon& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void InterfaceCon::Confirm(RenderWindow& window){
    if(btnConfirm.isClicked(window)){
        sf::Text nameText = inputLogin->getText();
        sf::String nameString = nameText.getString();
        vector<int> scores;
        User* user = new User(nameString,EnumStatus::user,scores);
        GestionUser::getInstance()->addUser(user);
        cout<<GestionUser::getInstance()->str()<<endl;

    }
}

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

void InterfaceCon::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    textLogin->draw(window);
    inputLogin->draw(window);
    btnConfirm.draw(window);
    btnBack.draw(window);


}

