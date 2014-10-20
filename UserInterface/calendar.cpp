#include "calendar.h"

//global pointer for this singleton
calendar* calendar::m_pInstance = NULL;

calendar* calendar::Instance(){
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new calendar;
	return m_pInstance;
}

void calendar::init(sf::RenderWindow* window){
	SFMLWindow = window;
	font.loadFromFile("NotoSansHant-Black.otf");
	createEmptyTable();

	//background for dates
	seperate_line.setSize(sf::Vector2f(100, 9999.f));
	seperate_line.setFillColor(sf::Color(0, 0, 0, 180));
	seperate_line.setPosition(0.f, -5000.f);
}

void calendar::drawVerticalFloating(){
	SFMLWindow->draw(calendarBackground[1]);	//draw the black bar
	for (int i = 0; i < calendarTableVertical_vtr.size(); i++){
		SFMLWindow->draw(calendarTableVertical_vtr[i]);
	}
	for (int i = 0; i < calendarTableTime_vtr.size(); i++){
		SFMLWindow->draw(calendarTableTime_vtr[i]);
	}
}
void calendar::drawHorizontalFloating(){
	SFMLWindow->draw(seperate_line);
	for (int i = 0; i < calendarTableDate_vtr.size(); i++){
		SFMLWindow->draw(calendarTableDate_vtr[i]);
	}
}

void calendar::draw(){
	//draw background
	SFMLWindow->draw(calendarBackground[0]);
	//draw horizontal lines
	for (int i = 0; i < calendarTableHorizontal_vtr.size(); i++){
		SFMLWindow->draw(calendarTableHorizontal_vtr[i]);
	}
	//draw tasks blocks
	for (int i = 0; i < calendarTasksBlk_vtr.size(); i++){
		SFMLWindow->draw(calendarTasksBlk_vtr[i]);
	}
	//draw tasks names
	for (int i = 0; i < calendarTasksName_vtr.size(); i++){
		SFMLWindow->draw(calendarTasksName_vtr[i]);
	}
}

void calendar::readFromState(State _state){
	dead_vtr = _state.getDeadlineTasks();
	timed_vtr = _state.getTimedTasks();
	createEmptyTable();
	createTaskOnTable();
}

void calendar::createEmptyTable(){
	calendarTableHorizontal_vtr.clear();
	calendarTableVertical_vtr.clear();
	calendarTableDate_vtr.clear();

	//Background dim rectangle
	sf::RectangleShape darkbg_task;
	darkbg_task.setSize(sf::Vector2f(9999.f, 9999.f));
	darkbg_task.setFillColor(sf::Color(0, 0, 0, 50));
	darkbg_task.setPosition(-5000, -5000);
	calendarBackground.push_back(darkbg_task);

	//Time black bar
	sf::RectangleShape darkbg_time;
	darkbg_time.setSize(sf::Vector2f(9999.f, 40.f));
	darkbg_time.setFillColor(sf::Color(0, 0, 0, 240));
	darkbg_time.setPosition(-5000.f, 0);
	calendarBackground.push_back(darkbg_time);

	//Time Text
	sf::Text text_time;
	text_time.setFont(font);
	text_time.setColor(sf::Color::White);
	text_time.setCharacterSize(18);

	//Vertical line
	sf::RectangleShape verticalLine[26];
	for (int i = 0; i < 26; i++){
		verticalLine[i].setSize(sf::Vector2f(5.f, 9999.f));
		verticalLine[i].setFillColor(sf::Color(0, 0, 0, 120));
		verticalLine[i].setPosition(VERTICAL_LINE_INTERVAL * i, 0.f);
		calendarTableVertical_vtr.push_back(verticalLine[i]);

		if (i < 25){
			if (to_string(i).size() == 1)
				text_time.setString("0" + to_string(i) + "00");
			else
				text_time.setString(to_string(i) + "00");
			text_time.setPosition(10 + VERTICAL_LINE_INTERVAL * i, 0 + 10.f);
			calendarTableTime_vtr.push_back(text_time);
		}
	}

	//Date Text
	sf::Text text_date;
	text_date.setFont(font);
	text_date.setColor(sf::Color::White);
	text_date.setCharacterSize(20);

	//get current time
	ptime now = second_clock::local_time();
	date today = now.date();
	
	//horizontal lines
	sf::RectangleShape horizontalLine[23]; //for 21 task prerendered
	for (int i = 0; i < 23; i++){
		//horizontal lines
		horizontalLine[i].setSize(sf::Vector2f(9999.f, 5.f));
		horizontalLine[i].setFillColor(sf::Color(0, 0, 0, 170));
		horizontalLine[i].setPosition(-5000, 100*i);
		calendarTableHorizontal_vtr.push_back(horizontalLine[i]);

		if (i < 22){
			//Date Text, e.g.: Mon 1/10
			text_date.setString(
				"\n " + day_of_week_to_string((today - days(7) + days(i)).day_of_week())
				+ "\n"
				+ to_string((today - days(7) + days(i)).day())
				+ " "
				+ month_to_string((today - days(7) + days(i)).month()));
			text_date.setPosition(10, 100 * i);
			calendarTableDate_vtr.push_back(text_date);
		}
	}
}
void calendar::createTaskBlock(Task task){
	sf::Text name;
	name.setString(task.getTaskName());
	name.setFont(font);
	name.setColor(sf::Color::White);
	name.setCharacterSize(18);

	sf::RectangleShape block;

	ptime now = second_clock::local_time();
	date today = now.date();

	if (task.getTaskType() == 1){ //FixedTime
		block.setSize(sf::Vector2f(
			160 * (task.getTaskDuration().hours())
			+ 160 * (task.getTaskDuration().minutes())/60
			, 100.f));
		block.setFillColor(sf::Color(10, 10, 10, 255));
		block.setPosition(sf::Vector2f(
			task.getTaskStartTime().time_of_day().hours() * 160
			+ 160 * task.getTaskStartTime().time_of_day().minutes()/60
			+ 2,
			(task.getTaskStartTime().date() - today + days(7)).days() * 100 + 2));
		name.setPosition(sf::Vector2f(
			task.getTaskStartTime().time_of_day().hours() * 160
			+ 160 * task.getTaskStartTime().time_of_day().minutes()/60
			+ 5,
			(task.getTaskStartTime().date() - today + days(7)).days() * 100 + 5));
	}
	if (task.getTaskType() == 2){ //Deadline
		block.setSize(sf::Vector2f(20.f, 100.f));
		block.setFillColor(sf::Color(50, 0, 0, 255));
		block.setPosition(sf::Vector2f(
			task.getTaskDeadline().time_of_day().hours() * 160
			+ 160 * task.getTaskDeadline().time_of_day().minutes()/60
			+ 2,
			(task.getTaskDeadline().date() - today + days(7)).days() * 100 + 2));
		name.setPosition(sf::Vector2f(
			task.getTaskDeadline().time_of_day().hours() * 160
			+ 160 * task.getTaskDeadline().time_of_day().minutes() / 60
			+ 5,
			(task.getTaskDeadline().date() - today + days(7)).days() * 100
			+ 5));
	}
	calendarTasksBlk_vtr.push_back(block);
	calendarTasksName_vtr.push_back(name);
}

void calendar::createTaskOnTable(){
	calendarTasksBlk_vtr.clear();
	calendarTasksName_vtr.clear();
	for (int i = 0; i < dead_vtr.size(); i++){
		createTaskBlock(dead_vtr[i]);
	}
	for (int i = 0; i < timed_vtr.size(); i++){
		createTaskBlock(timed_vtr[i]);
	}
}