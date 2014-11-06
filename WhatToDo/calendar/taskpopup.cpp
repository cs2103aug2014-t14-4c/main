//@author A0128603L
//
// Description in header file

#include "taskpopup.h"
#include "calendarcanvas.h"
#include "whattodo.h"

taskpopup::taskpopup(CalendarCanvas* canvas_ptr_){
	canvas_ptr = canvas_ptr_;
	font.loadFromFile("UI FIles/NotoSansHant-Black.otf");
	taskpopup_display.text_info.setCharacterSize(18);
	taskpopup_display.text_info.setFont(font);
	taskpopup_display.text_info.setColor(sf::Color(255, 255, 255, taskpopup_display.alpha_value));
	taskpopup_display.rectangle.setFillColor(sf::Color(0, 0, 0, taskpopup_display.alpha_value));
	taskpopup_display.rectangle.setOutlineThickness(4);
	taskpopup_display.rectangle.setOutlineColor(sf::Color(50, 50, 50, taskpopup_display.alpha_value));

	taskpopup_display.b_active = false;
	taskpopup_display.b_target_active = false;
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

void taskpopup::updateInfo(int task_index, bool is_done, sf::Vector2f position, string name, ptime start_time, ptime end_time){
	currentTask = task_index;
	b_isTaskDone = is_done;

	string display_string = name + "\n" + to_simple_string(start_time) + "\n to " + to_simple_string(end_time);
	taskpopup_display.text_info.setString(display_string);

	int extra_length = (name.size() - 22)*10;
	if (extra_length < 0) extra_length = 0;


	taskpopup_display.rectangle.setSize(sf::Vector2f(POPUP_MINIUM_WIDTH + extra_length, POPUP_HEIGHT));
	position = blockPositionLimit(position, taskpopup_display.rectangle.getSize());
	taskpopup_display.text_info.setPosition(position);
	taskpopup_display.rectangle.setPosition(position);

	taskpopup_display.btn_delete.init(position.x + 80, position.y + 80, "Delete");
	if (!b_isTaskDone){	 // task is not done
		taskpopup_display.btn_done.init(position.x, position.y + 80, "Done ");
	}
	else{
		taskpopup_display.btn_done.init(position.x, position.y + 80, "unDone");
	}
}

void taskpopup::updateInfo(int task_index, bool is_done, sf::Vector2f position, string name, ptime deadline_time){
	currentTask = task_index;
	b_isTaskDone = is_done;

	string display_string = name + "\n" + to_simple_string(deadline_time);
	taskpopup_display.text_info.setString(display_string);
	
	int extra_length = (name.size() - 22) * 10;
	if (extra_length < 0) extra_length = 0;


	taskpopup_display.rectangle.setSize(sf::Vector2f(POPUP_MINIUM_WIDTH + extra_length, POPUP_HEIGHT));
	position = blockPositionLimit(position, taskpopup_display.rectangle.getSize());
	taskpopup_display.text_info.setPosition(position);
	taskpopup_display.rectangle.setPosition(position);

	taskpopup_display.btn_delete.init(position.x + 80, position.y + 80, "Delete");
	if (!b_isTaskDone){	 // task is not done
		taskpopup_display.btn_done.init(position.x, position.y + 80, "Done ");
	}
	else{
		taskpopup_display.btn_done.init(position.x, position.y + 80, "unDone");
	}
}

void taskpopup::setActive(bool active){
	taskpopup_display.b_target_active = active;
}

void taskpopup::eventHandler(sf::Vector2f mouse){
	enum userCommandType { COMMAND_OTHERS = 1, COMMAND_EDIT, COMMAND_DONE, COMMAND_DELETE, COMMAND_HELP, COMMAND_HELP_ADD, COMMAND_HELP_EDIT, COMMAND_HELP_DELETE, COMMAND_HELP_DONE, COMMAND_HELP_SEARCH, COMMAND_HELP_CLEAR, COMMAND_HELP_UNDO, COMMAND_HELP_REDO, COMMAND_HELP_FILTER };
	
	if (!taskpopup_display.b_target_active) // if it is not active, dont do checking for buttons
		return;

	if (taskpopup_display.btn_delete.isClickingOn(sf::Vector2f(mouse.x, mouse.y))){
		cout << "clicked delete " << "/delete " + to_string(currentTask) << endl;
		(canvas_ptr->main_program_ptr)->handleCalendarCommands("/delete_r " + to_string(currentTask));
		(canvas_ptr->main_program_ptr)->updateCalendarView();
		setActive(false);
	}
	else if (taskpopup_display.btn_done.isClickingOn(sf::Vector2f(mouse.x, mouse.y))){
		if (!b_isTaskDone){
			//cout << "clicked done " << "/done " + to_string(currentTask) << endl;
			(canvas_ptr->main_program_ptr)->handleCalendarCommands("/done_r " + to_string(currentTask));
		}
		else{
			//cout << "clicked done " << "/undone " + to_string(currentTask) << endl;
			(canvas_ptr->main_program_ptr)->handleCalendarCommands("/undone_r " + to_string(currentTask));
		}
		(canvas_ptr->main_program_ptr)->updateCalendarView();
		setActive(false);
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

sf::Vector2f taskpopup::blockPositionLimit(sf::Vector2f input, sf::Vector2f extend){
	if ((input.y + extend.y) > FRAME_HEIGHT){
		input.y = FRAME_HEIGHT - extend.y;
	}
	if ((input.x + extend.x) > FRAME_WIDTH){
		input.x = FRAME_WIDTH - extend.x;
	}
	return input;
}
