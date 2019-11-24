#include "OresBar.h"

using namespace std;
using namespace sf;

const Color oreColor(40, 180, 99);
const int heightBar = 20;

OresBar::OresBar()
{
    sizeX = 200;

    if(!textureBlock.loadFromFile("blocks_sheet.png")){}
    if(!font.loadFromFile("arial.ttf")){}

    spriteBlock.setTexture(textureBlock);
    spriteBlock.setTextureRect(IntRect(0,64,32,32));

    oreText.setFont(font);

    oreText.setCharacterSize(20);
    oreText.setColor(Color::White);

    oreBar.setFillColor(oreColor);
    oreBorder.setFillColor(Color::Transparent);
    oreBorder.setSize(Vector2f(sizeX,heightBar));
    oreBorder.setOutlineThickness(2);
    oreBorder.setOutlineColor(Color::Black);

    spriteBorder.setSize(Vector2f(32,32));
    spriteBorder.setFillColor(Color::Transparent);
    spriteBorder.setOutlineThickness(3);
    spriteBorder.setOutlineColor(Color::Black);
}

OresBar::~OresBar()
{
    //dtor
}

OresBar::OresBar(const OresBar& other)
{
    //copy ctor
}

void OresBar::draw(RenderWindow& window){
    Vector2f size = window.getView().getSize();
    Vector2f center = window.getView().getCenter();

    int x = center.x + size.x/2 - sizeX - 10;
    int y = center.y - size.y/2 + 10;

    oreBar.setPosition(Vector2f(  x,  y));
    oreBorder.setPosition(Vector2f(  x,  y));
    oreText.setPosition(Vector2f(x + sizeX/2 - oreText.getGlobalBounds().width/2 , y - 2));
    spriteBlock.setPosition(x - spriteBlock.getGlobalBounds().width - 7, y - 6 );
    spriteBorder.setPosition(spriteBlock.getPosition());

    window.draw(oreBorder);
    window.draw(oreBar);
    window.draw(oreText);
    window.draw(spriteBlock);
    window.draw(spriteBorder);
}

void OresBar::update(int nbOresCraft,int nbOres,int currentPickaxe){
    this->currentPickaxe = currentPickaxe;
    spriteBlock.setTextureRect(IntRect(0,64 + 32 * currentPickaxe,32,32));

    oreText.setString(to_string(nbOres)+ "/" + to_string(nbOresCraft));
    oreBar.setSize(Vector2f(nbOres * sizeX/nbOresCraft,heightBar));
}
