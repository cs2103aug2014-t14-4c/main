#include "Storage.h"
#include "Storage.h"


State Storage::_currState;

Storage::Storage(void) {
}

Storage::~Storage(void)
{
}

void Storage::GUIUndo() {
	_currState = LogicExecutor::getNewState("/undo");
	emit dataChanged(_currState);

}

void Storage::GUIRedo() {
	_currState = LogicExecutor::getNewState("/redo");
	emit dataChanged(_currState);
}



void Storage::searchInput() {
	QString currentText = _ui.searchbox->toPlainText();
	string userinput = currentText.toStdString();
	boost::replace_all(userinput, "\n", "");
	boost::replace_all(userinput, "\r", "");
	if (userinput == "") {
		_currState = LogicExecutor::getNewState("/clear");
		emit dataChanged(_currState);
		return;
	}
	_currState = LogicExecutor::getNewState("/search " + userinput);
	emit dataChanged(_currState);
	return;
}


void Storage::setUI(Ui::AnotherGUIClass ui) {
	_ui = ui;
	return;
}

void Storage::commandLineInput() {
	QString currentText = _ui.commandbox->toPlainText();
	_ui.commandbox->setPlainText(QString::fromStdString(""));
	string userinput = currentText.toStdString();
	boost::replace_all(userinput, "\n", "");
	boost::replace_all(userinput, "\r", "");
	if (userinput == "") {
		return;
	}
	
	string testcommand;
	int testindex;
	istringstream goingin(userinput);
	goingin >> testcommand;
	if (testcommand == "/edit") {
		if (goingin >> testindex) {
			if ((testindex <= 0) || (testindex > _hello.size())) { 
			}
			else {
				int now = _hello[testindex-1].getTaskIndex();
				string wtf;
				if (getline(goingin, wtf)) {
					string fake = "/edit " + to_string(now) + wtf;
					_currState = LogicExecutor::getNewState(fake);
				}
			}
		}
	}
	else if (testcommand == "/delete") {
		if (goingin >> testindex) {
			if ((testindex <= 0) || (testindex > _hello.size())) { 
			}
			else {
				int now = _hello[testindex-1].getTaskIndex();
				string fake = "/delete " + to_string(now);
				_currState = LogicExecutor::getNewState(fake);
			}
		}
	}
	else if (testcommand == "/done") {
		if (goingin >> testindex) {
			if ((testindex <= 0) || (testindex > _hello.size())) { 
			}
			else {
				int now = _hello[testindex-1].getTaskIndex();
				string fake = "/done " + to_string(now);
				_currState = LogicExecutor::getNewState(fake);
			}
		}
	}
	else if (testcommand == "/search") {
		string what;
		if (getline(goingin, what)) {
			_currState = LogicExecutor::getNewState("/search " + what);
		}
	}
	else {
		_currState = LogicExecutor::getNewState(userinput);
	}

	emit dataChanged(_currState);
	return;
}

void Storage::setindex(int index) {
	_index = index;
	return;
}

void Storage::setlist(vector<Task> hello) {
	_hello = hello;
}

/*
void Storage::commandLineInput() {
	QString stringToAdd = _ui.commandbox->toPlainText();
	_ui.commandbox->setPlainText(QString::fromStdString(""));
	string userinput = stringToAdd.toStdString();
	
	if (userinput == "") {
		return;
	}

	istringstream inputstring(userinput);
	string command;
	inputstring >> command;

	if (command == "add") {
		string therest;
		getline(inputstring, therest);
		commandAdd(therest);
	}
	else if (command == "delete") {
		int index;
		inputstring >> index;
		commandDelete(index);
	}
	else if (command == "clear") {
		commandClear();
	}
	else if (command == "edit") {
		int index;
		string therest;
		inputstring >> index;
		getline(inputstring, therest);
		commandEdit(index, therest);
	}
	else if (command == "search") {
		commandSearch();
	}
	else if (command == "refresh") {
		commandRefresh();
	}
	else {
		commandAdd(userinput);
	}

	emit dataChanged(_listOfTasks);
	return;
}

void Storage::commandAdd(string toAdd) {
	_listOfTasks.push_back(toAdd);
	return;
}

void Storage::commandDelete(int index) {
	_listOfTasks.erase(_listOfTasks.begin()+index-1);
	return;
}

void Storage::commandClear() {
	_listOfTasks.clear();
	return;
}

void Storage::commandEdit(int index, string toAdd) {
	_listOfTasks[index-1] = toAdd;
	return;
}

void Storage::commandSearch() {
	return;
}

void Storage::commandRefresh() {
	return;
}

void Storage::commandUndo() {
	return;
}

void Storage::commandRedo() {
	return;
}
*/

void Storage::toggleCalandarview() {
	_ui.displaycalendar->setVisible(true);
	return;
}

void Storage::toggleAgendaview() {
	_ui.displaycalendar->setVisible(false);
	return;
}
