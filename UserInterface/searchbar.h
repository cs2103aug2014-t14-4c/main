#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <windows.h>
#include "LogicExecutor.h"

#define SEARCH_INACTIVE_COLOUR sf::Color(50, 50, 50, 80)
#define SEARCH_ACTIVE_COLOUR sf::Color(50, 50, 50, 170)


using namespace std;

class searchbar{
public:
	static searchbar* Instance();
	void init(sf::RenderWindow* window);
	void draw();
	void resizedUpdate();
	void eventHandler(sf::Event, sf::Vector2f);
	void setActive(bool);
private:
	searchbar();
	~searchbar(){};
	searchbar& operator=(searchbar const&){};
	static searchbar* m_pInstance;

	void updateView();
	void getPastedString(string);
	std::string getCommandFieldContent();
	void backSpace();
	void addCharacter(char content);
	sf::Text userInput;				//the text that user typed/pasted

	sf::RenderWindow* SFMLWindow;
	sf::RectangleShape rectangle;
	sf::Font font;
	bool b_Enable, b_LCtrl;
};

