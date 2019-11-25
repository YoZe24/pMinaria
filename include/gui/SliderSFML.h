#ifndef SLIDERSFML_H
#define SLIDERSFML_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class SliderSFML
{
    private:

        sf::RectangleShape slider;
        sf::RectangleShape axis;
        sf::Font font;
        sf::Text text;
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
        sf::Text returnText(float x, float y, float z, int fontSize);
        void create(float min, float max);
        void logic(sf::RenderWindow &window);
        float getSliderValue();
        void setSliderValue(float newValue);
        void draw(sf::RenderWindow& window);
};
#endif // SLIDERSFML_H
