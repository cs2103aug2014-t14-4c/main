#include "agenda.h"
agenda* agenda::m_pInstance = NULL;

int getTaskDetailedType(Task myTask);

enum taskDetailedType { TASK_FLOATING = 1, TASK_DEADLINE_TIME, TASK_DEADLINE_ALLDAY, TASK_FIXED_TIME, TASK_FIXED_START, TASK_FIXED_ALLDAY };

int getTaskDetailedType(Task myTask) {
	if (myTask.getTaskType() == FLOATING) {
		return TASK_FLOATING;
	}
	else if (myTask.getTaskType() == DEADLINE) {
		if (myTask.getTaskDeadline().time_of_day().seconds() == 1) {
			return TASK_DEADLINE_ALLDAY;
		}
		else {
			return TASK_DEADLINE_TIME;
		}
	}
	else if (myTask.getTaskType() == FIXEDTIME) {
		if (myTask.getTaskEndTime() != not_a_date_time) {
			return TASK_FIXED_TIME;
		}
		else if (myTask.getTaskEndTime().time_of_day().seconds() == 1) {
			return TASK_FIXED_ALLDAY;
		}
		else {
			return TASK_FIXED_START;
		}
	}
}

bool taskCompare(Task i, Task j){

	if (i.getTaskType() == FLOATING) {
		return true;
	}
	if (j.getTaskType() == FLOATING) {
		return false;
	}

	ptime iTime;
	ptime jTime;

	if (i.getTaskType() == DEADLINE) {
		iTime = i.getTaskDeadline();
	}
	else {
		iTime = i.getTaskStartTime();
	}

	if (j.getTaskType() == DEADLINE) {
		jTime = j.getTaskDeadline();
	}
	else {
		jTime = j.getTaskStartTime();
	}

	if (iTime.date() < jTime.date()) {
		return true;
	}
	else if (iTime.date() > jTime.date()) {
		return false;
	}
	else {
		if (getTaskDetailedType(i) == TASK_FIXED_ALLDAY) {
			return true;
		}
		if (getTaskDetailedType(j) == TASK_FIXED_ALLDAY) {
			return false;
		}
		if (getTaskDetailedType(i) == TASK_DEADLINE_ALLDAY) {
			return true;
		}
		if (getTaskDetailedType(j) == TASK_DEADLINE_ALLDAY) {
			return false;
		}

		if (iTime < jTime) {
			return true;
		}
		else {
			return false;
		}
	}
}

void agenda::taskSortByTime(void){
	std::sort(allTask.begin(), allTask.end(), taskCompare);
}


string day_of_week_to_string(int day){
	if (day == 0) {
		return "Mon";
	}
	else if (day == 1) {
		return "Tue";
	}
	else if (day == 2) {
		return "Wed";
	}
	else if (day == 3) {
		return "Thu";
	}
	else if (day == 4) {
		return "Fri";
	}
	else if (day == 5) {
		return "Sat";
	}
	else if (day == 6) {
		return "Sun";
	}

	return "";
}


string month_to_string(int month) {
	if (month == 1) {
		return "Jan";
	}
	else if (month == 2) {
		return "Feb";
	}
	else if (month == 3) {
		return "Mar";
	}
	else if (month == 4) {
		return "Apr";
	}
	else if (month == 5) {
		return "May";
	}
	else if (month == 6) {
		return "Jun";
	}
	else if (month == 7) {
		return "Jul";
	}
	else if (month == 8) {
		return "Aug";
	}
	else if (month == 9) {
		return "Sep";
	}
	else if (month == 10) {
		return "Oct";
	}
	else if (month == 11) {
		return "Nov";
	}
	else if (month == 12) {
		return "Dec";
	}

	return "";
}

agenda* agenda::Instance(){
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new agenda;
	return m_pInstance;
}

void agenda::init(sf::RenderWindow* window){
	SFMLWindow = window;
	font.loadFromFile("NotoSansHant-Black.otf");
}

void agenda::draw(sf::RenderWindow* window){
	for (int i = 0; i < tasksBlocks.size(); i++){
		window->draw(tasksBlocks[i].rectangle);
		for (int j = 0; j < tasksBlocks[i].text_vtr.size(); j++){
			window->draw(tasksBlocks[i].text_vtr[j]);
		}
	}
}

void agenda::clear(){
	tasksBlocks.clear();
}

//Read all tasks from state
void agenda::readFromState(State _state){
	state = _state;
	allTask = state.getAllTasks();
	createAgendaView();
}

void agenda::createFloatingTaskTitle(){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();

	sf::Text title;
	title.setString("Floating Task");
	title.setFont(font);
	title.setStyle(sf::Text::Underlined);
	title.setColor(sf::Color::White);
	title.setCharacterSize(28);
	title.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(title);

	taskInfo.text_vtr.push_back(title);
	taskInfo.rectangle.setFillColor(TITLE_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x-100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));
	taskInfo.rectangle.setOutlineThickness(3);
	taskInfo.rectangle.setOutlineColor(sf::Color(0, 0, 0, 75));

	tasksBlocks.push_back(taskInfo);
}
void agenda::createFloatingTaskBlock(int index, string name){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();
	if (index > 0){
		sf::Text number;
		number.setString(to_string(task_index) + ".");
		number.setFont(font);
		number.setColor(sf::Color(255, 255, 255, 200));
		number.setCharacterSize(30);
		number.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
		taskInfo.text_vtr.push_back(number);
	}

	sf::Text display_name;
	display_name.setString(name);
	display_name.setFont(font);
	display_name.setColor(sf::Color::White);
	display_name.setCharacterSize(30);
	display_name.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()), (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_name);

	taskInfo.rectangle.setFillColor(ELEMENT_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));

	tasksBlocks.push_back(taskInfo);
}

void agenda::createDateTitle(ptime date){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();

	string showing_date;
	showing_date += day_of_week_to_string(date.date().day_of_week());
	showing_date += ", ";
	showing_date += to_string(date.date().day());
	showing_date += " ";
	showing_date += month_to_string(date.date().month());
	showing_date += " ";
	showing_date += to_string(date.date().year());

	sf::Text title;
	title.setString(showing_date);
	title.setFont(font);
	title.setStyle(sf::Text::Underlined);
	title.setColor(sf::Color::White);
	title.setCharacterSize(28);
	title.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(title);

	taskInfo.text_vtr.push_back(title);
	taskInfo.rectangle.setFillColor(TITLE_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));
	taskInfo.rectangle.setOutlineThickness(3);
	taskInfo.rectangle.setOutlineColor(sf::Color(0,0,0,75));


	tasksBlocks.push_back(taskInfo);
}

void agenda::createDueTaskBlock(int index, string displayInfo, string name){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();

	sf::Text number;
	number.setString(to_string(task_index) + ".");
	number.setFont(font);
	number.setColor(sf::Color(255, 255, 255, 200));
	number.setCharacterSize(30);
	number.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(number);
	/*
	sf::Text display_due;
	display_due.setString(displayInfo);
	display_due.setFont(font);
	display_due.setColor(sf::Color(100,0,0,255));
	display_due.setCharacterSize(30);
	display_due.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()), (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_due);
	*/

	sf::Text display_name;
	display_name.setString(displayInfo + name);
	display_name.setFont(font);
	display_name.setColor(sf::Color::White);
	display_name.setCharacterSize(30);
	display_name.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()), (taskInfo.index + 1) * 40 + 5)); //sf::Vector2f(40.f + 30 * (to_string(task_index).length()) + 90, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_name);

	taskInfo.rectangle.setFillColor(ELEMENT_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));

	tasksBlocks.push_back(taskInfo);
}

void agenda::createTimedTaskBlock(int index, string displayInfo, string name){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();

	sf::Text number;
	number.setString(to_string(task_index) + ".");
	number.setFont(font);
	number.setColor(sf::Color(255, 255, 255, 200));
	number.setCharacterSize(30);
	number.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(number);

	sf::Text display_name;
	display_name.setString(displayInfo + name);
	display_name.setFont(font);
	display_name.setColor(sf::Color::White);
	display_name.setCharacterSize(30);
	display_name.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()), (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_name);

	taskInfo.rectangle.setFillColor(ELEMENT_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));

	tasksBlocks.push_back(taskInfo);
}

void agenda::createAgendaView(){
	date last_date;
	string taskDisplayInfo;
	bool first_floating = true;
	bool floating_exist = false;
	task_index = 1;
	tasksBlocks.clear();

	taskSortByTime();

	//cout << "================================" << endl;
	for (int i = 0; i < allTask.size(); i++){
		//cout << "Agenda: " << allTask[i].getTaskName() << endl;
		if (allTask[i].getTaskType() == FLOATING){
			if (first_floating){
				first_floating = false;
				floating_exist = true;
				createFloatingTaskTitle();
			}
			createFloatingTaskBlock(i + 1, allTask[i].getTaskName());
		}
		else if (allTask[i].getTaskType() == DEADLINE){
			if (last_date != allTask[i].getTaskDeadline().date()){
				createFloatingTaskBlock(0, " ");
				createDateTitle(allTask[i].getTaskDeadline());
				last_date = allTask[i].getTaskDeadline().date();
			}
			taskDisplayInfo = getTaskDisplayInfo(allTask[i]);
			createDueTaskBlock(i + 1, taskDisplayInfo, allTask[i].getTaskName());
		}
		else if (allTask[i].getTaskType() == FIXEDTIME){
			if (last_date != allTask[i].getTaskStartTime().date()){
				createFloatingTaskBlock(0, " ");
				createDateTitle(allTask[i].getTaskStartTime());
				last_date = allTask[i].getTaskStartTime().date();
			}
			taskDisplayInfo = getTaskDisplayInfo(allTask[i]);
			createTimedTaskBlock(i + 1, taskDisplayInfo, allTask[i].getTaskName());
		}
		task_index++;
	}
}

void agenda::resizedUpdate(){
	/*
	agendaRectangles_vtr[0].setSize(sf::Vector2f(1, SFMLWindow->getSize().y - 60));
	for (int i = 1; i < agendaRectangles_vtr.size(); i++){
		
		TableRectangle_vtr[i].setSize(sf::Vector2f(SFMLWindow->getSize().x - 200, 1));
	}
	*/
}

string agenda::returnRealIndex(int index){
	return to_string(allTask[index].getTaskIndex());
}

vector<Task> agenda::returnAllTasks() {
	return allTask;
}

int agenda::clickingOn(sf::Vector2f mouse, sf::View currentView){
	//mouse.y = mouse.y + currentView.getCenter().y - currentView.getSize().y / 2 - 60;
	mouse.y = mouse.y + currentView.getCenter().y - currentView.getSize().y/2 - 60;
	for (int i = 0; i < tasksBlocks.size(); i++){
		if (tasksBlocks[i].rectangle.getGlobalBounds().contains(mouse)){
			return stoi(returnRealIndex(tasksBlocks[i].index-1));
		}
	}
	return -1;
} 

string agenda::getTaskDisplayInfo(Task myTask) {
	string taskDisplayInfo = "";
	if (getTaskDetailedType(myTask) == TASK_DEADLINE_ALLDAY) {
		taskDisplayInfo = "[DUE] ";
	}
	else if (getTaskDetailedType(myTask) == TASK_DEADLINE_TIME) {
		taskDisplayInfo = "[DUE @ " + getDisplayTime(myTask.getTaskDeadline()) + "] ";
	}
	else if (getTaskDetailedType(myTask) == TASK_FIXED_ALLDAY) {
		taskDisplayInfo = "[All Day] ";
	}
	else if (getTaskDetailedType(myTask) == TASK_FIXED_START) {
		taskDisplayInfo = "[" + getDisplayTime(myTask.getTaskStartTime()) + "] ";
	}
	else if (getTaskDetailedType(myTask) == TASK_FIXED_TIME) {
		if (myTask.getTaskStartTime().date() == myTask.getTaskEndTime().date()) {
			taskDisplayInfo = "[" + getDisplayTime(myTask.getTaskStartTime()) + " - " + getDisplayTime(myTask.getTaskEndTime()) + "] ";
		}
		else {
			taskDisplayInfo = "[" + getDisplayTime(myTask.getTaskStartTime()) + " - " + to_simple_string(myTask.getTaskEndTime().date()) + "]";
		}
	}
	return taskDisplayInfo;
}

string agenda::getDisplayTime(ptime myTime) {
	string hours = "";
	string minutes = "";
	string displayTime = "";

	if (myTime.time_of_day().hours() < 10) {
		hours = "0" + to_string(myTime.time_of_day().hours());
	}
	else {
		hours = to_string(myTime.time_of_day().hours());
	}

	if (myTime.time_of_day().minutes() < 10) {
		minutes = "0" + to_string(myTime.time_of_day().minutes());
	}
	else {
		minutes = to_string(myTime.time_of_day().minutes());
	}

	displayTime = hours + ":" + minutes;

	return displayTime;
}