#include <sstream>
#include <assert.h>
#include "commandfield.h"
#include "agenda.h"
#include "calendar.h"
#include "searchbar.h"

commandfield* commandfield::m_pInstance = NULL;

commandfield* commandfield::Instance(){
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new commandfield;
	return m_pInstance;
}

commandfield::commandfield(){
	font.loadFromFile("NotoSansHant-Black.otf");
	main_field.userInput.setFont(font);
	main_field.userInput.setColor(sf::Color(255, 255, 255, 255));
	main_field.main_rectangle.setFillColor(CMD_INACTIVE_COLOUR);

	suggestion_box.text.setFont(font);
	suggestion_box.text.setColor(sf::Color(255, 255, 255, 255));
	suggestion_box.suggestion_rectangle.setFillColor(SGT_COLOUR_HIDE);

	user_message.setFont(font);
	user_message.setColor(sf::Color(255, 0, 0, 255));

	main_field.userInput.setCharacterSize(30);
	suggestion_box.text.setCharacterSize(24);

	b_LCtrl = false;
	main_field.b_Enable = false;
	suggestion_box.b_Enable = false;
}

void commandfield::init(sf::RenderWindow* window){
	SFMLWindow = window;
	resizedUpdate();
}

void commandfield::resizedUpdate(){
	main_field.main_rectangle.setPosition(sf::Vector2f(30.f, SFMLWindow->getSize().y - CMD_Y_POS));
	main_field.main_rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 60, 40));

	suggestion_box.suggestion_rectangle.setPosition(sf::Vector2f(30.f, SFMLWindow->getSize().y - (CMD_Y_POS+60)));
	suggestion_box.suggestion_rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 60, 40));

	main_field.userInput.setPosition(sf::Vector2f(35.f, SFMLWindow->getSize().y - (CMD_Y_POS-2)));
	suggestion_box.text.setPosition(sf::Vector2f(35.f, SFMLWindow->getSize().y - (CMD_Y_POS+48)));

	user_message.setPosition(sf::Vector2f(30.f, SFMLWindow->getSize().y - 10));
}

void commandfield::draw(){
	setSuggestionText(main_field.userInput.getString());
	SFMLWindow->draw(main_field.main_rectangle);
	SFMLWindow->draw(main_field.userInput);
	SFMLWindow->draw(suggestion_box.suggestion_rectangle);
	SFMLWindow->draw(suggestion_box.text);
}

void commandfield::getPastedString(string content){
	main_field.userInput.setString(content);
}

void commandfield::backSpace(){
	string temp;
	string temp2 = main_field.userInput.getString();
	if (!temp2.empty()){
		temp = temp2.substr(0, temp2.size() - 1);
		main_field.userInput.setString(temp);
	}
}

void commandfield::addCharacter(char content){
	main_field.userInput.setString(main_field.userInput.getString() + content);
}

std::string commandfield::getCommandFieldContent(){
	return main_field.userInput.getString();
}


void commandfield::processUserCommandInput() {
	string userCommandInput = main_field.userInput.getString().toAnsiString();
	bool isUserCommandValid = checkIsUserCommandInputValid(userCommandInput);
	int commandType;

	if (isUserCommandValid) {
		commandType = determineCommandType(userCommandInput);
		switch (commandType) {
			case COMMAND_EDIT: {
				processCommandEdit(userCommandInput);
				break;
			}
			case COMMAND_DONE: {
				processCommandDone(userCommandInput);
				break;
			}
			case COMMAND_DELETE: {
				processCommandDelete(userCommandInput);
				break;
			}
			case COMMAND_OTHERS: {
				processCommandOthers(userCommandInput);
				break;
			}
		}
		clearCommandField();
	}

	return;
}

void commandfield::processCommandEdit(string userCommandInput) {
	istringstream inputString(userCommandInput);
	vector<Task> allCurrentTasks = agenda::Instance()->returnAllTasks();
	int displayIndexToEdit;
	int actualIndexToEdit;
	string userCommand;
	string newEditContents;
	string commandToPassLogic;

	if (inputString >> userCommand >> displayIndexToEdit >> newEditContents) {
		if ((displayIndexToEdit >= 1) && (displayIndexToEdit <= allCurrentTasks.size())) {
			actualIndexToEdit = allCurrentTasks[displayIndexToEdit-1].getTaskIndex();
			commandToPassLogic = "/edit " + to_string(actualIndexToEdit) + " " + newEditContents;
			State newStateToUpdate = LogicExecutor::getNewState(commandToPassLogic);
			updateAllViews(&newStateToUpdate);
		}
	}
	return;
}

void commandfield::processCommandDone(string userCommandInput) {
	istringstream inputString(userCommandInput);
	vector<Task> allCurrentTasks = agenda::Instance()->returnAllTasks();
	int displayIndexToEdit;
	int actualIndexToEdit;
	string userCommand;
	string commandToPassLogic;

	if (inputString >> userCommand >> displayIndexToEdit) {
		if ((displayIndexToEdit >= 1) && (displayIndexToEdit <= allCurrentTasks.size())) {
			actualIndexToEdit = allCurrentTasks[displayIndexToEdit-1].getTaskIndex();
			commandToPassLogic = "/done " + to_string(actualIndexToEdit);
			State newStateToUpdate = LogicExecutor::getNewState(commandToPassLogic);
			updateAllViews(&newStateToUpdate);
		}
	}
	return;
}

void commandfield::processCommandDelete(string userCommandInput) {
	istringstream inputString(userCommandInput);
	vector<Task> allCurrentTasks = agenda::Instance()->returnAllTasks();
	int displayIndexToEdit;
	int actualIndexToEdit;
	string userCommand;
	string commandToPassLogic;

	if (inputString >> userCommand >> displayIndexToEdit) {
		if ((displayIndexToEdit >= 1) && (displayIndexToEdit <= allCurrentTasks.size())) {
			actualIndexToEdit = allCurrentTasks[displayIndexToEdit-1].getTaskIndex();
			commandToPassLogic = "/delete " + to_string(actualIndexToEdit);
			State newStateToUpdate = LogicExecutor::getNewState(commandToPassLogic);
			updateAllViews(&newStateToUpdate);
		}
	}
	return;
}

void commandfield::processCommandOthers(string userCommandInput) {
	State newStateToUpdate = LogicExecutor::getNewState(userCommandInput);
	updateAllViews(&newStateToUpdate);
	return;
}

bool commandfield::checkIsUserCommandInputValid(string userCommandInput) {
	bool isUserCommandValid = false;
	userCommandInput = removeUnwantedCharacters(userCommandInput);
	if (userCommandInput != "") {
		isUserCommandValid = true;
	}
	return isUserCommandValid;
}

string commandfield::removeUnwantedCharacters(string stringToProcess) {
	boost::replace_all(stringToProcess, "\n", "");
	boost::replace_all(stringToProcess, "\r", "");
	boost::replace_all(stringToProcess, " ", "");
	return stringToProcess;
}

int commandfield::determineCommandType(string userCommandInput) {
	istringstream inputString(userCommandInput);
	string userCommand;
	inputString >> userCommand;
	if (userCommand == "/edit") {
		return COMMAND_EDIT;
	}
	else if (userCommand == "/done") {
		return COMMAND_DONE;
	}
	else if (userCommand == "/delete") {
		return COMMAND_DELETE;
	}
	else {
		return COMMAND_OTHERS;
	}
	return COMMAND_OTHERS;
}

void commandfield::updateAllViews(State* stateToUpdateWith) {
	agenda::Instance()->readFromState(*stateToUpdateWith);
	calendar::Instance()->readFromState(*stateToUpdateWith);
	return;
}

void commandfield::clearCommandField() {
	main_field.userInput.setString("");
	return;
}



void commandfield::eventHandler(sf::Event event, sf::Vector2f mouse){
	switch (event.type){
		case sf::Event::MouseButtonPressed:
			if (mouse.x > main_field.main_rectangle.getPosition().x &&
				mouse.x < (main_field.main_rectangle.getPosition().x + main_field.main_rectangle.getSize().x) &&
				mouse.y > main_field.main_rectangle.getPosition().y &&
				mouse.y < (main_field.main_rectangle.getPosition().y + main_field.main_rectangle.getSize().y)){
				setActive(true);
			}
			else{
				setActive(false);
			}
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F1){
				if (main_field.b_Enable)
					setActive(false);
				else
					setActive(true);
			}
			if (main_field.b_Enable){
				if (event.key.code == sf::Keyboard::Return){
					processUserCommandInput();					
				}
				if (event.key.code == sf::Keyboard::BackSpace){
					backSpace();
				}
				if (event.key.code == sf::Keyboard::LControl){
					b_LCtrl = 1;
				}
				if (event.key.code == sf::Keyboard::V){
					if (b_LCtrl){
						OpenClipboard(0);
						HGLOBAL hglb = GetClipboardData(CF_TEXT);
						cout << "paste!" << endl;
						cout << (char*)hglb << endl;
						getPastedString((char*)hglb);
						CloseClipboard();
					}
				}
			}
			break;

		case sf::Event::KeyReleased:
			if (main_field.b_Enable){
				if (event.key.code == sf::Keyboard::LControl){
					b_LCtrl = 0;
				}
			}
			break;

		case sf::Event::TextEntered:
			if (main_field.b_Enable){
				if (event.text.unicode < 128 && event.text.unicode > 0x0000001f){
					addCharacter(static_cast<char>(event.text.unicode));
					cout << "Typed: " << event.text.unicode << endl;
				}
			}
			break;

		default:
			break;
	}
}

void commandfield::setActive(bool active){
	if (active){
		main_field.b_Enable = true;
		main_field.main_rectangle.setFillColor(CMD_ACTIVE_COLOUR);
		searchbar::Instance()->setActive(false);
	}
	else{
		main_field.b_Enable = false;
		main_field.main_rectangle.setFillColor(CMD_INACTIVE_COLOUR);
	}
}

void commandfield::setSuggestionText(string text){
	if (text.size() == 0){
		suggestion_box.text.setString(text);
		suggestion_box.suggestion_rectangle.setFillColor(SGT_COLOUR_HIDE);
	}
	else{
		suggestion_box.text.setString(text);
		suggestion_box.suggestion_rectangle.setFillColor(SGT_ACTIVE_COLOUR);
	}
}
