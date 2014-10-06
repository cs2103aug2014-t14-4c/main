#include <iostream>
#include <vector>
#include <string>
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandEdit.h"
#include "CommandDone.h"
#include "CommandSearch.h"
#include "CommandClear.h"
#include "CommandUndo.h"
#include "CommandRedo.h"
#include "LogicData.h"
#include "State.h"
#include "Task.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

void printtask(Task mytask) {
	ptime start = mytask.getTaskStartTime();
	ptime end = mytask.getTaskEndTime();
	ptime deadline = mytask.getTaskDeadline();
	time_duration duration = mytask.getTaskDuration();
	string name = mytask.getTaskName();
	int index = mytask.getTaskIndex();
	int tasktype = mytask.getTaskType();
	bool isdone = mytask.getTaskIsDone();
	cout << "Name: " << name << endl;
	cout << "StartTime: " << to_simple_string(start) << endl;
	cout << "EndTime: " << to_simple_string(end) << endl;
	cout << "Deadline: " << to_simple_string(deadline) << endl;
	cout << "Duration: " << to_simple_string(duration) << endl;
	cout << "Index: " << index << endl;
	cout << "Type: " << tasktype << endl;
	cout << "Done?: " << isdone << endl;
	cout << endl;
	return;
}

void printstate(State mystate) {
	vector<Task> all = mystate.getAllTasks();
	int i;
	for (i=0; unsigned(i)<all.size(); i++) {
		printtask(all[i]);
	}
	cout << mystate.getUserMessage() << endl << endl;
	return;
}

int main() {

	//ptime(date(2000, 10, 10), hours(1));

	Command* abc = new CommandAdd;
	Task taskone;
	taskone.setTaskName("taskone");
	taskone.setTaskStartTime(ptime(date(2014, 10, 5), hours(5)));
	taskone.setTaskEndTime(ptime(date(2014, 10, 5), hours(7)));
	taskone.setTaskDeadline(ptime(date(2014, 10, 6)));
	Task tasktwo;
	tasktwo.setTaskName("tasktwo");
	tasktwo.setTaskStartTime(ptime(date(2014, 10, 5), hours(20)));
	tasktwo.setTaskEndTime(ptime(date(2014, 10, 5), hours(22)));
	//tasktwo.setTaskDeadline(ptime(date(2014, 10, 6)));
	State mystate;
	mystate.addTask(taskone);
	mystate.addTask(tasktwo);
	printstate(mystate);
	LogicData::fakeinitiate(mystate);

	Task taskthree;
	taskthree.setTaskName("taskthree");
	taskthree.setTaskStartTime(ptime(date(2014, 10, 6), hours(10)));
	taskthree.setTaskEndTime(ptime(date(2014, 10, 6), hours(11)));
	taskthree.setTaskDeadline(ptime(date(2014, 10, 5)));
	abc->setCurrentTask(taskthree);
	abc->execute();

	Task taskfour;
	taskfour.setTaskName("taskfour");
	taskfour.setTaskDeadline(ptime(date(2014, 10, 10)));
	vector<string> lalatags;
	lalatags.push_back("oa");
	lalatags.push_back("iab");
	taskfour.setTaskTags(lalatags);
	Command* bcd = new CommandEdit;
	bcd->setTaskIndex(1);
	bcd->setCurrentTask(taskfour);
	bcd->execute();

	Command* doo = new CommandDone;
	doo->setTaskIndex(0);
	doo->execute();

	Command* ss = new CommandSearch;
	ss->setSearchKeyword("task#o#i");
	ss->execute();

	Command* ooi = new CommandClear;
	ooi->execute();

	Command* backk = new CommandUndo;
	backk->execute();
	backk->execute();
	backk->execute();
	backk->execute();

	Command* ahead = new CommandRedo;
	ahead->execute();

	vector<Command*> something = LogicData::getCommandHistory();

	mystate = LogicData::getViewState();
	printstate(mystate);
	cout << something.size() << " " << LogicData::getCurrentCommandHistoryIndex() << endl;

	int i;
	cin >> i;
	return 0;
}