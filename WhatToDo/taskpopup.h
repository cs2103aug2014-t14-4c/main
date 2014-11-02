//@author A0128603L

#pragma once
#include <SFML/Graphics.hpp>
#include "LogicExecutor.h"
#include "button.h"

#define POPUP_MINIUM_WIDTH 230
#define POPUP_HEIGHT 100

class CalendarCanvas;

struct struct_taskpopup_display{
	bool b_active, b_target_active, b_calendar;
	sf::RectangleShape rectangle;
	sf::Text text_info;
	button btn_done, btn_delete;
	float alpha_value;
};

class taskpopup{
public:
	taskpopup(CalendarCanvas* canvas_ptr);
	~taskpopup();
	void init(sf::RenderWindow* window);
	void draw();
	void updateInfo(sf::Vector2f position, string name, ptime start_time, ptime end_time);
	void updateInfo(sf::Vector2f position, string name, ptime time);
	void setActive(bool active);
	void eventHandler(sf::Vector2f mouse);
	int currentTask;
	bool isActive();
	void update();
private:
	CalendarCanvas* canvas_ptr;
	sf::RenderWindow* SFMLWindow;
	sf::Font font;
	struct_taskpopup_display taskpopup_display;
};


