#include "StorageConverter.h"
#include <string>
#include <vector>
#include "Task.h"
#include <sstream>
#include <boost/regex.hpp>

using namespace std; 

StorageConverter::StorageConverter(void)
{
}

string StorageConverter::convertTaskToString(Task taskToConvert){
	string myConvertedString;
	//set the order of the task attributes to be converted to string
	//[int gettasktype][Datetime getTaskStartDatetime][Datetime getTaskEndDatetime][Datetime getTaskDeadline]
	//[int getTaskDuration][string getTaskName][string getTaskDetails][vector<string> getTaskTags][int getTaskIndex]
	//[bool getIsDone]
	vector<string> myStringParameters;

	vector<string> taskTags = taskToConvert.getTaskTags();
	string taskTagString; 
	string boolToString; 

	vector<string>::iterator myTaskTagIterator = taskTags.begin(); 
	while(myTaskTagIterator != taskTags.end()){
		taskTagString = taskTagString + " " + *myTaskTagIterator;
		myTaskTagIterator++;
	}
	
	bool isDone = taskToConvert.getIsDone(); 
	boolToString = boolConverter(isDone);

	myStringParameters.push_back(to_string(taskToConvert.getTaskType()));
	//myStringParameters.push_back(tostring datetime);
	myStringParameters.push_back(to_string(taskToConvert.getTaskDuration()));
	myStringParameters.push_back(taskToConvert.getTaskName());
	myStringParameters.push_back(taskToConvert.getTaskDetails());
	myStringParameters.push_back(taskTagString);
	myStringParameters.push_back(to_string(taskToConvert.getTaskIndex()));
	myStringParameters.push_back(boolToString);
	myConvertedString =  "[" + to_string(taskToConvert.getTaskType()) + "]"  //+ Datetime stuff;
	+ "";
	return myConvertedString;
}

Task StorageConverter::convertStringToTask(string stringToConvert){
	Task myConvertedTask;
	
	return myConvertedTask;
}

string StorageConverter::boolConverter(bool boolToConvert){
	stringstream converter; 
	converter << boolToConvert;
	return converter.str();
}