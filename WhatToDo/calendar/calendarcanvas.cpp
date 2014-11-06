//@author A0128603L
//
// Description in header file

#include "calendarcanvas.h"
#include "whattodo.h"
#include "taskpopup.h"
#include "Task.h"

void CalendarCanvas::Init(){
	ptime now = second_clock::local_time();
	changeStartingDate(now.date());

	font.loadFromFile("UI Files/NotoSansHant-Black.otf");
	font_time.loadFromFile("UI Files/NotoSansHant-Light.otf");
	bg_texture.loadFromFile("UI Files/image.jpg");
	bg_sprite.setTexture(bg_texture);

	createEmptyTable();

	//background for dates
	seperate_line.setSize(sf::Vector2f(100, 9999.f));
	seperate_line.setFillColor(sf::Color(0, 0, 0, 180));
	seperate_line.setPosition(0.f, -5000.f);

	popup = new taskpopup(this);
	popup->init(this);

	b_dragging = false;
	b_active = true;

	this->setFramerateLimit(60);

	resizedUpdate(FRAME_WIDTH, FRAME_HEIGHT);
	//jumpToTask(0);
}

void CalendarCanvas::Update(){
	clear(sf::Color(0, 0, 0, 0));
	if (b_active){
		eventHandler();
		setView(this->getDefaultView());
		draw(bg_sprite);

		//draw tasks
		setView(viewTasksCalendar);
		drawTasks();

		//draw timeline
		setView(viewTasksCalendarTimeLine);
		drawVerticalFloating();

		//draw dateline
		setView(viewTasksCalendarDateLine);
		drawHorizontalFloating();

		setView(this->getDefaultView());
		popup->draw();
	}
}

void CalendarCanvas::readFromState(State state){
	cout << "CalendarCanvas readFromState" << endl;
	all_calendar_task_vtr.clear();
	vector<Task> all_task_vtr = state.getAllTasks();
	lastActionType = state.getLastActionType();
	lastActionTaskIndex = state.getLastActionTaskIndex();
	for (unsigned i = 0; i < all_task_vtr.size(); i++){
		//cout << "[Task: " << i << "] " << all_calendar_task_vtr[i].task.getTaskName() << endl;
		if (all_task_vtr[i].getTaskType() == Task::DEADLINE_TIME ||
			all_task_vtr[i].getTaskType() == Task::FIXED_TIME ||
			all_task_vtr[i].getTaskType() == Task::FIXED_START){
			Calendar_task suitable_task;
			suitable_task.task = all_task_vtr[i];
			all_calendar_task_vtr.push_back(suitable_task);
		}
	}
	createEmptyTable();
	createTaskOnTable();
}

void CalendarCanvas::resizedUpdate(int window_width, int window_height){

	viewTasksCalendarTimeLine.setSize(sf::Vector2f(window_width, window_height));
	viewTasksCalendarTimeLine.setViewport(sf::FloatRect(
		1 - ((float)(window_width - 100) / (float)window_width),
		1 - ((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height),
		1.f,
		((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height)));

	viewTasksCalendarTimeLine.setCenter(sf::Vector2f(window_width / 2, window_height / 2));

	viewTasksCalendarDateLine.setSize(sf::Vector2f(window_width, window_height));
	viewTasksCalendarDateLine.setViewport(sf::FloatRect(
		0,
		1 - ((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height),
		1.f,
		((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height)));

	viewTasksCalendarDateLine.setCenter(sf::Vector2f(window_width / 2, window_height / 2));

	viewTasksCalendar.setSize(sf::Vector2f(window_width, window_height));
	viewTasksCalendar.setViewport(sf::FloatRect(
		1 - ((float)(window_width - 100) / (float)window_width),
		1 - ((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height),
		1.f,
		((float)(window_height - TOOLBAR_HEIGHT) / (float)window_height)));

	viewTasksCalendar.setCenter(sf::Vector2f(window_width / 2, window_height / 2));

	bg_sprite.setPosition(sf::Vector2f(0, TOOLBAR_HEIGHT));
	bg_sprite.setScale(sf::Vector2f(1, (float)((float)(window_height - 120) / (float)window_height)));
}

void CalendarCanvas::prevPage(){
	changeStartingDate(calendar_starting_date - days(21));
	createEmptyTable();
	createTaskOnTable();
}

void CalendarCanvas::nextPage(){
	changeStartingDate(calendar_starting_date + days(21));
	createEmptyTable();
	createTaskOnTable();
}

void CalendarCanvas::jumpToTask(int index){	//using index in all_calendar_task_vtr
	if (all_calendar_task_vtr.size() == 0)
		return;	//no task to see, dont jump

	if (all_calendar_task_vtr[index].task.getTaskType() != Task::DEADLINE_TIME)
		changeStartingDate(all_calendar_task_vtr[index].task.getTaskStartTime().date());
	else
		changeStartingDate(all_calendar_task_vtr[index].task.getTaskDeadline().date());


	sf::Vector2f target_pos = all_calendar_task_vtr[index].calendarTasksBlk.getPosition();
	target_pos.x = target_pos.x + viewTasksCalendar.getSize().x / 2 - 100;
	target_pos.y = target_pos.y + viewTasksCalendar.getSize().y / 2 - 100;

	//cout << "Center Pos:" << viewTasksCalendar.getCenter().x << " " << viewTasksCalendar.getCenter().y << endl;
	//cout << "Target Pos:" << target_pos.x << " " << target_pos.y << endl;
	if (abs(viewTasksCalendar.getCenter().x - target_pos.x) > 10){
		if (viewTasksCalendar.getCenter().x > target_pos.x){
			while (ableToMove(LEFT, -10)){
				if (viewTasksCalendar.getCenter().x < target_pos.x)
					break;
				else
					viewMove(LEFT, -10);
			}
		}
		else if (viewTasksCalendar.getCenter().x < target_pos.x){
			while (ableToMove(RIGHT, 10)){
				if (viewTasksCalendar.getCenter().x > target_pos.x)
					break;
				else
					viewMove(RIGHT, 10);
			}
		}
	}

	if (abs(viewTasksCalendar.getCenter().y - target_pos.y) > 10){
		if (viewTasksCalendar.getCenter().y > target_pos.y){
			while (ableToMove(UP, -10)){
				if (viewTasksCalendar.getCenter().y < target_pos.y)
					break;
				else
					viewMove(UP, -10);
			}
		}
		else if (viewTasksCalendar.getCenter().y < target_pos.y){
			while (ableToMove(DOWN, 10)){
				if (viewTasksCalendar.getCenter().y > target_pos.y)
					break;
				else
					viewMove(DOWN, 10);
			}
		}
	}
}

void CalendarCanvas::drawTasks(){
	draw(calendarBackground[0]);

	for (unsigned i = 0; i < calendarTableHorizontal_vtr.size(); i++)	
		draw(calendarTableHorizontal_vtr[i]);//draw horizontal lines

	for (unsigned i = 0; i < all_calendar_task_vtr.size(); i++)	
		draw(all_calendar_task_vtr[i].calendarTasksBlk);//draw tasks blocks

	for (unsigned i = 0; i < calendarTasksName_vtr.size(); i++) 
		draw(calendarTasksName_vtr[i]);//draw tasks names
}

void CalendarCanvas::drawVerticalFloating(){
	draw(calendarBackground[1]);	//draw the black bar
	for (unsigned i = 0; i < calendarTableVertical_vtr.size(); i++)
		draw(calendarTableVertical_vtr[i]);
	for (unsigned i = 0; i < calendarTableTime_vtr.size(); i++)
		draw(calendarTableTime_vtr[i]);
}

void CalendarCanvas::drawHorizontalFloating(){
	draw(seperate_line);
	for (unsigned i = 0; i < calendarTableDate_vtr.size(); i++)
		draw(calendarTableDate_vtr[i]);
}

void CalendarCanvas::createEmptyTable(){
	calendarTableHorizontal_vtr.clear();
	calendarTableVertical_vtr.clear();
	calendarTableDate_vtr.clear();
	calendarTableTime_vtr.clear();

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
	text_time.setStyle(sf::Text::Underlined);
	text_time.setColor(sf::Color::White);
	text_time.setCharacterSize(14);

	//Vertical line
	sf::RectangleShape verticalLine[26];
	for (unsigned i = 0; i < 26; i++){
		verticalLine[i].setSize(sf::Vector2f(2.f, 9999.f));
		verticalLine[i].setFillColor(sf::Color(0, 0, 0, 120));
		verticalLine[i].setPosition(VERTICAL_LINE_INTERVAL * i, 0.f);
		calendarTableVertical_vtr.push_back(verticalLine[i]);

		if (i < 25){
			if (to_string(i).size() == 1)
				text_time.setString("0" + to_string(i) + "00");
			else
				text_time.setString(to_string(i) + "00");
			text_time.setPosition(5 + VERTICAL_LINE_INTERVAL * i, 0 + 10.f);
			calendarTableTime_vtr.push_back(text_time);
		}
	}

	//Date Text
	sf::Text text_date;
	text_date.setFont(font);
	text_date.setColor(sf::Color::White);
	text_date.setCharacterSize(14);

	//get current time

	date today = calendar_starting_date;
	calendarTableDate_vtr.clear();
	//horizontal lines
	sf::RectangleShape horizontalLine[23]; //for 21 task prerendered
	for (unsigned i = 0; i < 23; i++){
		//horizontal lines
		horizontalLine[i].setSize(sf::Vector2f(9999.f, 2.f));
		horizontalLine[i].setFillColor(sf::Color(0, 0, 0, 170));
		horizontalLine[i].setPosition(-5000, BLOCK_HEIGHT * i);
		if (i == 22){
			horizontalLine[i].setSize(sf::Vector2f(9999.f, 200.f));
		}
		calendarTableHorizontal_vtr.push_back(horizontalLine[i]);

		if (i < 22){
			//Date Text, e.g.: Mon 1/10
			text_date.setString(
				"\n " + day_of_week_to_string((today + days(i - 1)).day_of_week())
				+ "\n"
				+ to_string((today + days(i)).day())
				+ " "
				+ month_to_string((today + days(i)).month()));
			text_date.setPosition(13, BLOCK_HEIGHT * i - 14);
			calendarTableDate_vtr.push_back(text_date);
		}
	}
}
sf::RectangleShape CalendarCanvas::createTaskBlockRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color colour){
	sf::RectangleShape block;
	block.setSize(size);
	block.setFillColor(colour);
	block.setPosition(position);
	block.setOutlineColor(BLOCK_OUTLINE_COLOUR);
	return block;
}

void CalendarCanvas::createTaskBlock(int block_index,Task task){
	sf::Text name;
	name.setFont(font);
	name.setColor(sf::Color::White);
	name.setCharacterSize(14);
	float block_width = VERTICAL_LINE_INTERVAL * (task.getTaskDuration().hours()) + VERTICAL_LINE_INTERVAL * (task.getTaskDuration().minutes()) / 60;
	
	//checking whether the block can fully display the task name
	if (block_width / 15 >= task.getTaskName().size()){	
		name.setString(task.getTaskName());	//can display full name
	}
	else{
		if ((block_width) > 30)
			name.setString((task.getTaskName().substr(0, block_width / 15)) + ".."); //display partial and ".."
		else
			name.setString("."); //display partial and "."
	}


	//Creating the rectangluar block
	date today = calendar_starting_date;
	
	//Only display DEADLINE_TIME, FIXED_TIME, FIXED_START,
	if (task.getTaskType() == Task::DEADLINE_TIME){
		all_calendar_task_vtr[block_index].calendarTasksBlk =
		createTaskBlockRectangle(sf::Vector2f(15.f, BLOCK_HEIGHT), BLOCK_DEADLINE_POS, BLOCK_DEADLINE_BG_COLOUR);

		name.setPosition(all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().x + 3,
			all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().y + 3);
	}
	else if (task.getTaskType() == Task::FIXED_TIME){
		all_calendar_task_vtr[block_index].calendarTasksBlk = createTaskBlockRectangle(
			sf::Vector2f(block_width, BLOCK_HEIGHT),BLOCK_FIXED_POS,BLOCK_BG_COLOUR);

		name.setPosition(all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().x + 3,
						 all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().y + 3);
	}
	else if (task.getTaskType() == Task::FIXED_START){
		all_calendar_task_vtr[block_index].calendarTasksBlk = createTaskBlockRectangle(
			sf::Vector2f(15.f, BLOCK_HEIGHT), BLOCK_FIXED_POS,BLOCK_BG_COLOUR);

		name.setPosition(all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().x + 3,
			all_calendar_task_vtr[block_index].calendarTasksBlk.getPosition().y + 3);
	}
	//done task
	if (all_calendar_task_vtr[block_index].task.getTaskIsDone()){
		all_calendar_task_vtr[block_index].calendarTasksBlk.setFillColor(sf::Color(0, 255, 0, 180));
	}
	//deleting task
	if (lastActionType != State::CHANGED && lastActionType != State::NONE && all_calendar_task_vtr[block_index].task.getTaskIndex() == lastActionTaskIndex){
		all_calendar_task_vtr[block_index].calendarTasksBlk.setFillColor(sf::Color(100, 0, 0, 80));
	}
	calendarTasksName_vtr.push_back(name);
}

void CalendarCanvas::createTaskOnTable(){
	calendarTasksName_vtr.clear();
	for (unsigned i = 0; i < all_calendar_task_vtr.size(); i++){
		createTaskBlock(i, all_calendar_task_vtr[i].task);
	}
}

int CalendarCanvas::clickingOn(sf::Vector2i mouse, sf::View currentView){
	int result = -1;
	//cout << mapPixelToCoords(mouse, viewTasksCalendar).x << " " << mapPixelToCoords(mouse, viewTasksCalendar).y << endl;
	for (unsigned i = 0; i < all_calendar_task_vtr.size(); i++){
		all_calendar_task_vtr[i].calendarTasksBlk.setOutlineColor(BLOCK_OUTLINE_COLOUR);
		if (all_calendar_task_vtr[i].calendarTasksBlk.getGlobalBounds().contains(mapPixelToCoords(mouse, viewTasksCalendar))){
			cout << "calendarTasksBlk_vtr: " << all_calendar_task_vtr[i].task.getTaskName() << endl;
			all_calendar_task_vtr[i].calendarTasksBlk.setOutlineColor(BLOCK_HIGHLIGHT_OUTLINE_COLOUR);
			result = i;
		}
	}
	return result;
}

void CalendarCanvas::wheelEvent(QWheelEvent *x){
}

void CalendarCanvas::keyPressEvent(QKeyEvent *event){
	std::cout << "jump to first task" << std::endl;
	if (event->key() == Qt::Key_Space){
		jumpToTask(0);
	}
}

void CalendarCanvas::eventHandler(){
	sf::Event event;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		b_dragging = false;
	}
	if (b_dragging){
		//cout << "Center Pos:" << viewTasksCalendar.getCenter().x << " " << viewTasksCalendar.getCenter().y << endl;
		sf::Vector2i stationary_mouse = sf::Mouse::getPosition();
		int delta_x = stationary_mouse.x - dragging_start.x;
		int delta_y = stationary_mouse.y - dragging_start.y;
		dragging_start = stationary_mouse;

		if (delta_x > 0)		viewMove(LEFT, -delta_x);
		else if (delta_x < 0)	viewMove(RIGHT, -delta_x);

		if (delta_y > 0)		viewMove(UP, -delta_y);
		else if (delta_y < 0)	viewMove(DOWN, -delta_y);

		//main_program_ptr->updateCalendarScrollBar(viewTasksCalendarTimeLine.getCenter().x, viewTasksCalendarDateLine.getCenter().y);
	}
	popup->update();
	while (pollEvent(event)){
		switch (event.type){
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left){
				popup->eventHandler((sf::Vector2f)sf::Mouse::getPosition(*this));
				int task_no = clickingOn(sf::Mouse::getPosition(*this), viewTasksCalendar);
				if (task_no == -1){	//not clicking on a task, drag
					dragging_start = sf::Mouse::getPosition();
					b_dragging = true;
				}
				else if (all_calendar_task_vtr[task_no].task.getTaskType() == Task::FIXED_TIME){ //is clicking on a task, show popup
					popup->updateInfo(all_calendar_task_vtr[task_no].task.getTaskIndex(),
						all_calendar_task_vtr[task_no].task.getTaskIsDone(),
						(sf::Vector2f)sf::Mouse::getPosition(*this),
						all_calendar_task_vtr[task_no].task.getTaskName(),
						all_calendar_task_vtr[task_no].task.getTaskStartTime(),
						all_calendar_task_vtr[task_no].task.getTaskEndTime()
						);
					popup->setActive(true);
				}
				else if (all_calendar_task_vtr[task_no].task.getTaskType() == Task::FIXED_START){ //is clicking on a task, show popup
					popup->updateInfo(all_calendar_task_vtr[task_no].task.getTaskIndex(),
						all_calendar_task_vtr[task_no].task.getTaskIsDone(),
						(sf::Vector2f)sf::Mouse::getPosition(*this),
						all_calendar_task_vtr[task_no].task.getTaskName(),
						all_calendar_task_vtr[task_no].task.getTaskStartTime()
						);
					popup->setActive(true);
				}
				else if (all_calendar_task_vtr[task_no].task.getTaskType() == Task::DEADLINE_TIME){ //is clicking on a task, show popup
					popup->updateInfo(all_calendar_task_vtr[task_no].task.getTaskIndex(),
						all_calendar_task_vtr[task_no].task.getTaskIsDone(),
						(sf::Vector2f)sf::Mouse::getPosition(*this),
						all_calendar_task_vtr[task_no].task.getTaskName(),
						all_calendar_task_vtr[task_no].task.getTaskDeadline()
						);
					popup->setActive(true);
				}
			}
			break;

		case sf::Event::MouseMoved:

			break;
		default:
			break;
		}
	}
}

bool CalendarCanvas::ableToMove(ENUM_DIR dir, int extra_dist){
	switch (dir){
		case(RIGHT):
			if (viewTasksCalendarTimeLine.getCenter().x + extra_dist < RIGHT_BOUNDARY)
				return true;
			break;
		case(LEFT):
			if (viewTasksCalendarTimeLine.getCenter().x + extra_dist > LEFT_BOUNDARY)
				return true;
			break;
		case(DOWN) :
			if (viewTasksCalendarDateLine.getCenter().y + extra_dist < BOT_BOUNDARY)
				return true;
			break;
		case(UP) :
			if (viewTasksCalendarDateLine.getCenter().y + extra_dist > TOP_BOUNDARY)
				return true;
			break;
		default:
			return false;
	}
	return false;
}

void CalendarCanvas::viewMove(ENUM_DIR dir, int distance){
	//cout << "viewTasksCalendarDateLine: " << viewTasksCalendarDateLine.getCenter().y << endl;
	//cout << "viewTasksCalendarTimeLine: " << viewTasksCalendarTimeLine.getCenter().x << endl;
	if (ableToMove(dir, distance)){
		switch (dir){
			case(RIGHT) :
				viewTasksCalendarTimeLine.move(distance, 0);
				viewTasksCalendar.move(distance, 0);
				break;
			case(LEFT) :
				viewTasksCalendarTimeLine.move(distance, 0);
				viewTasksCalendar.move(distance, 0);
				break;
			case(DOWN) :
				viewTasksCalendarDateLine.move(0, distance);
				viewTasksCalendar.move(0, distance);
				break;
			case(UP) :
				viewTasksCalendarDateLine.move(0, distance);
				viewTasksCalendar.move(0, distance);
				break;
			default:
				return;
		}
	}
}

void CalendarCanvas::changeStartingDate(date Date){
	calendar_starting_date = Date;
	//readFromState(state);
}


string CalendarCanvas::day_of_week_to_string(int day){
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

string CalendarCanvas::month_to_string(int month) {
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
