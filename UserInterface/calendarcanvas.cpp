#include "calendarcanvas.h"
#include <Windows.h>

string day_of_week_to_string(int day){
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


string month_to_string(int month) {
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

void CalendarCanvas::resizedUpdate(){
	viewTasksCalendarTimeLine.setSize(sf::Vector2f(this->getSize().x, this->getSize().y));
	viewTasksCalendarTimeLine.setViewport(sf::FloatRect(
		1 - ((float)(this->getSize().x - 100) / (float)this->getSize().x),
		1 - ((float)(this->getSize().y - 60) / (float)this->getSize().y),
		1.f,
		((float)(this->getSize().y - 60) / (float)this->getSize().y)));

	viewTasksCalendarTimeLine.setCenter(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));

	viewTasksCalendarDateLine.setSize(sf::Vector2f(this->getSize().x, this->getSize().y));
	viewTasksCalendarDateLine.setViewport(sf::FloatRect(
		0,
		1 - ((float)(this->getSize().y - 60) / (float)this->getSize().y),
		1.f,
		((float)(this->getSize().y - 60) / (float)this->getSize().y)));

	viewTasksCalendarDateLine.setCenter(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));

	viewTasksCalendar.setSize(sf::Vector2f(this->getSize().x, this->getSize().y));
	viewTasksCalendar.setViewport(sf::FloatRect(
		1 - ((float)(this->getSize().x - 100) / (float)this->getSize().x),
		1 - ((float)(this->getSize().y - 60) / (float)this->getSize().y),
		1.f,
		((float)(this->getSize().y - 60) / (float)this->getSize().y)));

	viewTasksCalendar.setCenter(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));

	bg_sprite.setPosition(sf::Vector2f(0, 60));
	bg_sprite.setScale(sf::Vector2f(1, (float)((float)(this->getSize().y - 120) / (float)this->getSize().y)));
}

void CalendarCanvas::Init(){
	font.loadFromFile("Resources/NotoSansHant-Black.otf");

	createEmptyTable();

	//background for dates
	seperate_line.setSize(sf::Vector2f(100, 9999.f));
	seperate_line.setFillColor(sf::Color(0, 0, 0, 180));
	seperate_line.setPosition(0.f, -5000.f);

	bg_texture.loadFromFile("Resources/image.jpg");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(sf::Vector2f(1, (float)((float)(this->getSize().y - 120) / (float)this->getSize().y)));

	popup = new taskpopup(this);
	popup->init(this);

	b_dragging = false;

	State state = LogicExecutor::getNewState("/load");	//load previous created tasks
	readFromState(state);

	resizedUpdate();
	this->setFramerateLimit(60);
	b_active = true;
	jumpToTask(0);
}

void CalendarCanvas::Update(){
	clear(sf::Color(0, 0, 0, 255));
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

void CalendarCanvas::drawTasks(){
	//draw background
	draw(calendarBackground[0]);
	//draw horizontal lines
	for (int i = 0; i < calendarTableHorizontal_vtr.size(); i++)
		draw(calendarTableHorizontal_vtr[i]);
	//draw tasks blocks
	for (int i = 0; i < all_calendar_task_vtr.size(); i++)
		draw(all_calendar_task_vtr[i].calendarTasksBlk);
	//draw tasks names
	for (int i = 0; i < calendarTasksName_vtr.size(); i++)
		draw(calendarTasksName_vtr[i]);
}

//draw timeline
void CalendarCanvas::drawVerticalFloating(){
	draw(calendarBackground[1]);	//draw the black bar
	for (int i = 0; i < calendarTableVertical_vtr.size(); i++)
		draw(calendarTableVertical_vtr[i]);
	for (int i = 0; i < calendarTableTime_vtr.size(); i++)
		draw(calendarTableTime_vtr[i]);
}

//draw dateline
void CalendarCanvas::drawHorizontalFloating(){
	draw(seperate_line);
	for (int i = 0; i < calendarTableDate_vtr.size(); i++)
		draw(calendarTableDate_vtr[i]);
}

//Get newest State
void CalendarCanvas::readFromState(State _state){
	all_calendar_task_vtr.clear();
	vector<Task> all_task_vtr = _state.getAllTasks();
	for (int i = 0; i < all_task_vtr.size(); i++){
		if (all_task_vtr[i].getTaskType() == 1 || all_task_vtr[i].getTaskType() == 2){
			Calendar_task suitable_task;
			suitable_task.task = all_task_vtr[i];
			all_calendar_task_vtr.push_back(suitable_task);
		}
	}
	createEmptyTable();
	createTaskOnTable();
}

void CalendarCanvas::createEmptyTable(){
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
		horizontalLine[i].setPosition(-5000, 100 * i);
		calendarTableHorizontal_vtr.push_back(horizontalLine[i]);

		if (i < 22){
			//Date Text, e.g.: Mon 1/10
			text_date.setString(
				"\n " + day_of_week_to_string((today + days(i - 1)).day_of_week())
				+ "\n"
				+ to_string((today + days(i)).day())
				+ " "
				+ month_to_string((today + days(i)).month()));
			text_date.setPosition(10, 100 * i);
			calendarTableDate_vtr.push_back(text_date);
		}
	}
}
void CalendarCanvas::createTaskBlock(int block_index,Task task){
	sf::Text name;
	float block_width = VERTICAL_LINE_INTERVAL * (task.getTaskDuration().hours()) + VERTICAL_LINE_INTERVAL * (task.getTaskDuration().minutes()) / 60;
	if (block_width / 15 >= task.getTaskName().size()){	//can display full name
		name.setString(task.getTaskName());
	}
	else{
		if ((block_width) > 30)
			name.setString((task.getTaskName().substr(0, block_width / 15)) + ".."); //display partial and ..
		else{
			name.setString("."); //display partial and ..
		}
	}
	name.setFont(font);
	name.setColor(sf::Color::White);
	name.setCharacterSize(18);

	sf::RectangleShape block;

	ptime now = second_clock::local_time();
	date today = now.date();

	if (task.getTaskType() == 1){ //FixedTime
		block.setSize(sf::Vector2f(block_width , BLOCK_HEIGHT));
		block.setFillColor(sf::Color(10, 10, 10, 255));
		block.setPosition(sf::Vector2f(
			task.getTaskStartTime().time_of_day().hours() * VERTICAL_LINE_INTERVAL
			+ VERTICAL_LINE_INTERVAL * task.getTaskStartTime().time_of_day().minutes() / 60
			+ 2,
			(task.getTaskStartTime().date() - today).days() * BLOCK_HEIGHT + 2));
		name.setPosition(sf::Vector2f(
			task.getTaskStartTime().time_of_day().hours() * VERTICAL_LINE_INTERVAL
			+ VERTICAL_LINE_INTERVAL * task.getTaskStartTime().time_of_day().minutes() / 60
			+ 5,
			(task.getTaskStartTime().date() - today).days() * BLOCK_HEIGHT + 5));
	}
	if (task.getTaskType() == 2){ //Deadline
		block.setSize(sf::Vector2f(20.f, BLOCK_HEIGHT));
		block.setFillColor(sf::Color(50, 0, 0, 255));
		block.setPosition(sf::Vector2f(
			task.getTaskDeadline().time_of_day().hours() * VERTICAL_LINE_INTERVAL
			+ VERTICAL_LINE_INTERVAL * task.getTaskDeadline().time_of_day().minutes() / 60
			+ 2,
			(task.getTaskDeadline().date() - today).days() * BLOCK_HEIGHT + 2));
		name.setPosition(sf::Vector2f(
			task.getTaskDeadline().time_of_day().hours() * VERTICAL_LINE_INTERVAL
			+ VERTICAL_LINE_INTERVAL * task.getTaskDeadline().time_of_day().minutes() / 60
			+ 5,
			(task.getTaskDeadline().date() - today).days() * BLOCK_HEIGHT
			+ 5));
	}

	block.setOutlineColor(BLOCK_DEFAULT_OUTLINE_COLOUR);
	all_calendar_task_vtr[block_index].calendarTasksBlk = block;
	calendarTasksName_vtr.push_back(name);
}

void CalendarCanvas::createTaskOnTable(){
	calendarTasksName_vtr.clear();
	for (int i = 0; i < all_calendar_task_vtr.size(); i++){
		createTaskBlock(i, all_calendar_task_vtr[i].task);
	}
}

int CalendarCanvas::clickingOn(sf::Vector2i mouse, sf::View currentView){
	int result = -1;
	cout << mapPixelToCoords(mouse, viewTasksCalendar).x << " " << mapPixelToCoords(mouse, viewTasksCalendar).y << endl;
	for (int i = 0; i < all_calendar_task_vtr.size(); i++){
		all_calendar_task_vtr[i].calendarTasksBlk.setOutlineColor(BLOCK_DEFAULT_OUTLINE_COLOUR);
		if (all_calendar_task_vtr[i].calendarTasksBlk.getGlobalBounds().contains(mapPixelToCoords(mouse, viewTasksCalendar))){
			cout << "calendarTasksBlk_vtr: " << all_calendar_task_vtr[i].task.getTaskName() << endl;
			all_calendar_task_vtr[i].calendarTasksBlk.setOutlineColor(BLOCK_HIGHLIGHT_OUTLINE_COLOUR);
			result = i;
		}
	}
	return result;
}


void CalendarCanvas::jumpToTask(int index){	//using index in all_calendar_task_vtr
	if (all_calendar_task_vtr.size() == 0)
		return;	//no task to see, dont jump
	sf::Vector2f target_pos = sf::Vector2f(all_calendar_task_vtr[index].calendarTasksBlk.getPosition().x + this->getSize().x / 2 * 0.8,
		all_calendar_task_vtr[index].calendarTasksBlk.getPosition().y + this->getSize().y / 2 * 0.8);

	viewTasksCalendar.setCenter(target_pos.x, target_pos.y);
	viewTasksCalendarTimeLine.setCenter(target_pos.x, viewTasksCalendarTimeLine.getCenter().y);
	viewTasksCalendarDateLine.setCenter(viewTasksCalendarDateLine.getCenter().x, target_pos.y);
	if (target_pos.x + this->getSize().x / BOUNDARY_FACTOR > VERTICAL_LINE_INTERVAL * 25){
		viewTasksCalendar.setCenter(VERTICAL_LINE_INTERVAL * 25 - this->getSize().x / BOUNDARY_FACTOR, viewTasksCalendar.getCenter().y);
		viewTasksCalendarTimeLine.setCenter(VERTICAL_LINE_INTERVAL * 25 - this->getSize().x / BOUNDARY_FACTOR, viewTasksCalendarTimeLine.getCenter().y);
	}
	if (target_pos.x - this->getSize().x / BOUNDARY_FACTOR < 0){ //24 hours width boundary
		viewTasksCalendar.setCenter(this->getSize().x / BOUNDARY_FACTOR, viewTasksCalendar.getCenter().y);
		viewTasksCalendarTimeLine.setCenter(this->getSize().x / BOUNDARY_FACTOR, viewTasksCalendarTimeLine.getCenter().y);
	}
	if (target_pos.y + this->getSize().y / BOUNDARY_FACTOR > BLOCK_HEIGHT * 21){ //3 days
		viewTasksCalendar.setCenter(viewTasksCalendar.getCenter().x, BLOCK_HEIGHT * 21 - this->getSize().y / BOUNDARY_FACTOR);
		viewTasksCalendarDateLine.setCenter(viewTasksCalendarDateLine.getCenter().x, BLOCK_HEIGHT * 21 - this->getSize().y / BOUNDARY_FACTOR);
	}
	if (target_pos.y - this->getSize().y / BOUNDARY_FACTOR < 0){
		viewTasksCalendar.setCenter(viewTasksCalendar.getCenter().x, this->getSize().y / BOUNDARY_FACTOR);
		viewTasksCalendarDateLine.setCenter(viewTasksCalendarDateLine.getCenter().x, this->getSize().y / BOUNDARY_FACTOR);
	}
}

void CalendarCanvas::wheelEvent(QWheelEvent *x){
	std::cout << "scroll" << std::endl;
}
void CalendarCanvas::keyPressEvent(QKeyEvent *event){
	std::cout << "key in" << std::endl;
	if (event->key() == Qt::Key_Tab){
		b_active = !b_active;
	}
	if (event->key() == Qt::Key_Space){
		jumpToTask(0);
	}
}
void CalendarCanvas::keyReleaseEvent(QKeyEvent *x){
	std::cout << "key out" << std::endl;
}
void CalendarCanvas::resizeEvent(QResizeEvent *x){
	std::cout << "resize" << std::endl;
}

void CalendarCanvas::eventHandler(){
	sf::Event event;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		b_dragging = false;
	}
	popup->update();
	while (pollEvent(event)){
		switch (event.type){
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Tab){
				b_active = !b_active;
				cout << "on/off" << endl;
			}
			break;
		case sf::Event::MouseWheelMoved:
			cout << "mouse scroll" << endl;
			viewTasksCalendarDateLine.move(0, event.mouseWheel.delta * -20);
			viewTasksCalendar.move(0, event.mouseWheel.delta * -20);
			break;
		case sf::Event::MouseButtonPressed:
			if (this->mapPixelToCoords(sf::Mouse::getPosition(*this)).x > 0 &&
				this->mapPixelToCoords(sf::Mouse::getPosition(*this)).x < this->getSize().x &&
				this->mapPixelToCoords(sf::Mouse::getPosition(*this)).y > 0 &&
				this->mapPixelToCoords(sf::Mouse::getPosition(*this)).y < this->getSize().y
				){
				SetForegroundWindow(this->getSystemHandle());
			}
			if (event.mouseButton.button == sf::Mouse::Left){
				//drag_elapsed = clock.getElapsedTime();
				popup->eventHandler((sf::Vector2f)sf::Mouse::getPosition(*this));
				int task_no = clickingOn(sf::Mouse::getPosition(*this), viewTasksCalendar);
				if (task_no == -1){	//not clicking on a task, drag
					dragging_start = sf::Mouse::getPosition();
					b_dragging = true;
				}
				else{ //is clicking on a task, show popup
					popup->updateInfo((sf::Vector2f)sf::Mouse::getPosition(*this),
						all_calendar_task_vtr[task_no].task.getTaskName(),
						all_calendar_task_vtr[task_no].task.getTaskStartTime(),
						all_calendar_task_vtr[task_no].task.getTaskEndTime()
						);
					popup->currentTask = all_calendar_task_vtr[task_no].task.getTaskIndex();
					popup->setActive(true);
				}
			}
			break;
		case sf::Event::MouseMoved:
			if (b_dragging){
				sf::Vector2i stationary_mouse = sf::Mouse::getPosition();
				bool up = false, down = false, left = false, right = false;
				if (viewTasksCalendarTimeLine.getCenter().x + this->getSize().x / BOUNDARY_FACTOR < VERTICAL_LINE_INTERVAL * 25){
					right = true;
				}
				if (viewTasksCalendarTimeLine.getCenter().x - this->getSize().x / BOUNDARY_FACTOR > 0){ //24 hours width boundary
					left = true;
				}
				if (viewTasksCalendarDateLine.getCenter().y + this->getSize().y / BOUNDARY_FACTOR < BLOCK_HEIGHT * 21){ //3 days
					down = true;
				}
				if (viewTasksCalendarDateLine.getCenter().y - this->getSize().y / BOUNDARY_FACTOR > 0){
					up = true;
				}
				if ((-(stationary_mouse.x - dragging_start.x) < 0 & left) || (-(stationary_mouse.x - dragging_start.x) > 0 & right)){
					viewTasksCalendarTimeLine.move(-(stationary_mouse.x - dragging_start.x), 0);
					viewTasksCalendar.move(-(stationary_mouse.x - dragging_start.x), 0);
				}
				if ((-(stationary_mouse.y - dragging_start.y) > 0 & down) || (-(stationary_mouse.y - dragging_start.y) < 0 & up)){
					viewTasksCalendarDateLine.move(0, -(stationary_mouse.y - dragging_start.y));
					viewTasksCalendar.move(0, -(stationary_mouse.y - dragging_start.y));
				}

				
				dragging_start = stationary_mouse;
			}
			break;

		case sf::Event::Resized:
			// update the view to the new size of the window
			resizedUpdate();
			break;
		default:
			break;
		}
	}
}