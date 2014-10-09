#include "anothergui.h"
using namespace std;

int AnotherGUI::_size;

AnotherGUI::AnotherGUI(QWidget *parent)
	: QMainWindow(parent)
{
	createSuggestionList();
	ui.setupUi(this);
	this->setFixedSize(956, 681);
	ui.displaycalendar->setVisible(false);

	_myKeyPressEater = new KeyPressEater();
	ui.commandbox->installEventFilter(_myKeyPressEater);

	_myStorage = new Storage();
	_myStorage->setUI(ui);

	connectAllSlots();
	
	//ptime x(date(2014,10,7), hours(2));
	//string everything = changeDateToString(x);
	ui.displaybox->setHtml(QString::fromStdString(""));
	//string html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Calibri'; font-size:11pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:25px; margin-bottom:0px; margin-left:2px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">Mon, 6 Oct 2014 </span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:20%;\"><br /></p><ol style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 2;\"><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> <span style=\" font-weight:600; color:#ff0000;\">[DUE]</span> Finish last round of revision for IE2110 (write the summary cheat sheet to bring in) and PC1432 (redo the two papers asap)</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Try out new things for the fake GUI!</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Are we meeting today? &gt;.&lt;</li><p style=\" margin-top:25px; margin-bottom:0px; margin-left:2px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">Wed, 8 Oct 2014 </span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:20%;\"><br /></p><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> <span style=\" font-weight:600; color:#ff0000;\">[DUE]</span> Do some writeup on IE2101 midterm deliverables</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> <span style=\" font-weight:600; color:#ff0000;\">[DUE]</span> Attempt to compile CS2103 maybe after PC1431</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Watch anime</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Play piano</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> <span style=\" font-weight:600; color:#0000ff;\">[7pm]</span> Have dinner with blah blah blah</li><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> <span style=\" font-weight:600; color:#0000ff;\">[7pm - 8pm]</span> Watch TV</li><p style=\" margin-top:25px; margin-bottom:0px; margin-left:2px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">Thurs, 9 Oct 2014 </span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:20%;\"><br /></p><li style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Screw the CS2103 demo!</li></ol></body></html>";
	
	State somestate = LogicExecutor::getNewState("/load");
	updateView(somestate);

}

AnotherGUI::~AnotherGUI()
{

}

void AnotherGUI::connectAllSlots() {
	QObject* declarativeMain;
	declarativeMain = ui.buttonUndo->rootObject();
	connect(declarativeMain, SIGNAL(buttonClick()), _myStorage, SLOT(GUIUndo()));
	declarativeMain = ui.buttonRedo->rootObject();
	connect(declarativeMain, SIGNAL(buttonClick()), _myStorage, SLOT(GUIRedo()));
	declarativeMain = ui.buttonAgendaview->rootObject();
	connect(declarativeMain, SIGNAL(buttonClick()), _myStorage, SLOT(toggleAgendaview()));
	declarativeMain = ui.buttonCalendarview->rootObject();
	connect(declarativeMain, SIGNAL(buttonClick()), _myStorage, SLOT(toggleCalandarview()));
	declarativeMain = ui.buttonEnter->rootObject();
	connect(declarativeMain, SIGNAL(buttonClick()), _myStorage, SLOT(commandLineInput()));
	connect(_myKeyPressEater, SIGNAL(enterPressed()), _myStorage, SLOT(commandLineInput()));
	//connect(ui.commandbox, SIGNAL(cursorPositionChanged()), this, SLOT(setSuggestionList()));
	connect(ui.searchbox, SIGNAL(textChanged()), _myStorage, SLOT(searchInput()));
	//connect(ui.commandbox, SIGNAL(textChanged()), _myStorage, SLOT(commandLineInput()));
	connect(_myStorage, SIGNAL(dataChanged(State)), this, SLOT(updateView(State)));
	return;
}

void AnotherGUI::updateView(State latestState) {
	string html = convertStateToHtml(latestState);
	ui.displaybox->setHtml(QString::fromStdString(html));
	return;
}

void AnotherGUI::createSuggestionList() {
	QMainWindow* hidden = new QMainWindow();
	_listView = new QListView(hidden);
    _listView->setObjectName(QStringLiteral("listView"));
    _listView->setGeometry(QRect(150, 300, 256, 192));
    _listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listView->setResizeMode(QListView::Adjust);
    _listView->setSelectionRectVisible(true);
	QStringListModel* model = new QStringListModel();
	QStringList List;
	List << "Clair de Lune" << "Reverie" << "Prelude" << "damn" << "This doesnt fit well lalala a a ajfadljdjdjjdjd inside";
	model->setStringList(List);
	_listView->setModel(model);
	_listView->setStyleSheet(QString::fromStdString("font: 11pt calibri"));

	_listView->setFixedHeight(getSuggestionListHeight(&List));
	_listView->setFixedWidth(getSuggestionListWidth(&List));
	_listView->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	//_listView->show();
	return;
}

int AnotherGUI::getSuggestionListHeight(QStringList* List) {
	return _listView->sizeHintForRow(0)*List->size()+10;
}

int AnotherGUI::getSuggestionListWidth(QStringList* List) {
	int i;
	int wtf = 0;
	double finalsize = 0;
	for (i=0; unsigned(i)<List->size(); i++) {
		if (List->at(i).size() > wtf) {
			wtf = List->at(i).size();
		}
	}
	finalsize = wtf*10.4;
	return finalsize;
}

void AnotherGUI::setSuggestionList() {
	QString whycannot = ui.commandbox->toPlainText();
	string llll = whycannot.toStdString();
	if (llll.size() > 10) {
		_listView->setGeometry(QRect(100, 700, 741, 81));
	}
	else {
		_listView->setGeometry(QRect(100, 700, 741, 81));
	}
	return;
}

vector<Task> AnotherGUI::specialSortByDeadline(vector<Task> toSort) {
	int i;
	int j;
	Task tempTask;
	for (i=0; unsigned(i)<toSort.size(); i++) {
		for (j=i+1; unsigned(j)<toSort.size(); j++) {
			if (toSort[j].getTaskDeadline() < toSort[i].getTaskDeadline()) {
				tempTask = toSort[j];
				toSort[j] = toSort[i];
				toSort[i] = tempTask;
			}
		}
	}
	return toSort;
}


string AnotherGUI::convertStateToHtml(State inputState) {
	
	int i; 
	int j;
	vector<Task> watashino;
	vector<Task> timedtasks = inputState.getTimedTasks();
	vector<Task> floatingg = inputState.getFloatingTasks();
	vector<ptime> alltasktimes;
	for (i=0; unsigned(i)<timedtasks.size(); i++) {
		watashino.push_back(timedtasks[i]);
		alltasktimes.push_back(timedtasks[i].getTaskStartTime());
	}
	vector<Task> deadlinetasks = inputState.getDeadlineTasks();
	vector<ptime> deadlinetasktimes;
	for (i=0; unsigned(i)<deadlinetasks.size(); i++) {
		watashino.push_back(deadlinetasks[i]);
		alltasktimes.push_back(deadlinetasks[i].getTaskDeadline());
	}
	
	for (i=0; unsigned(i)<watashino.size(); i++) {
		for (j=i+1; unsigned(j)<watashino.size(); j++) {
			bool swap = false;
			if (alltasktimes[j].date() < alltasktimes[i].date()) {
				swap = true;
			}
			else if (alltasktimes[j].date() == alltasktimes[i].date()) {
				if ((watashino[j].getTaskType() == 2) && (watashino[i].getTaskType() == 1)) {
					swap = true;
				}
				else if ((watashino[j].getTaskType() == 1) && (watashino[i].getTaskType() == 1)) {
					if (alltasktimes[j] < alltasktimes[i]) {
						swap = true;
					}
				}
			}
			if (swap) {
				ptime temptime = alltasktimes[j];
				alltasktimes[j] = alltasktimes[i];
				alltasktimes[i] = temptime;
				Task temptask = watashino[j];
				watashino[j] = watashino[i];
				watashino[i] = temptask;
			}
		}
	}

	string beginone = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Calibri'; font-size:11pt; font-weight:400; font-style:normal;\">";
	string preol = "<ol style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 2;\">";
	string firstpredate ="<p style=\" margin-top:25px; margin-bottom:0px; margin-left:2px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">";
	string firstpostdate = "</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:20%;\"><br /></p>";
	string predate = "<p style=\" margin-top:25px; margin-bottom:0px; margin-left:2px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline;\">";
	string postdate = "</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:20%;\"><br /></p>";
	string pretask = "<li style=\" font-family:'Calibri'; font-size:11pt;\" style=\" margin-top:0px; margin-bottom:4px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">";
	string posttask = "</li>";
	string postol = "</ol></body></html>";
	string thedue = " <span style=\" font-weight:600; color:#ff0000;\">[DUE]</span> ";
	string total = beginone + preol;
	
	bool gotfloating = floatingg.size() != 0;
	bool gotwatashi = watashino.size() != 0;
	ptime currentptime;

	if (gotfloating) {
		total += firstpredate + "Floating Tasks!" + firstpostdate;
		for (i=0; unsigned(i)<floatingg.size(); i++) {
			total += pretask + floatingg[i].getTaskName() + posttask;
		}
	}

	if (gotwatashi) {
		currentptime = currentptime = alltasktimes[0];		

		if (!gotfloating) {
			total += firstpredate + changeDateToString(currentptime) + firstpostdate;
		}
		else {
			total += predate + changeDateToString(currentptime) + postdate;
		}

		for (i=0; unsigned(i)<watashino.size(); i++) {
			if (alltasktimes[i].date() == currentptime.date()) {
				string showtime = "";
				if (watashino[i].getTaskType() == 1) {
					showtime = getShowTime(watashino[i].getTaskStartTime(), watashino[i].getTaskEndTime());
					total += pretask + showtime + watashino[i].getTaskName() + posttask;
				}	
				else if (watashino[i].getTaskType() == 2) {
					total += pretask + thedue + showtime + watashino[i].getTaskName() + posttask;
				}
			}
			else {
				total += predate + changeDateToString(alltasktimes[i]) + postdate;
				string showtime = "";
				if (watashino[i].getTaskType() == 1) {
					showtime = getShowTime(watashino[i].getTaskStartTime(), watashino[i].getTaskEndTime());
					total += pretask + showtime + watashino[i].getTaskName() + posttask;
				}	
				else if (watashino[i].getTaskType() == 2) {
					total += pretask + thedue + showtime + watashino[i].getTaskName() + posttask;
				}
			}
			currentptime = alltasktimes[i];
		}
	}

	vector<Task> alllll = floatingg;
	for (i=0; unsigned(i)<watashino.size(); i++) {
		alllll.push_back(watashino[i]);
	}
	_myStorage->setlist(alllll);
	total += postol;

	return total;
}

vector<Task> AnotherGUI::sortTasksByDate(vector<Task> toSort) {
	int i;
	int j;
	Task tempTask;
	for (i=0; unsigned(i)<toSort.size(); i++) {
		for (j=i+1; unsigned(j)<toSort.size(); j++) {
			if (toSort[j].getTaskStartTime() < toSort[i].getTaskStartTime()) {
				tempTask = toSort[j];
				toSort[j] = toSort[i];
				toSort[i] = tempTask;
			}
		}
	}
	return toSort;
}

int AnotherGUI::getNoOfIndexes() {
	return _size;
}

string AnotherGUI::changeDayToDay(int day) {
	if (day == 0) {
		return "Mon";
	}
	else if (day == 1) {
		return "Tues";
	}
	else if (day == 2) {
		return "Wed";
	}
	else if (day == 3) {
		return "Thurs";
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

string AnotherGUI::changeMonthToMonth(int month) {
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

string AnotherGUI::changeDateToString(ptime x) {
	string everything = "";
	string theyear = to_string(x.date().year());
	string themonth = changeMonthToMonth(x.date().month());
	string theday = changeDayToDay(x.date().day_of_week());
	string thedayy = to_string(x.date().day());
	everything = theday + ", " + thedayy + " " + themonth + " " + theyear;
	return everything;
}

string AnotherGUI::getShowTime(ptime one, ptime two) {
	string lalala = "";
	string precolor = " <span style=\" font-weight:600; color:#0000ff;\">";
	string postcolor = "</span> ";
	if (two == not_a_date_time) {
		lalala = precolor + "[" + getampm(one) + "] " + postcolor;
	}
	else {
		if (one.date() == two.date()) {
			lalala = precolor + "[" + getampm(one) + " - " + getampm(two) + "]" + postcolor;
		}
		else {
			lalala = precolor + "[" + getampm(one) + " - " + getampm(two) + " " + to_string(two.date().day()) + " " + changeMonthToMonth(two.date().month()) + " " + to_string(two.date().year()) + "]" + postcolor;
		}
	}
	return lalala;
}

string AnotherGUI::getampm(ptime one) {
	string ampm = "am";
	int timetoprint;
	if ((one.time_of_day().hours() - 12) >= 0) {
		ampm = "pm";
		if (one.time_of_day().hours() != 12) {
			timetoprint = one.time_of_day().hours() - 12;
		}
		else {
			timetoprint = 12;
		}
	}
	else {
		timetoprint = one.time_of_day().hours();
	}
	string all = to_string(timetoprint) + ampm;
	return all;
}