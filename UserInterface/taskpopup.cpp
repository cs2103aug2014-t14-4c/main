#include "taskpopup.h"
#include "calendarcanvas.h"

taskpopup::taskpopup(CalendarCanvas* canvas_ptr_){
	canvas_ptr = canvas_ptr_;
	font.loadFromFile("Resources/NotoSansHant-Black.otf");
	taskpopup_display.text_info.setCharacterSize(18);
	taskpopup_display.text_info.setFont(font);
	taskpopup_display.text_info.setColor(sf::Color(255, 255, 255, taskpopup_display.alpha_value));
	taskpopup_display.rectangle.setFillColor(sf::Color(0, 0, 0, taskpopup_display.alpha_value));
	taskpopup_display.rectangle.setOutlineThickness(4);
	taskpopup_display.rectangle.setOutlineColor(sf::Color(50, 50, 50, taskpopup_display.alpha_value));

	taskpopup_display.b_active = false;
	taskpopup_display.b_target_active = false;
	taskpopup_display.b_calendar = true;
	taskpopup_display.alpha_value = 0;

}

taskpopup::~taskpopup(){
}

void taskpopup::init(sf::RenderWindow* window){
	SFMLWindow = window;
}

void taskpopup::draw(){
	if (taskpopup_display.b_active == true || taskpopup_display.b_target_active){
		SFMLWindow->draw(taskpopup_display.rectangle);
		SFMLWindow->draw(taskpopup_display.text_info);
		taskpopup_display.btn_delete.draw(SFMLWindow);
		taskpopup_display.btn_done.draw(SFMLWindow);
	}
}

void taskpopup::updateInfo(sf::Vector2f position, string name, ptime start_time, ptime end_time){
	string display_string = name + "\n" + to_simple_string(start_time) + "\n to " + to_simple_string(end_time);
	taskpopup_display.text_info.setString(display_string);

	int extra_length = (name.size() - 22)*10;
	if (extra_length < 0) extra_length = 0;

	taskpopup_display.text_info.setPosition(position);
	taskpopup_display.rectangle.setPosition(position);
	taskpopup_display.rectangle.setSize(sf::Vector2f(POPUP_MINIUM_WIDTH + extra_length, POPUP_HEIGHT));

	taskpopup_display.btn_delete.init(position.x + 80, position.y + 80, "Delete", NULL);
	taskpopup_display.btn_done.init(position.x, position.y + 80, "Done ", NULL);
}

void taskpopup::updateInfo(sf::Vector2f position, string name, ptime deadline_time){
	string display_string = name + "\n" + to_simple_string(deadline_time);
	taskpopup_display.text_info.setString(display_string);
	
	int extra_length = (name.size() - 22) * 10;
	if (extra_length < 0) extra_length = 0;

	taskpopup_display.text_info.setPosition(position);
	taskpopup_display.rectangle.setPosition(position);
	taskpopup_display.rectangle.setSize(sf::Vector2f(POPUP_MINIUM_WIDTH + extra_length, POPUP_HEIGHT));
}

void taskpopup::setActive(bool active){
	taskpopup_display.b_target_active = active;
}

void taskpopup::eventHandler(sf::Vector2f mouse){
	if (taskpopup_display.btn_delete.isClickingOn(sf::Vector2f(mouse.x, mouse.y))){
		cout << "clicked delete " << "/delete " + to_string(currentTask) << endl;
		State state = LogicExecutor::getNewState("/delete " + to_string(currentTask));
		canvas_ptr->readFromState(state);
		setActive(false);
	}
	else if (taskpopup_display.btn_done.isClickingOn(sf::Vector2f(mouse.x, mouse.y))){
		cout << "clicked delete " << "/done " + to_string(currentTask) << endl;
		State state = LogicExecutor::getNewState("/done " + to_string(currentTask));
		canvas_ptr->readFromState(state);
	}
	//if user clicking elsewhere (even not in rectangle), popup deactive it self
	else if (!taskpopup_display.rectangle.getGlobalBounds().contains(mouse)){
			setActive(false);
	}
}

void taskpopup::update(){
	//Fade in/out effect
	if (taskpopup_display.b_target_active != taskpopup_display.b_active){
		if (taskpopup_display.b_target_active == true && taskpopup_display.b_active == false){
			if (taskpopup_display.alpha_value < 255){
				taskpopup_display.alpha_value = taskpopup_display.alpha_value + 20;
				if (taskpopup_display.alpha_value > 255)
					taskpopup_display.alpha_value = 255;
			}
			else taskpopup_display.b_active = true;
		}
		else if (taskpopup_display.b_target_active == false && taskpopup_display.b_active == true){
			if (taskpopup_display.alpha_value > 0){
				taskpopup_display.alpha_value = taskpopup_display.alpha_value - 60;
				if (taskpopup_display.alpha_value < 0)
					taskpopup_display.alpha_value = 0;
			}
			else taskpopup_display.b_active = false;
		}
		taskpopup_display.text_info.setColor(sf::Color(255, 255, 255, taskpopup_display.alpha_value));
		taskpopup_display.rectangle.setFillColor(sf::Color(0, 0, 0, taskpopup_display.alpha_value));
		taskpopup_display.rectangle.setOutlineColor(sf::Color(50, 50, 50, taskpopup_display.alpha_value));
		taskpopup_display.btn_done.setAlpha(taskpopup_display.alpha_value);
		taskpopup_display.btn_delete.setAlpha(taskpopup_display.alpha_value);
	}
}

bool taskpopup::isActive(){
	return taskpopup_display.b_target_active;
}