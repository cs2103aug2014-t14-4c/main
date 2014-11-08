#include "StorageConverter.h"

StorageConverter::StorageConverter(void){
	_taskDatetimeString = ""; 
	_taskName = "";
	_taskTags = "";
	_taskIsDone = ""; 
	_logFileName = LOG_FILE_NAME; 
}

vector<string> StorageConverter::convertTaskToString(Task taskToConvert){

	//will convert individual task attributes to strings
	//note: order of conversion important for the developer, not for the user
	//clear initial content
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

Task StorageConverter::convertStringToTask(vector<string> stringToConvert) {
	Task convertedTask; 
	assert(&stringToConvert != NULL);
	vector<string>::iterator taskAttributeIterator = stringToConvert.begin(); 
	
	//get the substring which is input for conversion
	//convert individual substrings into task attributes
	//use task setter methods to "Create" the task

	try{
		//1. convert startime
		_taskDatetimeString = (*taskAttributeIterator).substr(TITLE_TASKSTARTDATETIME.size());
		//assert(_taskDatetimeString.size()==15);
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
	_taskName = taskToConvert.getTaskName();
	return _taskName; 
}

//convert taskTagstring to vector<string>
vector<string> StorageConverter::convertTaskTagStringToVector(string tagString){
	//pass in the string to a iss object
	//read individual substr delimited by whitespace
	//push into the tagVector
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

//convert string to bool 
void StorageConverter::convertStringIsdoneToTask(Task& convertedTask){
	//converting string to boolean
	try{
		if(_taskIsDone==STRING_TRUE){
			convertedTask.setTaskIsDone();
		}else if(_taskIsDone==STRING_FALSE){
			
		}else{
			compileErrorMessage(FUNCTION_CONVERT_ISDONE,MSG_ISDONE_ERROR);
			logErrorMessage(_logErrorMessage);
			throw; 
		} 
		return;
	}
	catch(exception&){
		compileErrorMessage(FUNCTION_CONVERT_ISDONE,MSG_ISDONE_ERROR);
		logErrorMessage(_logErrorMessage);
		throw; 
		//log error
	}
}

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
		compileErrorMessage(FUNCTION_CONVERT_PTIME_START, MSG_PTIME_START_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
		//log error
	}
	return; 
}

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
		compileErrorMessage(FUNCTION_CONVERT_PTIME_END,MSG_PTIME_END_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
		//throw outofrange error message
	}
	
}

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
		compileErrorMessage(FUNCTION_CONVERT_PTIME_DEADLINE,MSG_PTIME_DEADLINE_ERROR);
		logErrorMessage(_logErrorMessage);
		throw;
		//log error message
	}
	
}

void StorageConverter::convertStringTasktagToTask(Task& convertedTask){

	vector<string> taskTagVector = convertTaskTagStringToVector(_taskTags);
	convertedTask.setTaskTags(taskTagVector);

	return; 
}

void StorageConverter::logErrorMessage(string errorMessage){
	if(LOGGING_MODE_ON == true){
		ofstream writeToLogFile;
		string currentTime = to_simple_string(second_clock::local_time());
		writeToLogFile.open(LOG_FILE_NAME, ios::app);
		writeToLogFile << currentTime << endl << errorMessage << endl;
		writeToLogFile.close();
	} 
	return;
}

void StorageConverter::compileErrorMessage(string errorMessageLocation, string errorMessage){
	
	sprintf_s(_logErrorMessage, LOGGING_TEMPLATE.c_str(), errorMessageLocation.c_str(), errorMessage.c_str());

	return;
}