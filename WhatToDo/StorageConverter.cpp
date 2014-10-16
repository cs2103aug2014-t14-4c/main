#include "StorageConverter.h"

string StorageConverter::TITLE_TASKSTARTDATETIME = "Start Datetime: ";
string StorageConverter::TITLE_TASKENDDATETIME = "End Datetime: ";
string StorageConverter::TITLE_TASKDEADLINE = "Task Deadline: ";
string StorageConverter::TITLE_TASKNAME = "Task Name: ";
string StorageConverter::TITLE_TASKTAGS = "Task Tags: ";
string StorageConverter::TITLE_TASKISDONE = "Task isDone Status: ";

string StorageConverter::NOT_A_DATETIME = "not-a-date-time"; 

//some are commented out as they are not implemented at this moment

StorageConverter::StorageConverter(void){
	taskDatetimeString= "";
}

vector<string> StorageConverter::convertTaskToString(Task taskToConvert){

	
	//will convert individual task attributes to strings
	//note: order of conversion important for the developer, not for the user
	//clear initial content
	taskStringAttributes.clear(); 
	//ensures that the taskStringAttribute is empty
	assert(taskStringAttributes.empty());
	
	string taskStartDatetime =  ptimeToStringConverter(taskToConvert.getTaskStartTime());
	string taskEndDatetime = ptimeToStringConverter(taskToConvert.getTaskEndTime());
	string taskDeadline = ptimeToStringConverter(taskToConvert.getTaskDeadline());
	string taskName = taskToConvert.getTaskName(); 
	string taskTags = taskTagVectorToStringConverter(taskToConvert.getTaskTags());
	string taskIsDone = boolConverter(taskToConvert.getTaskIsDone());
	//for each task, convert each attribute of a task into a string
	
	//1. get start datetime
	taskStringAttributes.push_back(TITLE_TASKSTARTDATETIME + taskStartDatetime);

	//2. get end datetime
	taskStringAttributes.push_back(TITLE_TASKENDDATETIME + taskEndDatetime); 

	//3. get task deadline 
	taskStringAttributes.push_back(TITLE_TASKDEADLINE + taskDeadline);

	//4. get taskName
	taskStringAttributes.push_back(TITLE_TASKNAME + taskName);

	//5. get task tags
	taskStringAttributes.push_back(TITLE_TASKTAGS + taskTags);
	
	//6. getIsdone
	taskStringAttributes.push_back(TITLE_TASKISDONE + taskIsDone); 

	//finally write the whole vector of string into file
	return taskStringAttributes; 
}

Task StorageConverter::convertStringToTask(vector<string> stringToConvert){

	vector<string>::iterator taskAttributeIterator = stringToConvert.begin(); 
	assert(&taskAttributeIterator != NULL); 
	
	//get the substring which is input for conversion
	//convert individual substrings into task attributes
	//use task setter methods to "Create" the task

	//1. convert startime
	taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKSTARTDATETIME.size());
	
	assert(taskDatetimeString.size()==15);

	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskStartTime(not_a_date_time); 
	} else {
		ptime taskStartTime(from_iso_string(taskDatetimeString));
		convertedTask.setTaskStartTime(taskStartTime);
	}
	taskAttributeIterator++; 

	//2. convert endtime
	taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKENDDATETIME.size());
	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskEndTime(not_a_date_time); 
	} else {
		ptime taskEndTime(from_iso_string(taskDatetimeString));
		convertedTask.setTaskEndTime(taskEndTime);
	}
	taskAttributeIterator++; 

	//3. convert task deadline
	taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKDEADLINE.size());
	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskDeadline(not_a_date_time); 
	} else {
		ptime taskDeadLine(from_iso_string(taskDatetimeString));
		convertedTask.setTaskDeadline(taskDeadLine); 
	}
	taskAttributeIterator++; 

	//4. convert task name
	string taskName = (*taskAttributeIterator).substr(TITLE_TASKNAME.size());
	convertedTask.setTaskName(taskName);
	taskAttributeIterator++; 

	//5. convert task tags 
	string taskTags = (*taskAttributeIterator).substr(TITLE_TASKTAGS.size());
	vector<string> taskTagVector = taskTagStringToVectorConverter(taskTags);
	convertedTask.setTaskTags(taskTagVector);
	taskAttributeIterator++; 
	
	//6. convert isDone, isDone initialized false, thus only call if it's true
	string taskIsDoneString = (*taskAttributeIterator).substr(TITLE_TASKISDONE.size());
	bool taskIsDone = taskStringToBooleanConverter(taskIsDoneString);
	
	if(taskIsDone) {
		convertedTask.setTaskIsDone();
	}

	//return the converted individual task
	return convertedTask;
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

