#pragma once
#include <boost\date_time.hpp>
#include <qevent.h>
#include "LogicExecutor.h"
#include "State.h"

#include "qsfmlcanvas.h"
#include "taskpopup.h"

using namespace boost::posix_time;
using namespace boost::gregorian;

#define TOOLBAR_HEIGHT 109.f
#define BOUNDARY_FACTOR 4
#define BLOCK_HEIGHT 100.f
#define BLOCK_HEIGHT_LOW_RES 80.f
#define VERTICAL_LINE_INTERVAL 80.f
#define BLOCK_DEFAULT_OUTLINE_COLOUR sf::Color(0, 0, 0, 255)
#define BLOCK_HIGHLIGHT_OUTLINE_COLOUR sf::Color(100, 100, 100, 55)

class CalendarCanvas : public QSFMLCanvas{

struct Calendar_task{
	Task task;
	sf::RectangleShape calendarTasksBlk;
};

public:
	CalendarCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size)
		:QSFMLCanvas(Parent, Position, Size, 0){}
	void readFromState(State);		//get state, for any changes in task please call this
	void jumpToTask(int);			//jumpToTask(0) to closest task, jumpToTask[all_calendar_task_vtr.size()-1] to latest task
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
	void keyReleaseEvent(QKeyEvent *);
	void resizeEvent(QResizeEvent *);

	void drawTasks();
	void drawVerticalFloating();	 // display time and vertical lines
	void drawHorizontalFloating();	 // display date and Day name

	void resizedUpdate();			 // seems to be useless, now only use once in init, now rendered extra area(bigger than window)

	int clickingOn(sf::Vector2i mouse, sf::View currentView);	//check which task the user is clicking, to show detail popup

	// Variables

	bool b_active;					// Is calendar view active?
	bool b_dragging;				// Is mouse pressed to drag move the view?

	State state;

	sf::View viewTasksCalendarTimeLine, viewTasksCalendarDateLine, viewTasksCalendar;	// view to seperate different axies

	//for grid table
	std::vector<sf::RectangleShape> calendarBackground, calendarTableHorizontal_vtr, calendarTableVertical_vtr;
	std::vector<sf::Text> calendarTableDate_vtr, calendarTableTime_vtr;
	sf::RectangleShape seperate_line;

	//for tasks blocks
	vector<Calendar_task> all_calendar_task_vtr;
	std::vector<sf::Text> calendarTasksName_vtr;	//to be integrated into all_calendar_task_vtr

	sf::Vector2i dragging_start;
	sf::Font font;
	sf::Texture bg_texture;	//background
	sf::Sprite bg_sprite;

	taskpopup* popup;
};