#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Task.h"
#include "LogicExecutor.h"

#define VERTICAL_LINE_INTERVAL 160.f

extern string day_of_week_to_string(int day);
extern string month_to_string(int month);

class calendar{
public:
	static calendar* Instance();

	void init(sf::RenderWindow* window);	//settings
	void drawVerticalFloating(); // display time and vertical lines
	void drawHorizontalFloating(); // display date and Day name
	void draw();	//display dates and horizontal lines
	void readFromState(State);	//get state
private:
	calendar(){};
	calendar(calendar const&){};
	calendar& operator=(calendar const&){};
	static calendar* m_pInstance;

	sf::RenderWindow* SFMLWindow;
	void createEmptyTable();
	void createTaskBlock(Task);
	void createTaskOnTable();
	State state;
	//for table
	std::vector<sf::RectangleShape> calendarBackground;
	std::vector<sf::RectangleShape> calendarTableHorizontal_vtr;
	std::vector<sf::RectangleShape> calendarTableVertical_vtr;
	std::vector<sf::Text> calendarTableDate_vtr;
	std::vector<sf::Text> calendarTableTime_vtr;
	sf::RectangleShape seperate_line;

	//for tasks blocks
	vector<Task> dead_vtr;
	vector<Task> timed_vtr;

	std::vector<sf::RectangleShape> calendarTasksBlk_vtr;
	std::vector<sf::Text> calendarTasksName_vtr;
	sf::Font font;
};

