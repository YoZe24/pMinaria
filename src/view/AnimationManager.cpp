#include "view/AnimationManager.h"
using namespace sf;

AnimationManager::AnimationManager()
{
    //ctor
}

AnimationManager::~AnimationManager()
{
    //dtor
}

AnimationManager::AnimationManager(const AnimationManager& other):currentAnim(other.currentAnim),animList(other.animList)
{
}

void AnimationManager::create(std::string name, sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step , bool loop ){
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(0,h);
    Animation a(speed,loop,sprite);

    for(int i = 0; i < count ; i++){
        a.addFrames(sf::IntRect(x+i*step,y,w,h));
        a.addFramesFlip(sf::IntRect(x+i*step+w,y,-w,h));
    }

    this->animList[name] = a;
    this->currentAnim = name;
}
