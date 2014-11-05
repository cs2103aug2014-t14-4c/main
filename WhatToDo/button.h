//@author A0128603L

//Class: button
//Its to provide buttons in calendar view

#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class button{
public:
	button();
	~button();

	// Initialize font, text and the rectangluar box for button
	void init(float, float, std::string);

	// Render the graphics elements on window
	void draw(sf::RenderWindow*);

	// Set button position
	void setPosition(sf::Vector2f);

	// Check if user is clicking on the button
	bool isClickingOn(sf::Vector2f mouse);

	// Set the opacity of the button
	void setAlpha(int);

private:
	//////////////
	//Member Data
	//////////////
	sf::Font font;
	sf::Text showingText;			//Button showing name
	sf::RectangleShape rectangle;	//The rectangular box
	int alpha_value;				//Opacity
};

