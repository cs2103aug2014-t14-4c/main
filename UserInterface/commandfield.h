#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <windows.h>
#include "LogicExecutor.h"

#define CMD_INACTIVE_COLOUR sf::Color(200, 200, 200, 30)
#define CMD_ACTIVE_COLOUR sf::Color(10, 10, 10, 255)


using namespace std;

class commandfield{
public:
	static commandfield* Instance();
	void init(sf::RenderWindow* window);
	void draw();
	void resizedUpdate();
	void eventHandler(sf::Event, sf::Vector2f);
	void setActive(bool);
private:
	commandfield();
	~commandfield(){};
	commandfield& operator=(commandfield const&){};
	static commandfield* m_pInstance;

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

