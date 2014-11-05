//@author A0128603L
//
// Class TaskPopup
// Is the class for popup in calendar view, showing 
// time info and done, delete buttons.
// Will show fade-in/fade-out effect when in transistion state
// e.g. from disabled->enabled and vice-versa

#pragma once

#include "LogicExecutor.h"
#include "button.h"

#define POPUP_MINIUM_WIDTH 230
#define POPUP_HEIGHT 100

// forward declaration is need in circular dependency
class CalendarCanvas;
class WhatToDo;

struct struct_taskpopup_display{
	bool b_active, b_target_active;		// The popup can be in transistion state (for fade in, fade out)
	sf::Text text_info;					// Name, time...
	button btn_done, btn_delete;		// Buttons for operation
	sf::RectangleShape rectangle;		// Box for the popup panel
	float alpha_value;
};

class taskpopup{
public:

	taskpopup(CalendarCanvas* canvas_ptr);
	~taskpopup();

	// Initialization
	void init(sf::RenderWindow* window);

	// Render
	void draw();

	// Replace info in the popup
	// for normal tasks
	void updateInfo(int task_index, bool is_done, sf::Vector2f position, string name, ptime start_time, ptime end_time);
	// for deadline, which only have starting/dead time
	void updateInfo(int task_index, bool is_done, sf::Vector2f position, string name, ptime time);

	// Enable/Disable
	void setActive(bool active);
	bool isActive();

	// Mouse event handler, to check which button is being clicked
	void eventHandler(sf::Vector2f mouse);

	// Update opacity
	void update();

private:
	// Return a good position that the popup should supposed to be
	sf::Vector2f blockPositionLimit(sf::Vector2f input, sf::Vector2f extend);

	//////////////
	//Member Data
	//////////////
	int							currentTask;	// The index of current showing tasks, to be used for further operation(done/delete)
	bool						b_isTaskDone;
	CalendarCanvas*				canvas_ptr;			//Pointer to the canvas
	sf::RenderWindow*			SFMLWindow;			//Pointer to the window
	WhatToDo*					main_program_ptr;
	sf::Font					font;
	struct_taskpopup_display	taskpopup_display;
};


