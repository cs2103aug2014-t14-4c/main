//@author A0128603L
//
// Description in header file

#include "button.h"

button::button(){
}

button::~button(){
}

void button::init(float x, float y, std::string name){
	font.loadFromFile("UI_Files/NotoSansHant-Black.otf");
	showingText.setFont(font);
	showingText.setString(name);
	showingText.setCharacterSize(20);
	showingText.setColor(sf::Color(255, 255, 255, 255));
	showingText.setPosition(sf::Vector2f(x + 2, y + 2));

	rectangle.setSize(sf::Vector2f(12 * name.length() + 6, 30.f));
	rectangle.setFillColor(sf::Color(0, 0, 0, 190));
	rectangle.setPosition(sf::Vector2f(x, y));
}

void button::setPosition(sf::Vector2f vector){
	showingText.setPosition(sf::Vector2f(vector.x, vector.y));
	rectangle.setPosition(sf::Vector2f(vector.x, vector.y));
}

void button::draw(sf::RenderWindow* window){
	window->draw(rectangle);
	window->draw(showingText);
}

bool button::isClickingOn(sf::Vector2f mouse){
	if (mouse.x > rectangle.getPosition().x &&
		mouse.x < (rectangle.getPosition().x + rectangle.getSize().x) &&
		mouse.y > rectangle.getPosition().y &&
		mouse.y < (rectangle.getPosition().y + rectangle.getSize().y)){
		return true;
	}
	return false;
}

void button::setAlpha(int alpha){
	showingText.setColor(sf::Color(255, 255, 255, alpha));
	rectangle.setFillColor(sf::Color(0, 0, 0, alpha));
}