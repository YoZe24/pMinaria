#include "view/Animation.h"

using namespace sf;
using namespace std;

Animation::Animation()
{
    currentFrame = 0;
    playing = true;
    flip = false;
    loop = true;
}

Animation::Animation(float speed,bool loop,sf::Sprite sprite)
{
    currentFrame = 0;
    playing = true;
    flip = false;

    this->speed = speed;
    this->loop = loop;
    this->sprite = sprite;
}

Animation::~Animation()
{
    //dtor
//    if(rand()%10000 == 1)cout<<"delete";
}

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

void Animation::addFrames(IntRect ir){
    this->frames.push_back(ir);
}

void Animation::addFramesFlip(IntRect ir){
    this->frames_flip.push_back(ir);
}

std::string Animation::str() const{
    std::stringstream sstr;
    for(int i = 0 ; i<this->frames.size() ; i++){
        sstr << "Top : " << this->frames[i].top << ", left : "<<this->frames[i].left << " w : "<<this->frames[i].width << " h : " << this->frames[i].height << "\n";
    }
    return sstr.str();
}
