#include "StorageConverter.h"
#include <string>
#include <vector>
#include "Task.h"
#include <sstream>
#include <boost/regex.hpp>

using namespace std; 

	string _getTaskType = "_taskType: ";
	string _getTaskStartDateime = "_taskStartDatetime: ";
	string _getTaskEndDatetime = "_taskEndDatetime: ";
	string _getTaskDeadline = "_taskDeadline: ";
	string _getTaskDuration = "_taskDuration: ";
	string _getTaskName = "_taskName: ";
	string _getTaskDetails = "_taskDetails: ";
	string _getTaskTags = "_taskTags: ";
	string _getTaskIndex = "_taskIndex: ";
	string _getTaskIsDone = "_isDone: ";

StorageConverter::StorageConverter(void){
}

vector<string> StorageConverter::convertTaskToString(Task taskToConvert){
	string myConvertedString;
	vector<string> myStringParameters;

	string taskType = to_string(taskToConvert.getTaskType()); 
	string taskStartDatetime =  ptimeToStringConverter(taskToConvert.getTaskStartTime());
	string taskEndDatetime = ptimeToStringConverter(taskToConvert.getTaskEndTime());
	string taskDeadline = ptimeToStringConverter(taskToConvert.getTaskDeadline());
	string taskDuration = ptimeDurationToStringConverter(taskToConvert.getTaskDuration());
	string taskName = taskToConvert.getTaskName(); 
	string taskDetails = taskToConvert.getTaskDetails(); 
	string taskIndex = to_string(taskToConvert.getTaskIndex());
	string taskTags = taskTagVectorToStringConverter(taskToConvert.getTaskTags());
	string taskIsDone = boolConverter(taskToConvert.getTaskIsDone());
	//for each task, convert each attribute of a task into a string
	
	//1. getTaskType
	myStringParameters.push_back(_getTaskType + taskType + "\n");
	
	//2. get start datetime 
	myStringParameters.push_back(_getTaskStartDateime + taskStartDatetime + "\n");

	//3. get end datetime
	myStringParameters.push_back(_getTaskEndDatetime + taskEndDatetime + "\n"); 

	//4. get task deadline 
	myStringParameters.push_back(_getTaskDeadline + taskDeadline + "\n");

	//5. get taskName
	myStringParameters.push_back(_getTaskName + taskName + "\n");

	//6. get taskDuration
	//myStringParameters.push_back(_getTaskDuration + taskDuration + "\n");

	//6. get task details
	//myStringParameters.push_back(_getTaskDetails + taskDetails + "\n");
	
	//6. get task tags
	myStringParameters.push_back(_getTaskTags + taskTags +"\n");
	
	//7. get task index
	//myStringParameters.push_back(_getTaskIndex + taskIndex + "\n"); 
	
	//7. getIsdone
	myStringParameters.push_back(_getTaskIsDone + taskIsDone + "\n"); 

	//finally write the whole vector of string into file
	return myStringParameters; 
}

Task StorageConverter::convertStringToTask(vector<string> stringToConvert){
	Task myConvertedTask;
	vector<string>::iterator myIndividualAttributeIterator = stringToConvert.begin(); 
	
	//1. convert task type
	string catenatedTaskType = (*myIndividualAttributeIterator).substr(_getTaskType.size()); //this gives some weird error??
	int taskType  = atoi(catenatedTaskType.c_str());
	myConvertedTask.setTaskIndex(taskType); 
	myIndividualAttributeIterator += 1; 

	//2. convert startime
	ptime startTime = from_iso_string((*myIndividualAttributeIterator).substr(_getTaskStartDateime.size()));
	myConvertedTask.setTaskStartTime(startTime); 
	myIndividualAttributeIterator += 1; 

	//3. convert endtime
	ptime endTime = from_iso_string((*myIndividualAttributeIterator).substr(_getTaskEndDatetime.size()));
	myConvertedTask.setTaskEndTime(endTime);
	myIndividualAttributeIterator += 1; 

	//4. convert task deadline
	ptime deadLine = from_iso_string((*myIndividualAttributeIterator).substr(_getTaskDeadline.size()));
	myConvertedTask.setTaskDeadline(deadLine); 
	myIndividualAttributeIterator += 1; 

	//5. convert task duration
	/*time_duration taskDuration = duration_from_string((*myIndividualAttributeIterator).substr(_getTaskDuration.size())); 
	myConvertedTask.setTaskDuration(taskDuration);
	myIndividualAttributeIterator += 1; */

	//5. convert task name
	string taskName = (*myIndividualAttributeIterator).substr(_getTaskName.size());
	myConvertedTask.setTaskName(taskName);
	myIndividualAttributeIterator += 1; 

	////7. convert task details 
	//string taskDetails = (*myIndividualAttributeIterator).substr(_getTaskDetails.size());
	//myConvertedTask.setTaskDetails(taskDetails);
	//myIndividualAttributeIterator += 1; 

	//6. convert task tags 
	string taskTags = (*myIndividualAttributeIterator).substr(_getTaskTags.size());
	vector<string> taskTagVector = taskTagStringToVectorConverter(taskTags);
	myConvertedTask.setTaskTags(taskTagVector);
	myIndividualAttributeIterator +=1; 

	//7. convert task index, NOTE task indexis the unique index only for searching function
	/*string catenatedIndexString = (*myIndividualAttributeIterator).substr(_getTaskIndex.size()); 
	int taskIndex = atoi(catenatedIndexString.c_str()); 
	myConvertedTask.setTaskIndex(taskIndex); 
	myIndividualAttributeIterator +=1;*/
	
	//7. convert isDone
	string taskIsDoneString = (*myIndividualAttributeIterator).substr(_getTaskIsDone.size());
	bool taskIsDone = taskStringToBooleanConverter(taskIsDoneString);
	
	if(taskIsDone) {
		myConvertedTask.setTaskIsDone();
	}

	//return the converted individual task
	return myConvertedTask;
}

string StorageConverter::boolConverter(bool boolToConvert){
	stringstream converter; 
	converter << boolToConvert;
	return converter.str();
}

string StorageConverter::ptimeToStringConverter(ptime myDatetime){
	string convertedPtimeString; 
	convertedPtimeString = to_iso_string(myDatetime); 
	return convertedPtimeString;
}

string StorageConverter::ptimeDurationToStringConverter(time_duration myDuration){
	
	string convertedPtimeDuration = to_iso_string(myDuration);
	return convertedPtimeDuration;
}

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

bool StorageConverter::taskStringToBooleanConverter(string boolString){
	//converting string to boolean
	bool isDone; 
	if(boolString=="1"){
		isDone = true; 
	}
	else if(boolString=="0"){
		isDone = false; 
	}
	return isDone; 
}