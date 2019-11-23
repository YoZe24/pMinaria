#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "view/Animation.h"


class AnimationManager
{
    public:
        AnimationManager();
        virtual ~AnimationManager();
        AnimationManager(const AnimationManager& other);

        void create(std::string name, sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool loop = true);

        /**
        *
        *   Set the value of flip
        *
        *   @param name : Texture's name to set if it can be flipped or not
        */
        void set(std::string name)
        {
            currentAnim = name;
            animList[currentAnim].setFlip(0);
        }
        std::string getCurrentAnim() const{
            return currentAnim;
        }


        /**
        *
        *   Draw the animations
        *
        *   @param window : Game's window to draw our animation
        *   @param x : Animation's position x on screen
        *   @param y : Animation's position y on screen
        */
        void draw(sf::RenderWindow &window,int x=0, int y=0)
        {
            animList[currentAnim].getSprite().setPosition(x,y);
            window.draw( animList[currentAnim].getSprite() );
        }


        /**
        *
        *   Flip function for textures
        *
        *   This function allows us to flip a texture and to don't have too much texture only for one animation
        *
        *   @param b : Value to flip or not
        */
        void flip(bool b=1) {animList[currentAnim].setFlip(b);}

        /**
        *
        *   Tick time
        *
        *   Set the time for the animation
        *
        *   @param time : Value to set the animation
        */
        void tick(float time)	 {animList[currentAnim].tick(time);}

        /**
        *
        *   Pause function for the animation
        *
        *   Set the pause for the animation
        *
        */
        void pause() {animList[currentAnim].setPlaying(false);}

        /**
        *
        *   Play function for the animation
        *
        *   Play the animation
        *
        */
        void play()  {animList[currentAnim].setPlaying(true);}

        /**
        *
        *   Check function animation
        *
        *   Check if the animation is playing or not
        *
        *   @return value : Value if the animation is playing or not
        */
        bool isPlaying()  {return animList[currentAnim].isPlaying();}

        float getH()  {return animList[currentAnim].getFramesHeight();}

        float getW() {return animList[currentAnim].getFramesWidth();}

        std::map<std::string,Animation>& getAnimList(){return animList;}
    protected:

    private:
        std::string currentAnim;
        std::map<std::string,Animation> animList;
};

#endif // ANIMATIONMANAGER_H
