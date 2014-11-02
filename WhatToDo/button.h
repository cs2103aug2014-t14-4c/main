//@author A0128603L

#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class button{
public:
	button();	//need to be created with a function
	~button();
	void init(float, float, std::string, void(*function)());
	void draw(sf::RenderWindow*);
	void setPosition(sf::Vector2f);
	bool isClickingOn(sf::Vector2f mouse);
	void onClick();
	void onHover();
	void setAlpha(int);
private:
	void(*function)();
	sf::Font font;
	sf::Text showingText;
	sf::RectangleShape rectangle;
	int alpha_value;
};

