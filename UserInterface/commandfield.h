#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <windows.h>
#include "LogicExecutor.h"
#include <boost/algorithm/string.hpp>

#define CMD_INACTIVE_COLOUR sf::Color(200, 200, 200, 30)
#define CMD_ACTIVE_COLOUR sf::Color(10, 10, 10, 255)
#define SGT_COLOUR_HIDE sf::Color(200, 200, 200, 0)
#define SGT_ACTIVE_COLOUR sf::Color(0, 0, 0, 180)
#define CMD_Y_POS 80
using namespace std;

struct struct_mainField{
	sf::RectangleShape main_rectangle;
	sf::Text userInput;				//the text that user typed/pasted
	bool b_Enable;
};

struct struct_suggestionBox{
	sf::RectangleShape suggestion_rectangle;
	sf::Text text;
	bool b_Enable;
};

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
	string getCommandFieldContent();
	void backSpace();
	void addCharacter(char content);
	void setSuggestionText(string text);

	sf::RenderWindow* SFMLWindow;
	sf::Font font;
	bool b_LCtrl;
	struct_mainField main_field;
	struct_suggestionBox suggestion_box;

	sf::Text user_message; // user message from logic executor



	enum userCommandType {COMMAND_OTHERS = 1, COMMAND_EDIT, COMMAND_DONE, COMMAND_DELETE};
	void processCommandEdit(string userCommandInput);
	void processCommandDone(string userCommandInput);
	void processCommandDelete(string userCommandInput);
	void processCommandOthers(string userCommandInput);
	void processUserCommandInput();
	bool checkIsUserCommandInputValid(string userCommandInput);
	string removeUnwantedCharacters(string stringToProcess);
	int determineCommandType(string userCommandInput);
	void updateAllViews(State* stateToUpdateWith);
	void clearCommandField();
	
};

