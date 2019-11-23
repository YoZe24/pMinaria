#include "view/AnimationManager.h"
using namespace sf;

/**
*
*   Default constructor
*/
AnimationManager::AnimationManager()
{
    //ctor
}

/**
*
*   Destructor
*
*/
AnimationManager::~AnimationManager()
{
    //dtor
}

/**
*
*   Copy constructor
*/
AnimationManager::AnimationManager(const AnimationManager& other):currentAnim(other.currentAnim),animList(other.animList)
{
}

/**
*
*   Creating function for the Manager
*
*   We load animation into a map.
*   We use the Animation constructor to set the animation to fit the map.
*   The map contains all animation we need to load the game, we just know the name to get the animation wanted (with the key).
*
*   @param texture : Texture's ref to set the sprite of the animation
*   @param x : Position x to set the Rect area position
*   @param y : Position y to set the Rect area position
*   @param w : Width of the texture loaded
*   @param h : Height of the texture loaded
*   @param speed : The speed to set the animation
*   @param step : The pixels between 2 texture of the sprite
*   @param loop : Value if the texture has animation or not
*/
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
