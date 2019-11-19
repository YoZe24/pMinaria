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

        void set(std::string name)
        {
            currentAnim = name;
            animList[currentAnim].setFlip(0);
        }
        std::string getCurrentAnim() const{
            return currentAnim;
        }

        void draw(sf::RenderWindow &window,int x=0, int y=0)
        {
            animList[currentAnim].getSprite().setPosition(x,y);
            window.draw( animList[currentAnim].getSprite() );
        }

        void flip(bool b=1) {animList[currentAnim].setFlip(b);}

        void tick(float time)	 {animList[currentAnim].tick(time);}

        void pause() {animList[currentAnim].setPlaying(false);}

        void play()  {animList[currentAnim].setPlaying(true);}

//        void play(std::string name)  {animList[name].isPlaying=true;}

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
