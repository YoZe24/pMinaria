#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class Animation
{
    public:
        Animation();
        Animation(float speed,bool loop,sf::Sprite sprite);
        virtual ~Animation();
        Animation(const Animation& other);
        Animation& operator=(const Animation& other);

        std::string str() const;

        void tick(float time);

        std::vector<sf::IntRect>& getFrames() {return frames;}
        std::vector<sf::IntRect>& getFrames_flip() {return frames_flip;}
        int getFramesHeight() const{return frames[0].height;}
        int getFramesWidth() const{return frames[0].width;}

        float getCurrentFrame() const{return currentFrame;}
        float getSpeed() const{return speed;}
        sf::Sprite& getSprite(){return sprite;}
        bool isPlaying()const{return playing;}

        void setPlaying(bool b){playing = b;}
        void setFlip(bool b){flip = b;}
        void setCurrentFrame(float cf){currentFrame = cf;}
        void setSpeed(float s){speed = s;}

        void addFrames(sf::IntRect ir);
        void addFramesFlip(sf::IntRect ir);
    protected:

    private:
        //Frames for animation left to right and right to left (flip)
        std::vector<sf::IntRect> frames,frames_flip;
        float currentFrame, speed;
        //Loop = false when animation is played one time
        bool loop,flip,playing;
        sf::Sprite sprite;
};

#endif // ANIMATION_H
