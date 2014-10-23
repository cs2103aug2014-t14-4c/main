#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include "StorageExecutor.h"
#include "Task.h"
#include <vector>
#include <string>

using namespace std;

int main(){


		vector<string> testVector; 
		vector<string> expectedVector; 
		Task expectedTask;
		Task convertedTask;


		expectedVector.clear();
		Task taskObj;
		Task taskObj2;
		StorageConverter storageConverterObj;

		ptime taskStartTime(date(2002,Jan,10), time_duration(1,2,3));
		ptime taskEndTime(date(2003,Jan,10), time_duration(1,2,3));
		ptime taskDeadline(date(2004,Jan,10), time_duration(1,2,3));
		string taskName = "fuckyou";
		string taskDetails = "we gg celebrate birthday";
		vector<string> taskTags;
		taskTags.push_back("#fuckyou");
		taskTags.push_back("#fuckme");
		taskTags.push_back("#fuckitall");

		taskObj.setTaskStartTime(taskStartTime);
		taskObj.setTaskEndTime(taskEndTime);
		taskObj.setTaskDeadline(taskDeadline);
		taskObj.setTaskName(taskName);
		//taskObj.setTaskDetails(taskDetails); // Not used for now
		taskObj.setTaskTags(taskTags);
		taskObj.setTaskIsDone();

		taskObj2.setTaskStartTime(taskStartTime);
		taskObj2.setTaskEndTime(taskEndTime);
		taskObj2.setTaskName(taskName);
		taskObj2.setTaskDeadline(taskDeadline);
		taskObj2.setTaskTags(taskTags);
		//taskObj2.setTaskIsDone();

		//1. getTaskType
		//string taskType = "1";
		//expectedVector.push_back(taskType);
			
		//2. get start datetime 
		string startDatetime = "20020110T010203";
		expectedVector.push_back(startDatetime);

		//3. get end datetime
		string endDatetime = "20030110T010203";
		expectedVector.push_back(endDatetime); 

		//4. get task deadline 
		string taskDuration = "20040110T010203";
		expectedVector.push_back(taskDuration);

		//5. get taskName
		string taskTestName = "fuckyou";
		expectedVector.push_back(taskTestName);

		////6. get task details
		//string taskTestDetails ="we gg celebrate birthday\n";
		//expectedVector.push_back(taskTestDetails);
	
		//6. get task tags
		string taskTagString = "#fuckyou #fuckme #fuckitall ";
		expectedVector.push_back(taskTagString);

		//7. getIsDone
		string getIsDone = "1";
		expectedVector.push_back(getIsDone);
			
		State myState;
		myState.addTask(taskObj);
		myState.addTask(taskObj2);
		StorageExecutor myExecutor; 
		myExecutor.saveToStorage(myState);
		

		vector<vector<string>> testVectorString;
		StorageDatabase myDatabase;
		testVectorString = myDatabase.readFromDatabase(); 

		vector<vector<string>>::iterator myIte = testVectorString.begin();
		while(myIte!=testVectorString.end()){
			for(int i =0; i<6; i++){
				cout << (*myIte)[i] << endl;
			}
			myIte++;
		}

		State myState2; 
		cout << "im getting the content of myState2 " << endl;
		myState2 = myExecutor.loadFromStorage();
		
		//myExecutor.saveToStorage(myState2);

		cout << " END " << endl;

		getchar();

	return 0;
}