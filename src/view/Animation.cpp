#include "view/Animation.h"

using namespace sf;
using namespace std;

/**
*
*     Default constructor
*
*     We set all default values
*/
Animation::Animation()
{
    currentFrame = 0;
    playing = true;
    flip = false;
    loop = true;
}

/**
*
*   Main constructor
*
*   @param speed : The speed to set the animation
*   @param step : The pixels between 2 texture of the sprite
*   @param loop : Value if the texture has animation or not
*/
Animation::Animation(float speed,bool loop,sf::Sprite sprite)
{
    currentFrame = 0;
    playing = true;
    flip = false;

    this->speed = speed;
    this->loop = loop;
    this->sprite = sprite;
}

/**
*   Destructor
*/
Animation::~Animation()
{
    //dtor
//    if(rand()%10000 == 1)cout<<"delete";
}

/**
*   Copy constructor
*/
Animation::Animation(const Animation& other)
{
    this->currentFrame = other.currentFrame;
    this->playing = other.playing;
    this->flip = other.flip;
    this->speed = other.speed;
    this->loop = other.loop;
    this->sprite = other.sprite;
    this->frames = other.frames;
    this->frames_flip = other.frames_flip;
}

/**
*   Operator= to compare 2 animations
*/
Animation& Animation::operator=(const Animation& other){
    if(this != &other){
        this->currentFrame = other.currentFrame;
        this->playing = other.playing;
        this->flip = other.flip;
        this->speed = other.speed;
        this->loop = other.loop;
        this->sprite = other.sprite;
        this->frames = other.frames;
        this->frames_flip = other.frames_flip;
    }
    return *this;
}

/**
*
*   Set the right frame from the animation
*
*   @param time : Value to change between 2 frame of the animation
*/
void Animation::tick(float time){
    if(!playing) return;

    currentFrame += speed * time;

    if(currentFrame > frames.size()){
        currentFrame -= frames.size();
        if(!loop){
            playing = false;
            return;
        }
    }
    sprite.setTextureRect(frames[currentFrame]);
    if(flip)
        sprite.setTextureRect(frames_flip[currentFrame]);
}

/**
*
*   Add frame from the sprite
*
*   We cut the sprite sheet into Rect and we have one frame.
*   We can build an animation with this function.
*
*   @param ir : Frame's rectangle to set the sprite for the animation
*/
void Animation::addFrames(IntRect ir){
    this->frames.push_back(ir);
}

/**
*
*   Add frame from the sprite
*
*   We cut the sprite sheet into Rect and we have one frame.
*   We can build an animation with this function.
*   It contains flipped frames.
*
*   @param ir : Frame's rectangle to set the sprite for the animation
*/
void Animation::addFramesFlip(IntRect ir){
    this->frames_flip.push_back(ir);
}

/**
*
*   String function to check our frames
*
*   Only used for checking
*
*/
std::string Animation::str() const{
    std::stringstream sstr;
    for(int i = 0 ; i<this->frames.size() ; i++){
        sstr << "Top : " << this->frames[i].top << ", left : "<<this->frames[i].left << " w : "<<this->frames[i].width << " h : " << this->frames[i].height << "\n";
    }
    return sstr.str();
}
