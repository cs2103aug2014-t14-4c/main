//@author A0128603L

#pragma once

#include <boost\date_time.hpp>
#include <qevent.h>

#include "LogicExecutor.h"
#include "State.h"

#include "qsfmlcanvas.h"
#include "taskpopup.h"

class WhatToDo;

using namespace boost::posix_time;
using namespace boost::gregorian;

#define TOOLBAR_HEIGHT 0.f
#define BOUNDARY_FACTOR 8
#define BLOCK_HEIGHT 50.f
#define VERTICAL_LINE_INTERVAL 60.f

#define BLOCK_BG_COLOUR sf::Color(10, 10, 10, 255)
#define BLOCK_OUTLINE_COLOUR sf::Color(0, 0, 0, 255)
#define BLOCK_HIGHLIGHT_OUTLINE_COLOUR sf::Color(100, 100, 100, 55)
#define BLOCK_DEADLINE_BG_COLOUR sf::Color(50, 0, 0, 255)
#define BLOCK_DEADLINE_POS sf::Vector2f(task.getTaskDeadline().time_of_day().hours() * VERTICAL_LINE_INTERVAL+ VERTICAL_LINE_INTERVAL * task.getTaskDeadline().time_of_day().minutes() / 60 + 2,(task.getTaskDeadline().date() - today).days() * BLOCK_HEIGHT + 2)
#define BLOCK_FIXED_POS sf::Vector2f(task.getTaskStartTime().time_of_day().hours() * VERTICAL_LINE_INTERVAL + VERTICAL_LINE_INTERVAL * task.getTaskStartTime().time_of_day().minutes() / 60 + 2,(task.getTaskStartTime().date() - today).days() * BLOCK_HEIGHT + 2)



#define FRAME_WIDTH 921	//To determinate the scale of the view
#define FRAME_HEIGHT 501

#define TOP_BOUNDARY 211
#define BOT_BOUNDARY 1042
#define LEFT_BOUNDARY 460
#define RIGHT_BOUNDARY 1140

class CalendarCanvas : public QSFMLCanvas{

	enum ENUM_DIR {RIGHT = 0, LEFT, DOWN, UP };

	struct Calendar_task{
		Task task;
		sf::RectangleShape calendarTasksBlk;
	};

	public:
		CalendarCanvas(WhatToDo* _main_program_ptr, QWidget* Parent, const QPoint& Position, const QSize& Size) :QSFMLCanvas(Parent, Position, Size, 0){
			main_program_ptr = _main_program_ptr;
		}
	
		void readFromState(State);		//get state, for any changes in task please call this
		void jumpToTask(int);			//jumpToTask(0) to closest task, jumpToTask[all_calendar_task_vtr.size()-1] to latest task
		void resizedUpdate(int, int);			 // zoom in and out, update window size
		//function for buttons
		void prevPage();
		void nextPage();
		//function for scrollbar
		void changeVerti(int);
		void changeHori(int);

	private:
		void Init();					//called when object is created
		void Update();					//called in update loop
		void eventHandler();			//only run when b_active is true
		void createEmptyTable();
		void createTaskBlock(int, Task);
		void createTaskOnTable();

		//QT Event Handler override (some sfml event handle is blocked by QT seems to be, so need to use QT's)
		void wheelEvent(QWheelEvent *);
		void keyPressEvent(QKeyEvent *);
		void keyReleaseEvent(QKeyEvent *){} //not used for now

		void drawTasks();				 // display tasks
		void drawVerticalFloating();	 // display time and vertical lines
		void drawHorizontalFloating();	 // display date and Day name

		int clickingOn(sf::Vector2i mouse, sf::View currentView);	//check which task the user is clicking, to show detail popup
		bool ableToMove(ENUM_DIR dir, int external_distance);
		void viewMove(ENUM_DIR dir, int distance);
		sf::RectangleShape createTaskBlockRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour);
		void changeStartingDate(date Date);

		// Variables
		bool b_active;					// Is calendar view active?
		bool b_dragging;				// Is mouse pressed to drag move the view?
		State state;
		sf::View viewTasksCalendarTimeLine, viewTasksCalendarDateLine, viewTasksCalendar;	// view to seperate different axies
		date calendar_starting_date;
		WhatToDo* main_program_ptr;

		//for grid table
		std::vector<sf::RectangleShape> calendarBackground, calendarTableHorizontal_vtr, calendarTableVertical_vtr;
		std::vector<sf::Text> calendarTableDate_vtr, calendarTableTime_vtr;
		sf::RectangleShape seperate_line;

		//for tasks blocks
		vector<Calendar_task> all_calendar_task_vtr;
		std::vector<sf::Text> calendarTasksName_vtr;	//to be integrated into all_calendar_task_vtr

		sf::Font font;
		sf::Vector2i dragging_start;

		sf::Texture bg_texture;	//background
		sf::Sprite bg_sprite;

		sf::Vector2i window_size;

		taskpopup* popup;
};