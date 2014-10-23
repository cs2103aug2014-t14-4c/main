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
	taskDatetimeString = ""; 
	taskName = "";
	taskTags = "";
	taskIsDone = ""; 
}

vector<string> StorageConverter::convertTaskToString(Task taskToConvert){

	//will convert individual task attributes to strings
	//note: order of conversion important for the developer, not for the user
	//clear initial content
	taskStringAttributes.clear(); 
	//ensures that the taskStringAttribute is empty
	assert(taskStringAttributes.empty());
	
	//string parameters after conversion
	string taskStartDatetime = convertTaskPtimeToString(taskToConvert.getTaskStartTime());
	string taskEndDatetime = convertTaskPtimeToString(taskToConvert.getTaskEndTime());
	string taskDeadline = convertTaskPtimeToString(taskToConvert.getTaskDeadline());
	string taskName = convertTaskNameToString(taskToConvert);
	string taskTags = convertTaskTagVectorToString(taskToConvert.getTaskTags());
	string taskIsDone = convertTaskBoolToString(taskToConvert.getTaskIsDone());
	
	//storing each string in a vector
	taskStringAttributes.push_back(TITLE_TASKSTARTDATETIME + taskStartDatetime);
	taskStringAttributes.push_back(TITLE_TASKENDDATETIME + taskEndDatetime); 
	taskStringAttributes.push_back(TITLE_TASKDEADLINE + taskDeadline);
	taskStringAttributes.push_back(TITLE_TASKNAME + taskName);
	taskStringAttributes.push_back(TITLE_TASKTAGS + taskTags);
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
	convertStringStartDatetimeToTask();
	taskAttributeIterator++; 

	//2. convert endtime
	taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKENDDATETIME.size());
	convertStringEndDatetimeToTask();
	taskAttributeIterator++; 

	//3. convert task deadline
	taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKDEADLINE.size());
	convertStringDeadlineToTask(); 
	taskAttributeIterator++; 

	//4. convert task name
	taskName = (*taskAttributeIterator).substr(TITLE_TASKNAME.size());
	convertedTask.setTaskName(taskName);
	taskAttributeIterator++; 

	//5. convert task tags 
	taskTags = (*taskAttributeIterator).substr(TITLE_TASKTAGS.size());
	convertStringTasktagToTask();
	taskAttributeIterator++; 
	
	//6. convert isDone, isDone initialized false, thus only call if it's true
	taskIsDone = (*taskAttributeIterator).substr(TITLE_TASKISDONE.size());
	convertStringIsdoneToTask();

	//return the converted individual task
	return convertedTask;
}

//convert boolean to string 
string StorageConverter::convertTaskBoolToString(bool boolToConvert){
	stringstream converter; 
	converter << boolToConvert;
	return converter.str();
}

//convert ptime to string
string StorageConverter::convertTaskPtimeToString(ptime myDatetime){
	string convertedPtimeString = to_iso_string(myDatetime); 
	return convertedPtimeString;
}

//convert duration to string, note: not in use at the moment
string StorageConverter::convertTaskPtimeDurationToString(time_duration myDuration){
	string convertedPtimeDuration = to_iso_string(myDuration);
	return convertedPtimeDuration;
}

//convert vector<string> of task tags to string
string StorageConverter::convertTaskTagVectorToString(vector<string> taskTags){
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

string StorageConverter::convertTaskNameToString(Task taskToConvert){
	taskName = taskToConvert.getTaskName();
	return taskName; 
}

//convert taskTagstring to vector<string>
vector<string> StorageConverter::convertTaskTagStringToVector(string tagString){
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
void StorageConverter::convertStringIsdoneToTask(){
	//converting string to boolean
	if(taskIsDone=="1"){
		convertedTask.setTaskIsDone();
	}
	else if(taskIsDone=="0"){
	}
	return;
}

void StorageConverter::convertStringStartDatetimeToTask(){
	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskStartTime(not_a_date_time); 
	} else {
		ptime taskStartTime(from_iso_string(taskDatetimeString));
		convertedTask.setTaskStartTime(taskStartTime);
	}
	return; 
}

void StorageConverter::convertStringEndDatetimeToTask(){
	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskEndTime(not_a_date_time); 
	} else {
		ptime taskEndTime(from_iso_string(taskDatetimeString));
		convertedTask.setTaskEndTime(taskEndTime);
	}
	return;
}

void StorageConverter::convertStringDeadlineToTask(){
	if (taskDatetimeString == NOT_A_DATETIME){
		convertedTask.setTaskDeadline(not_a_date_time); 
	} else {
		ptime taskDeadline(from_iso_string(taskDatetimeString));
		convertedTask.setTaskDeadline(taskDeadline);
	}
	return;
}

void StorageConverter::convertStringTasktagToTask(){
	
	vector<string> taskTagVector = convertTaskTagStringToVector(taskTags);
	convertedTask.setTaskTags(taskTagVector);

	return; 
}