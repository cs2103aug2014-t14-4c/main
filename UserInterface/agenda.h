#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <algorithm>
#include "State.h"
#include "Task.h"
#include "LogicExecutor.h"

#define TITLE_COLOUR sf::Color(0, 0, 0, 100)
#define ELEMENT_COLOUR sf::Color(0, 0, 0, 50)
using namespace std;

struct taskInfoElement{
	vector<sf::Text> text_vtr;
	sf::RectangleShape rectangle;
	int index;
	/*
	type:
	0: Floating Task						//Title
	1: [index] [plain_text]					//for floating tasks, e.g. "1. asdasd"
	2. [WeekDate], [Date] [Year]			//Title: Agenda date, e.g. "Tues, 10 Nov 2014"
	3. [index] [red_text] [plain_text]		//for DUE tasks, e.g. "2. [DUE] asdasd"
	4. [index] [blue_text] [plain_text]		//for timed tasks, e.g. "3. [12pm-12pm] asdasd"
	*/
};

enum TaskType{
	FIXEDTIME = 1, DEADLINE, FLOATING
};

class agenda{
public:
	static agenda* Instance();
	void init(sf::RenderWindow* window);	//settings
	void draw(sf::RenderWindow*);	//display
	void onClick();	//show options
	void onHover();	//show info
	void clear();
	void readFromState(State);	//get state
	void resizedUpdate();	//when window resize, this will recalculate the lines positions
	void setTransparency(int);
	string returnRealIndex(int);
	vector<Task> returnAllTasks();
	int clickingOn(sf::Vector2f mouse, sf::View currentView);

private:
	static agenda* m_pInstance;
	sf::RenderWindow* SFMLWindow;
	agenda(){};
	agenda(agenda const&){};
	agenda& operator=(agenda const&){};


	void createFloatingTaskTitle();
	void createFloatingTaskBlock(int, string);
	void createDateTitle(ptime);
	void createDueTaskBlock(int, string, string);
	void createTimedTaskBlock(int, string, string);

	void createAgendaView();
	void taskSortByTime(void);

	//related to tasks
	State state;
	vector<Task> allTask;
	sf::Font font;
	//for final display
	vector<taskInfoElement> tasksBlocks;
	int task_index;

	string getTaskDisplayInfo(Task myTask);
	string getDisplayTime(ptime myTime);

};
