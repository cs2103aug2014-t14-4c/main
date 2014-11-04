//@author A0128603L

//Class CalendarCanvas
// This is a derived class of QSFMLCanvas, to provide the features of calendar.

#pragma once

#include <boost\date_time.hpp>
#include <qevent.h>

#include "qsfmlcanvas.h"
#include "LogicExecutor.h"
#include "State.h"

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

class WhatToDo;
class taskpopup;

using namespace boost::posix_time;
using namespace boost::gregorian;

class CalendarCanvas : public QSFMLCanvas{

	enum ENUM_DIR {RIGHT = 0, LEFT, DOWN, UP };		//view moving directions

	//This struct is to link the task information and
	//the rectangular shape together, to make retrieving info easier
	struct Calendar_task{
		Task task;
		sf::RectangleShape calendarTasksBlk;
	};

	public:
		// Constructor
		CalendarCanvas(WhatToDo* _main_program_ptr, QWidget* Parent, const QPoint& Position, const QSize& Size) :QSFMLCanvas(Parent, Position, Size, 0){
			main_program_ptr = _main_program_ptr;
			Init();
		}

		// Get State. Update all_calendar_task_vtr, for any changes in task please call this
		void readFromState(State state);

		// Jump to a particular task in the view
		// e.g. jumpToTask(0) to closest task, jumpToTask[all_calendar_task_vtr.size() - 1] to latest task
		void jumpToTask(int);

		// Determinate view size with updated window size
		void resizedUpdate(int, int);

		// Methods for QT buttons to call
		void prevPage();
		void nextPage();

		//////////////
		//Member Data
		//////////////
		bool b_active;					// Is calendar view active?
		WhatToDo* main_program_ptr;		// Pointer to WhatToDo(QT) class
		taskpopup*		popup;					// Popup window when task is clicked

	private:
		// Called when object is created, do initialization
		void Init();

		// Called in update loop
		void Update();

		// Event handler, only run when b_active is true
		void eventHandler();			
		void createEmptyTable();
		void createTaskBlock(int, Task);
		void createTaskOnTable();

		// QT Event Handler override (some sfml event handle is blocked by QT seems to be, so need to use QT's)
		void wheelEvent(QWheelEvent *);
		void keyPressEvent(QKeyEvent *);
		void keyReleaseEvent(QKeyEvent *){} //not used for now

		// Rendering
		void drawTasks();				 // display tasks
		void drawVerticalFloating();	 // display time and vertical lines
		void drawHorizontalFloating();	 // display date and Day name

		// Check which task the user is clicking, to show detail popup
		int clickingOn(sf::Vector2i mouse, sf::View currentView);
		
		// Check whether the current view can move further with a specified direction and distance
		bool ableToMove(ENUM_DIR dir, int extra_dist);

		// Move the view, will check whether it is able to move inside the method before moving
		void viewMove(ENUM_DIR dir, int distance);

		// Create a rectangular shape for task, with tasks specification
		sf::RectangleShape createTaskBlockRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour);

		// Change the first showing date in the calendar
		void changeStartingDate(date Date);

		//////////////
		//Member Data
		//////////////
		//State			state;
		date			calendar_starting_date;	// The first showing date in the calendar	
		bool			b_dragging;				// Is mouse pressed to drag move the view?
		sf::Vector2i	dragging_start;			// The starting position when user drag since last window update
		sf::Font		font;

		// view to seperate different axies, so that they can move seperately
		sf::View		viewTasksCalendarTimeLine, viewTasksCalendarDateLine, viewTasksCalendar;	

		//for grid table graphics
		std::vector<sf::RectangleShape> calendarBackground, calendarTableHorizontal_vtr, calendarTableVertical_vtr;
		std::vector<sf::Text>			calendarTableDate_vtr, calendarTableTime_vtr;
		sf::RectangleShape				seperate_line;

		//for tasks blocks graphics
		vector<Calendar_task>		all_calendar_task_vtr;
		std::vector<sf::Text>		calendarTasksName_vtr;	//to be integrated into all_calendar_task_vtr

		//For background graphics
		sf::Texture		bg_texture;
		sf::Sprite		bg_sprite;
};