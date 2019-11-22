#include "gui/InterfaceConAdmin.h"

#include "gui/TextField.h"
#include "model/GestionUser.h"

#define MDP "123"

InterfaceConAdmin::InterfaceConAdmin(Texture& title,Texture& textureBG,Texture& textureBTN,Texture& textureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
    textMdp = new TextField(Vector2f(200,350),textureTXT,"Mot de passe :");
    inputMdp = new TextField(Vector2f(600,350),textureTXT," 'Ecrivez' ");

}

void InterfaceConAdmin::InputTextRecup(RenderWindow& window, sf::Event event){
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

InterfaceConAdmin::~InterfaceConAdmin()
{
    delete textMdp;
    delete inputMdp;
}

InterfaceConAdmin::InterfaceConAdmin(const InterfaceConAdmin& other)
{
    //copy ctor
}

InterfaceConAdmin& InterfaceConAdmin::operator=(const InterfaceConAdmin& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void InterfaceConAdmin::Confirm(RenderWindow& window){
    if(btnConfirm.isClicked(window)){
        sf::Text mdpText = inputMdp->getText();
        string mdpString = mdpText.getString();
        if(mdpString.compare(MDP)==0){
            cout<<"ACCES VALIDE";
        }else {
            cout<<"ACCES INVALIDE";
        }

    }
}

void InterfaceConAdmin::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = texture.getSize();

    this->title.setTexture(title);
    background.setTexture(texture);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
}

void InterfaceConAdmin::createButton(Font& font,Texture& tex,RenderWindow& window)
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

void InterfaceConAdmin::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    textMdp->draw(window);
    inputMdp->draw(window);
    btnConfirm.draw(window);
    btnBack.draw(window);


}
