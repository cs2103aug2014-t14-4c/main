#pragma once
#include <SFML\Graphics.hpp>
#include "button.h"
#include "calendar.h"
#include "agenda.h"
#include "commandfield.h"
#include "searchbar.h"

class SFMLManager
{
public:
	SFMLManager();
	~SFMLManager();

	void init();
	void ready();
	void eventHandler();
	void windowRender();
	bool exit;

private:
	void positionUpdate();
	void drawUI();
	void drawTasks();
	void drawUnfinishedTasks();
	void buttonInit();
	void buttonHandler(void);
	// SFML
	sf::RenderWindow* SFMLWindow;
	sf::Texture texture_background;
	sf::Sprite sprite_background;
	sf::Sprite sprite_background_darker;
	sf::Sprite sprite_background_trans;

	sf::View viewTop;			// Buttons, text fields view
	sf::View viewTasksCalendarTimeLine, viewTasksCalendarDateLine;
	sf::View viewTasksAgenda, viewTasksCalendar;			// Agenda, Calendar view

	button btn_toggleView, btn_undo, btn_redo, btn_delete;

	int view; // 0 = calendar, 1 = agenda
	bool b_dragging;
	sf::Vector2i dragging_start;
	//Keyboard handle
	bool b_LCtrl;

};

