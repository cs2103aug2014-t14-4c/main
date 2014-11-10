//@auher A0116278B
#include "StorageConverter.h"

StorageConverter::StorageConverter(void){
	_taskDatetimeString = ""; 
	_taskName = "";
	_taskTags = "";
	_taskIsDone = ""; 
	_logFileName = LOG_FILE_NAME; 
}

//will convert individual task attributes to strings
//note: order of conversion important for the developer, not for the user
//clear initial content
vector<string> StorageConverter::convertTaskToString(Task taskToConvert){

	_taskStringAttributes.clear(); 

	//string parameters after conversion
	string taskStartDatetime = convertTaskPtimeToString(taskToConvert.getTaskStartTime());
	string taskEndDatetime = convertTaskPtimeToString(taskToConvert.getTaskEndTime());
	string taskDeadline = convertTaskPtimeToString(taskToConvert.getTaskDeadline());
	string taskName = convertTaskNameToString(taskToConvert);
	string taskTags = convertTaskTagVectorToString(taskToConvert.getTaskTags());
	string taskIsDone = convertTaskBoolToString(taskToConvert.getTaskIsDone());
	
	//storing each string in a vector
	_taskStringAttributes.push_back(TITLE_TASKSTARTDATETIME + taskStartDatetime);
	_taskStringAttributes.push_back(TITLE_TASKENDDATETIME + taskEndDatetime); 
	_taskStringAttributes.push_back(TITLE_TASKDEADLINE + taskDeadline);
	_taskStringAttributes.push_back(TITLE_TASKNAME + taskName);
	_taskStringAttributes.push_back(TITLE_TASKTAGS + taskTags);
	_taskStringAttributes.push_back(TITLE_TASKISDONE + taskIsDone); 

	//finally write the whole vector of string into file
	return _taskStringAttributes; 
}

//handles the conversion from string to task attributes, function
//is futhered slapped into smaller subfunctions for each string conversion
//extraction of string -> conversion of string ->set Task parameters->
//return Task
Task StorageConverter::convertStringToTask(vector<string> stringToConvert) {
	Task convertedTask; 
	assert(&stringToConvert != NULL);
	vector<string>::iterator taskAttributeIterator = stringToConvert.begin(); 

	try{
		//1. convert startime
		_taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKSTARTDATETIME.size());
		convertStringStartDatetimeToTask(convertedTask);
		taskAttributeIterator++; 

		//2. convert endtime
		_taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKENDDATETIME.size());
		convertStringEndDatetimeToTask(convertedTask);
		taskAttributeIterator++; 

		//3. convert task deadline
		_taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKDEADLINE.size());
		convertStringDeadlineToTask(convertedTask); 
		taskAttributeIterator++; 

		//4. convert task name
		_taskName = (*taskAttributeIterator).substr(TITLE_TASKNAME.size());
		convertedTask.setTaskName(_taskName);
		taskAttributeIterator++; 

		//5. convert task tags 
		_taskTags = (*taskAttributeIterator).substr(TITLE_TASKTAGS.size());
		convertStringTasktagToTask(convertedTask);
		taskAttributeIterator++; 
	
		//6. convert isDone, isDone initialized false, thus only call if it's true
	
		_taskIsDone = (*taskAttributeIterator).substr(TITLE_TASKISDONE.size());
		convertStringIsdoneToTask(convertedTask);

		//return the converted individual task
		return convertedTask;
	} catch(exception&){
		throw;
	}
}

//convert ptime to string
string StorageConverter::convertTaskPtimeToString(ptime myDatetime){
	string convertedPtimeString = to_iso_string(myDatetime); 
	return convertedPtimeString;
}

string StorageConverter::convertTaskPtimeDurationToString(time_duration myDuration){
	string convertedPtimeDuration = to_iso_string(myDuration);
	return convertedPtimeDuration;
}

//convert boolean to string 
string StorageConverter::convertTaskBoolToString(bool boolToConvert){
	stringstream converter; 
	converter << boolToConvert;

	return converter.str();
}

//convert vector<string> of task tags to string
//read through all the vector of strings for task tags 
//concatenate the individual string
//return the whole string
string StorageConverter::convertTaskTagVectorToString(vector<string> taskTags){
	string tagString = "";
	vector<string>::iterator taskTagIterator = taskTags.begin();
	while(taskTagIterator!=taskTags.end()){
		tagString = tagString + *taskTagIterator + " ";
		taskTagIterator++;
	}

	return tagString;
}

//_taskName already in the form of string, function created for
//consistency sake
string StorageConverter::convertTaskNameToString(Task taskToConvert){
	_taskName = taskToConvert.getTaskName();
	return _taskName; 
}


//converts a Datetime string into a ptime object
//function throws exception if conversion is not successful
void StorageConverter::convertStringStartDatetimeToTask(Task& convertedTask){

	try{
		if (_taskDatetimeString == NOT_A_DATETIME){
			convertedTask.setTaskStartTime(not_a_date_time); 
		} else {
			ptime taskStartTime(from_iso_string(_taskDatetimeString));
			convertedTask.setTaskStartTime(taskStartTime);
		}
	}
	catch(exception&){
		compileErrorMessage(STORAGE_FUNCTION_CONVERT_PTIME_START, STORAGE_MSG_PTIME_START_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
	}
	return; 
}

//similar to convertStringToPtime, introduced for SLAP
void StorageConverter::convertStringEndDatetimeToTask(Task& convertedTask){
	try{
		if (_taskDatetimeString == NOT_A_DATETIME){
			convertedTask.setTaskEndTime(not_a_date_time); 
		} else {
			ptime taskEndTime(from_iso_string(_taskDatetimeString));
			convertedTask.setTaskEndTime(taskEndTime);
		}
	}
	catch(const out_of_range&){
		compileErrorMessage(STORAGE_FUNCTION_CONVERT_PTIME_END,STORAGE_MSG_PTIME_END_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
	}
	
}

//similar to convertStringToPtime, introduced for SLAP
void StorageConverter::convertStringDeadlineToTask(Task& convertedTask){
	try{
		if (_taskDatetimeString == NOT_A_DATETIME){
			convertedTask.setTaskDeadline(not_a_date_time); 
		} else {
			ptime taskDeadline(from_iso_string(_taskDatetimeString));
			convertedTask.setTaskDeadline(taskDeadline);
		}
		return;
	} catch(...){
		compileErrorMessage(STORAGE_FUNCTION_CONVERT_PTIME_DEADLINE,STORAGE_MSG_PTIME_DEADLINE_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
	}
	
}

//converts	 a vector<string> of tasktags to Task attribute 
void StorageConverter::convertStringTasktagToTask(Task& convertedTask){

	vector<string> taskTagVector = convertTaskTagStringToVector(_taskTags);
	convertedTask.setTaskTags(taskTagVector);

	return; 
}

//convert string to bool 
void StorageConverter::convertStringIsdoneToTask(Task& convertedTask){

	try{
		if(_taskIsDone==STRING_TRUE){
			convertedTask.setTaskIsDone();
		}else if(_taskIsDone==STRING_FALSE){
			convertedTask.setTaskIsNotDone();
		}else{
			compileErrorMessage(STORAGE_FUNCTION_CONVERT_ISDONE,STORAGE_MSG_ISDONE_ERROR);
			logErrorMessage(_logErrorMessage);
			throw; 
		} 
		return;
	}
	catch(exception&){
		compileErrorMessage(STORAGE_FUNCTION_CONVERT_ISDONE,STORAGE_MSG_ISDONE_ERROR);
		logErrorMessage(_logErrorMessage);
		throw; 
	}
}

//convert taskTagstring to vector<string>
//pass in the string to a iss object
//read individual substr delimited by whitespace
//push into the tagVector
vector<string> StorageConverter::convertTaskTagStringToVector(string tagString){

	assert(&tagString!=NULL);
	istringstream tagStringStream(tagString); 
	string individualTag; 
	vector<string> tagVector;
	
	while(tagStringStream>>individualTag){
		if(individualTag[0] != '#'){
			individualTag = '#' + individualTag;
			tagVector.push_back(individualTag);
		} else{
			tagVector.push_back(individualTag);
		}
	}

	return tagVector;
}

//logging function to write error message to file
void StorageConverter::logErrorMessage(string errorMessage){
	if(LOGGING_MODE_ON == true){
		ofstream writeToLogFile;
		string currentTime = to_simple_string(second_clock::local_time());
		writeToLogFile.open(LOG_FILE_NAME, ios::app);
		writeToLogFile << currentTime << endl << errorMessage << endl;
		writeToLogFile << endl;
		writeToLogFile.close();
	} 
	return;
}

//error messages will be compiled to a standard template before 
//it is to be written to file
void StorageConverter::compileErrorMessage(string errorMessageLocation, string errorMessage){
	
	sprintf_s(_logErrorMessage, STORAGE_LOGGING_TEMPLATE.c_str(), 
		errorMessageLocation.c_str(), errorMessage.c_str());

	return;
}


