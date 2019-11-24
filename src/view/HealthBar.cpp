#include "view/HealthBar.h"

using namespace sf;
using namespace std;

HealthBar::HealthBar()
{
    texture.loadFromFile("healthbar2.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(5,22,110,29));
    bar.setFillColor(Color(0,0,0));
    max = 100;
}

HealthBar::~HealthBar()
{
    //dtor
}

HealthBar::HealthBar(const HealthBar& other)
{
    //copy ctor
}

void HealthBar::update(int k){
    if(k>0 && k <= max)
        bar.setSize(Vector2f((max-k)*102 / max,20));
}

void HealthBar::draw(RenderWindow& window){
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    sprite.setPosition(   center.x - size.x/2 + 10 + 170 , center.y - size.y/2 + 10);
    bar.setPosition( center.x - size.x/2 + 14 + 170, center.y - size.y/2 + 15);

    window.draw(sprite);
    window.draw(bar);
}
