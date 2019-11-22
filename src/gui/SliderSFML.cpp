#include "gui/SliderSFML.h"

/**
*   Default constructor
*/
SliderSFML::SliderSFML(){}

/**
*
*   Main constructor for Sliders
*
*    @param x : the position x of the slider
*    @param y : the position y of the slider
*
*/
SliderSFML::SliderSFML(int x, int y)
{
	xCord = x;
	yCord = y;
	axisHeight = 10;
	axisWidth = 200;
	sliderWidth = 20;
	sliderHeight = 30;

	if (!font.loadFromFile("PoliceCool.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::Black);

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(Vector2f(axisWidth, axisHeight));
	axis.setFillColor(Color(63,63,63));
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(Color(192,192,192));
}

/**
*
*   Convert values of the slider to be displayed on screen
*
*   @param x : the position x of the text displayed next the slider
*   @param y : the position y of the text displayed next the slider
*   @param z : the max/min value of the slider
*   @param fontSize : the size of the font used
*   @return text : update the text object in the instance of slider to be displayed
*
*/
Text SliderSFML::returnText(float x, float y, float z, int fontSize)
{
    std::string zz= to_string(z).substr(0,3);
    Text t = Text(zz,font,fontSize);
	t.setPosition(x, y + 10);
	t.setFillColor(sf::Color::Black);
	text = t;
	return text;
}

/**
*
*   Initialize values of min/max/axis's value
*
*   @param min : The minimal value of the slider
*   @param max : The maximal value of the slider
*
*/
void SliderSFML::create(float min, float max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}

/**
*
*   Contains logic about the slider
*
*   We take the bounds of the sprite in the Slider class.
*   We test if the mouse is in the sprite's area and if we pressed on left click.
*   Then we test if the mouse leaves the axis of the slider.
*   We set the position (visual) of the slider and we update the slider's value
*
*   @param window : Window of the game to take input informations
*
*/
void SliderSFML::logic(sf::RenderWindow &window)
{
	if (slider.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)
		&& Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (Mouse::getPosition(window).x >= xCord && Mouse::getPosition(window).x <= xCord + axisWidth)
		{
			slider.setPosition(Mouse::getPosition(window).x, yCord);
			sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
		}
	}
}

/**
*
*   Return the slider's value
*
*   @return sliderValue : Return slider's value
*
*/
float SliderSFML::getSliderValue()
{
	return sliderValue;
}

/**
*
*   Set the slider's value
*
*   We check if the newValue is in range of min and max value setting.
*   We set the position of the slider with this new value.
*
*   @param newValue : The new value to update our slider
*/
void SliderSFML::setSliderValue(float newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz*diff2;
		posX += xCord;
		slider.setPosition(posX, yCord);
	}
}

/**
*
*   Drawing all elements of slider
*
*   We are calling the logic method to update our slider's informations
*
*   @param window : @param window : Window of the game to draw our slider
*/
void SliderSFML::draw(RenderWindow& window)
{
	logic(window);
	window.draw(returnText(xCord - 10, yCord + 5, minValue, 20));
	window.draw(axis);
	window.draw(returnText(xCord + axisWidth - 10, yCord + 5, maxValue, 20));
	window.draw(slider);
	window.draw(returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight, sliderValue, 15));
}
