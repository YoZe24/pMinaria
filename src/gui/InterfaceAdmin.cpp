#include "gui/InterfaceAdmin.h"

InterfaceAdmin::InterfaceAdmin(Texture& title,Texture& textureBG,Texture& textureBTN, Texture& TextureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    initListName(window, TextureTXT);
    createButton(font,textureBTN,window);
    initListScores(window, TextureTXT);
}

void InterfaceAdmin::initListName(RenderWindow& window, Texture& TextureTXT){
    int windowW = window.getSize().x;
    int windowH = window.getSize().y;
    int sep = 100;
    int countG = 1;

    users = GestionUser::getInstance()->getUsers();

    for(User* user : users){
        string name = user->getLogin();
        text = new TextField(Vector2f(windowW/6, (windowH/5)+sep),TextureTXT,name);
        listName.push_back(text);
        sep = sep+50;
    }
}

void InterfaceAdmin::initListScores(RenderWindow& window, Texture& TextureTXT){
    int windowW = window.getSize().x;
    int windowH = window.getSize().y;
    int sep = 100;
    int countG = 1;

    users = GestionUser::getInstance()->getUsers();

    for(User* user : users){
        vector<int> scores = user->getScores();
        stringstream st;
        for(int i=0; i<scores.size();i++){
            st<<scores[i]<<", ";
        }
        string score = st.str();
        text = new TextField(Vector2f((windowW/6)+400, (windowH/5)+sep),TextureTXT,score);
        listScores.push_back(text);
        sep = sep+50;
    }
}

InterfaceAdmin::~InterfaceAdmin()
{
    for(int i=0;i<listName.size();i++){
        delete listName[i];
        delete listScores[i];
    }
}

InterfaceAdmin::InterfaceAdmin(const InterfaceAdmin& other)
{
    //copy ctor
}

InterfaceAdmin& InterfaceAdmin::operator=(const InterfaceAdmin& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void InterfaceAdmin::initBackGround(Texture& title,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = texture.getSize();

    this->title.setTexture(title);
    background.setTexture(texture);
    background.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    this->title.setPosition((float) (windowSize.x - windowSize.x/2) - title.getSize().x/2,0);
}
void InterfaceAdmin::Delete(RenderWindow& window){
    if(btnDelete.isClicked(window) && getPositionSelected() != -1){
        int pos = getPositionSelected();
        User* tmp = *(users.begin()+pos);
        User& u = *tmp;
        GestionUser::getInstance()->removeUser(u);
        listName.erase(listName.begin()+pos);
        listScores.erase(listScores.begin()+pos);
        delete tmp;

        return;

    }
}

void InterfaceAdmin::getTextFieldSelected(RenderWindow& window){
    Texture textClicked;
    for(int i = 0; i<listName.size(); i++){
        if(listName[i]->isClicked(window)){
            setPositionSelected(i);
            textClicked.loadFromFile("inputText2.png");
            listName[i]->setTexture(textClicked);
            listScores[i]->setTexture(textClicked);
        }
        if (i != getPositionSelected()) {
            cout<<1;
            textClicked.loadFromFile("inputText.png");
            listName[i]->setTexture(textClicked);
            listScores[i]->setTexture(textClicked);
        }
    }
}


void InterfaceAdmin::createButton(Font& font,Texture& tex,RenderWindow& window)
{
    Texture& texture = tex;
    int buttonW = texture.getSize().x;
    int buttonH = texture.getSize().y;

    int windowW = window.getSize().x;
    int windowH = window.getSize().y;

    btnDelete = Button(texture,font,"Delete");

    btnDelete.setPosition(Vector2f((windowW-windowW/3),windowH/1.3));
    btnDelete.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnDelete.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnDelete.getText().setPosition(22,22);

    btnBack = Button(texture,font,"Back");

    btnBack.setPosition(Vector2f(windowW/14,windowH/1.3));
    btnBack.addSpriteFullSize(IntRect(0,0,buttonW,buttonH/2),NORMAL);
    btnBack.addSpriteFullSize(IntRect(0,buttonH/2,buttonW,buttonH/2),PRESSED);
    btnBack.getText().setPosition(22,22);
}
int InterfaceAdmin::getPositionSelected(){
    return positionSelected;
}
void InterfaceAdmin::setPositionSelected(int newPosition){
    this->positionSelected = newPosition;
}

void InterfaceAdmin::draw(RenderWindow& window)
{
    window.draw(background);
    window.draw(title);
    int i = 0;
    for(User* user : users){
        listName[i]->draw(window);
        listScores[i]->draw(window);
        i++;
    }
    btnDelete.draw(window);
    btnBack.draw(window);
}
