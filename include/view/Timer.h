#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <string>
class Timer
{
    public:
        Timer(float timeEnd);
        virtual ~Timer();
        Timer(const Timer& other);

        void setTimeout(std::function<void(void)> f,int delay);
        void draw(sf::RenderWindow& window);
        void update(int playerScore);
        void stop(){clear = true;}
        void run();
        void reset();
        std::string getStringTimeLeft();
    protected:

    private:
        std::function<void(void)> endFunction;
        std::thread thTimer;
        bool clear = false;
        float time,timeEnd,sizeX;
        int delay,score;
        const float interval = 1.0;
        sf::RectangleShape timerBar,timerBorder;
        sf::Text timerText,scoreText;
        sf::Font font;
};

#endif // TIMER_H
