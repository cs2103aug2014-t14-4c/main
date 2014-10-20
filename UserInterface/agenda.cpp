#include "agenda.h"
agenda* agenda::m_pInstance = NULL;

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
void agenda::createDueTaskBlock(int index, string name){
	taskInfoElement taskInfo;
	taskInfo.index = tasksBlocks.size();

	sf::Text number;
	number.setString(to_string(task_index) + ".");
	number.setFont(font);
	number.setColor(sf::Color(255, 255, 255, 200));
	number.setCharacterSize(30);
	number.setPosition(sf::Vector2f(40.f, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(number);

	sf::Text display_due;
	display_due.setString("[DUE]");
	display_due.setFont(font);
	display_due.setColor(sf::Color(100,0,0,255));
	display_due.setCharacterSize(30);
	display_due.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()), (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_due);

	sf::Text display_name;
	display_name.setString(name);
	display_name.setFont(font);
	display_name.setColor(sf::Color::White);
	display_name.setCharacterSize(30);
	display_name.setPosition(sf::Vector2f(40.f + 30 * (to_string(task_index).length()) + 90, (taskInfo.index + 1) * 40 + 5));
	taskInfo.text_vtr.push_back(display_name);

	taskInfo.rectangle.setFillColor(ELEMENT_COLOUR);
	taskInfo.rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 100, 40));
	taskInfo.rectangle.setPosition(sf::Vector2f(30.f, (taskInfo.index + 1) * 40));

	tasksBlocks.push_back(taskInfo);
}
void agenda::createTimedTaskBlock(int index, ptime startTime, ptime endTime, string name){
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
	display_name.setString("[fixed time]" + name);
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

bool taskCompare(Task i, Task j){

	if (i.getTaskType() == FIXEDTIME && j.getTaskType() == FIXEDTIME){
		return (i.getTaskStartTime() < j.getTaskStartTime());
	}
	if (i.getTaskType() == FIXEDTIME && j.getTaskType() == DEADLINE){
		return (i.getTaskStartTime() < j.getTaskDeadline());
	}
	if (i.getTaskType() == FIXEDTIME && j.getTaskType() == FLOATING){
		return false;
	}
	if (i.getTaskType() == DEADLINE && j.getTaskType() == FIXEDTIME){
		return (i.getTaskDeadline() < j.getTaskStartTime());
	}
	if (i.getTaskType() == DEADLINE && j.getTaskType() == DEADLINE){
		return (i.getTaskDeadline() < j.getTaskDeadline());
	}
	if (i.getTaskType() == DEADLINE && j.getTaskType() == FLOATING){
		return false;
	}
	if (i.getTaskType() == FLOATING && j.getTaskType() == FIXEDTIME){
		return true;
	}
	if (i.getTaskType() == FLOATING && j.getTaskType() == DEADLINE){
		return true;
	}
	if (i.getTaskType() == FLOATING && j.getTaskType() == FLOATING){
		return true;
	}
}

void agenda::taskSortByTime(void){
	std::sort(allTask.begin(), allTask.end(), taskCompare);
}

void agenda::createAgendaView(){
	date last_date;
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
			createDueTaskBlock(i + 1, allTask[i].getTaskName());
		}
		else if (allTask[i].getTaskType() == FIXEDTIME){
			if (last_date != allTask[i].getTaskStartTime().date()){
				createFloatingTaskBlock(0, " ");
				createDateTitle(allTask[i].getTaskStartTime());
				last_date = allTask[i].getTaskStartTime().date();
			}
			createTimedTaskBlock(i + 1, allTask[i].getTaskStartTime(), allTask[i].getTaskEndTime(), allTask[i].getTaskName());
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