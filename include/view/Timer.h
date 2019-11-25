#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <functional>
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
        bool clear = false;
        float timeElapsed,timeEnd,sizeX;
        int score;
        const float interval = 1.0;
        sf::RectangleShape timerBar,timerBorder;
        sf::Text timerText,scoreText;
        sf::Font font;
};

#endif // TIMER_H
