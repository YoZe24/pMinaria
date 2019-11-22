#include "gui/InterfaceTableScore.h"
#include <algorithm>

InterfaceTableScore::InterfaceTableScore(Texture& title,Texture& textureBG,Texture& textureBTN, Texture& TextureTXT,Font& font,RenderWindow& window)
{
    initBackGround(title,textureBG,window);
    createButton(font,textureBTN,window);
    initListScores(window, TextureTXT);
}

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

InterfaceTableScore::~InterfaceTableScore()
{
    for(int i=0;i<listName.size();i++){
        delete listName[i];
        delete listScores[i];
    }
}

InterfaceTableScore::InterfaceTableScore(const InterfaceTableScore& other)
{
    //copy ctor
}

InterfaceTableScore& InterfaceTableScore::operator=(const InterfaceTableScore& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

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
