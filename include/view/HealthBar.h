#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar();
        HealthBar(const HealthBar& other);

        void update(int k);
        void draw(sf::RenderWindow &window);

    protected:

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int max;
        sf::RectangleShape bar;
};

#endif // HEALTHBAR_H
