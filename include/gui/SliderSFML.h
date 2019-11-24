#ifndef SLIDERSFML_H
#define SLIDERSFML_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class SliderSFML
{
    private:

        RectangleShape slider;
        RectangleShape axis;
        Font font;
        Text text;
        float minValue;
        float maxValue;
        int xCord;
        int yCord;
        int axisWidth;
        int axisHeight;
        int sliderWidth;
        int sliderHeight;
        float sliderValue;

    public:
        SliderSFML();
        SliderSFML(int x, int y);
        Text returnText(float x, float y, float z, int fontSize);
        void create(float min, float max);
        void logic(RenderWindow &window);
        float getSliderValue();
        void setSliderValue(float newValue);
        void draw(RenderWindow& window);
};
#endif // SLIDERSFML_H
