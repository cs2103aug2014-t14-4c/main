#pragma once
#include <string>
#include <vector>
#include "boost\date_time.hpp"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Task {
	public:
		Task(void);
		bool isOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);
		int getTaskType();
		
		int getTaskIndex();
		ptime getTaskStartDatetime();
		ptime getTaskEndDatetime();
		ptime getTaskDeadline();
		int getTaskDuration();
		string getTaskName();
		string getTaskDetails();
		vector<string> getTaskTags();
		bool getIsDone();

		void setTaskStartDatetime(ptime datetimeToSet);
		void setTaskEndDatetime(ptime datetimeToSet);
		void setTaskDeadline(ptime datetimeToSet);
		void setTaskDuration(int durationToSet);
		void setTaskName(string nameToSet);
		void setTaskDetails(string detailsToSet);
		void setTaskTags(vector<string> tagsToSet);
		void setIsDone();
		void setIsNotDone();

	private:
		ptime _taskStartDateTime;
		ptime _taskEndDateTime;
		ptime _taskDeadline;
		int _taskDuration;
		string _taskName;
		string _taskDetails;
		vector<string> _taskTags;
		int _taskIndex;
		bool _isDone;

};

