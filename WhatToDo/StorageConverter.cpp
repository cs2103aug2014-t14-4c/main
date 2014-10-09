#include "StorageConverter.h"
#include <string>
#include <vector>
#include "Task.h"
#include <sstream>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std; 
//some are commented out as they are not implemented at this moment
string StorageConverter::_getTaskType = "_taskType: ";
string StorageConverter::_getTaskStartDatetime = "_taskStartDatetime: ";
string StorageConverter::_getTaskEndDatetime = "_taskEndDatetime: ";
string StorageConverter::_getTaskDeadline = "_taskDeadline: ";
//string _getTaskDuration = "_taskDuration: ";
string StorageConverter::_getTaskName = "_taskName: ";
//string _getTaskDetails = "_taskDetails: ";
string StorageConverter::_getTaskTags = "_taskTags: ";
//string _getTaskIndex = "_taskIndex: ";
string StorageConverter::_getTaskIsDone = "_isDone: ";

StorageConverter::StorageConverter(void){
}

vector<string> StorageConverter::convertTaskToString(Task taskToConvert){
	string myConvertedString;
	vector<string> myStringParameters; //to store all the converted strings
	myStringParameters.clear(); //safety net
	//will convert individual task attributes to strings
	//note: order of conversion important for the developer, not for the user

	//string taskType = to_string(taskToConvert.getTaskType()); 
	string taskStartDatetime =  ptimeToStringConverter(taskToConvert.getTaskStartTime());
	string taskEndDatetime = ptimeToStringConverter(taskToConvert.getTaskEndTime());
	string taskDeadline = ptimeToStringConverter(taskToConvert.getTaskDeadline());
	//string taskDuration = ptimeDurationToStringConverter(taskToConvert.getTaskDuration());
	string taskName = taskToConvert.getTaskName(); 
	//string taskDetails = taskToConvert.getTaskDetails(); 
	//string taskIndex = to_string(taskToConvert.getTaskIndex());
	string taskTags = taskTagVectorToStringConverter(taskToConvert.getTaskTags());
	string taskIsDone = boolConverter(taskToConvert.getTaskIsDone());
	//for each task, convert each attribute of a task into a string
	
	//1. getTaskType
	//myStringParameters.push_back(_getTaskType + taskType);
	
	//2. get start datetime
	
	myStringParameters.push_back(_getTaskStartDatetime + taskStartDatetime);



	//3. get end datetime
	myStringParameters.push_back(_getTaskEndDatetime + taskEndDatetime); 

	//4. get task deadline 
	myStringParameters.push_back(_getTaskDeadline + taskDeadline);

	//5. get taskName
	myStringParameters.push_back(_getTaskName + taskName);

	//6. get taskDuration
	//myStringParameters.push_back(_getTaskDuration + taskDuration + "\n");

	//6. get task details
	//myStringParameters.push_back(_getTaskDetails + taskDetails + "\n");
	
	//6. get task tags
	myStringParameters.push_back(_getTaskTags + taskTags);
	
	//7. get task index
	//myStringParameters.push_back(_getTaskIndex + taskIndex + "\n"); 
	
	//7. getIsdone
	myStringParameters.push_back(_getTaskIsDone + taskIsDone); 

	//finally write the whole vector of string into file
	return myStringParameters; 
}

Task StorageConverter::convertStringToTask(vector<string> stringToConvert){
	Task myConvertedTask;
	vector<string>::iterator myIndividualAttributeIterator = stringToConvert.begin(); 
	
	//get the substring which is input for conversion
	//convert individual substrings into task attributes
	//use task setter methods to "Create" the task

	//1. convert task type
	//string concatenatedTaskType = (*myIndividualAttributeIterator).substr(_getTaskType.size()); //this gives some weird error??
	//int taskType  = atoi(concatenatedTaskType.c_str());
	//myConvertedTask.setTaskT(taskType); 
	//myIndividualAttributeIterator += 1; 

	//2. convert startime
	string later = "";

	later = (*myIndividualAttributeIterator).substr(_getTaskStartDatetime.size());
	if (later == "not-a-date-time") {
		myConvertedTask.setTaskStartTime(not_a_date_time); 
	}
	else {
		ptime startTime(from_iso_string((*myIndividualAttributeIterator).substr(_getTaskStartDatetime.size())));
		myConvertedTask.setTaskStartTime(startTime); 
	}
	myIndividualAttributeIterator++; 

	////3. convert endtime
	later = (*myIndividualAttributeIterator).substr(_getTaskEndDatetime.size());
	if (later == "not-a-date-time") {
		myConvertedTask.setTaskEndTime(not_a_date_time); 
	}
	else {
		ptime endTime(from_iso_string((*myIndividualAttributeIterator).substr(_getTaskEndDatetime.size())));
		myConvertedTask.setTaskEndTime(endTime);
	}
	myIndividualAttributeIterator++; 

	//4. convert task deadline
	later = (*myIndividualAttributeIterator).substr(_getTaskDeadline.size());
	if (later == "not-a-date-time") {
		myConvertedTask.setTaskDeadline(not_a_date_time); 
	}
	else {
		ptime deadLine(from_iso_string((*myIndividualAttributeIterator).substr(_getTaskDeadline.size())));
		myConvertedTask.setTaskDeadline(deadLine); 
	}
	myIndividualAttributeIterator++; 

	//5. convert task duration
	/*time_duration taskDuration = duration_from_string((*myIndividualAttributeIterator).substr(_getTaskDuration.size())); 
	myConvertedTask.setTaskDuration(taskDuration);
	myIndividualAttributeIterator += 1; */

	//5. convert task name
	string taskName = (*myIndividualAttributeIterator).substr(_getTaskName.size());
	myConvertedTask.setTaskName(taskName);
	myIndividualAttributeIterator++; 

	//7. convert task details 
	//string taskDetails = (*myIndividualAttributeIterator).substr(_getTaskDetails.size());
	//myConvertedTask.setTaskDetails(taskDetails);
	//myIndividualAttributeIterator += 1; 

	//6. convert task tags 
	string taskTags = (*myIndividualAttributeIterator).substr(_getTaskTags.size());
	vector<string> taskTagVector = taskTagStringToVectorConverter(taskTags);
	myConvertedTask.setTaskTags(taskTagVector);
	myIndividualAttributeIterator++; 

	//7. convert task index, NOTE task index is the unique index only for searching function
	/*string catenatedIndexString = (*myIndividualAttributeIterator).substr(_getTaskIndex.size()); 
	int taskIndex = atoi(catenatedIndexString.c_str()); 
	myConvertedTask.setTaskIndex(taskIndex); 
	myIndividualAttributeIterator +=1;*/
	
	//7. convert isDone, isDone initialized false, thus only call if it's true
	string taskIsDoneString = (*myIndividualAttributeIterator).substr(_getTaskIsDone.size());
	bool taskIsDone = taskStringToBooleanConverter(taskIsDoneString);
	
	if(taskIsDone) {
		myConvertedTask.setTaskIsDone();
	}

	//return the converted individual task
	return myConvertedTask;
}

//convert boolean to string 
string StorageConverter::boolConverter(bool boolToConvert){
	stringstream converter; 
	converter << boolToConvert;
	return converter.str();
}

//convert ptime to string
string StorageConverter::ptimeToStringConverter(ptime myDatetime){
	string convertedPtimeString; 
	convertedPtimeString = to_iso_string(myDatetime); 
	return convertedPtimeString;
}

//convert duration to string, note: not in use at the moment
string StorageConverter::ptimeDurationToStringConverter(time_duration myDuration){
	
	string convertedPtimeDuration = to_iso_string(myDuration);
	return convertedPtimeDuration;
}

//convert vector<string> of task tags to string
string StorageConverter::taskTagVectorToStringConverter(vector<string> taskTags){
	string tagString = "";
	//read through all the vector of strings for task tags 
	//concatenate the individual string
	//return the whole string
	vector<string>::iterator taskTagIterator = taskTags.begin();
	while(taskTagIterator!=taskTags.end()){
		tagString = tagString + *taskTagIterator + " ";
		taskTagIterator++;
	}

	return tagString;
}

//convert taskTagstring to vector<string>
vector<string> StorageConverter::taskTagStringToVectorConverter(string tagString){
	//pass in the string to a iss object
	//read individual substr delimited by whitespace
	//push into the tagVector
	istringstream tagStringStream(tagString); 
	string individualTag; 
	vector<string> tagVector;
	
	while(tagStringStream>>individualTag){
		tagVector.push_back(individualTag);
	}

	return tagVector;
}

//convert string to bool 
bool StorageConverter::taskStringToBooleanConverter(string boolString){
	//converting string to boolean
	bool isDone = false; 
	if(boolString=="1"){
		isDone = true; 
	}
	else if(boolString=="0"){
		isDone = false; 
	}
	return isDone; 
}