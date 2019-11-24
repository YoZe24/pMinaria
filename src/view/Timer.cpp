#include "view/Timer.h"
#include <sstream>
using namespace std;
using namespace sf;

const Color barColor(43,87,151);
const Color endBarColor = Color::Red;
const int heightBar = 20;

Timer::Timer(float timeEnd):timeEnd(timeEnd)
{
    time = 0;
    sizeX = 400;
    score = 0;

    if(font.loadFromFile("arial.ttf")){}

    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setColor(Color::White);

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setColor(Color::Black);

    timerBar.setFillColor(barColor);
    timerBorder.setFillColor(Color::Transparent);
    timerBorder.setSize(Vector2f(sizeX,heightBar));
    timerBorder.setOutlineThickness(2);
    timerBorder.setOutlineColor(Color::Black);
}

Timer::~Timer()
{
    //dtor
}

Timer::Timer(const Timer& other):time(other.time),timerBar(other.timerBar),timerBorder(other.timerBorder),
timerText(other.timerText),timeEnd(other.timeEnd)
{
    //copy ctor
}

string Timer::getStringTimeLeft(){
    stringstream timeStr;
    int minute = (timeEnd-time) / 60;
    int second = (int)(timeEnd-time) % 60;
    if(minute < 10) timeStr << "0";
    timeStr << to_string(minute) << ":";
    if(second < 10) timeStr << "0";
    timeStr << to_string(second);
    return timeStr.str();
}

void Timer::update(int score){
    timerBar.setSize(Vector2f( (timeEnd-time) * sizeX/timeEnd,heightBar));
    timerText.setString(getStringTimeLeft());
    if(this->score < score)this->score = score;
    scoreText.setString("Score : " + to_string(this->score));
}

void Timer::draw(RenderWindow& window){
    Vector2f size = window.getView().getSize();
    Vector2f center = window.getView().getCenter();

    timerBar.setPosition(Vector2f(  center.x - sizeX/2  ,  center.y - size.y/2 + 10 ));
    timerBorder.setPosition(Vector2f(  center.x - sizeX/2  ,  center.y - size.y/2 + 10 ));
    timerText.setPosition(Vector2f(center.x - timerText.getGlobalBounds().width/2, center.y - size.y/2 + 8 ));
    scoreText.setPosition(center.x - size.x/2, center.y - size.y/2 + 3 );

    window.draw(scoreText);
    window.draw(timerBorder);
    window.draw(timerBar);
    window.draw(timerText);
}

void Timer::run(){
    this->clear = false;
    std::thread t([=](){
        while(time <= timeEnd){
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(this->clear) return;
            time += 0.1;
            if(timeEnd - time < timeEnd / 5){
                timerBar.setFillColor((int)(time*10) % 3 == 0 ? endBarColor : Color::Transparent);
            }
        }
    });
    t.detach();
}

void Timer::setTimeout(std::function<void(void)> f, int delay) {
    this->clear = false;
    endFunction = f;
    this->delay = delay;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        endFunction();
    });
    t.detach();

}

void Timer::reset(){
    clear = true;
    time = 0.;
    timerBar.setFillColor(barColor);
    setTimeout(endFunction,delay);
    run();
}
