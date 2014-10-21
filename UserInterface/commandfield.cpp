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
	userInput.setFont(font);
	userInput.setColor(sf::Color(255, 255, 255, 255));
	rectangle.setFillColor(CMD_INACTIVE_COLOUR);
	b_LCtrl = false;
	b_Enable = false;
}

void commandfield::init(sf::RenderWindow* window){
	SFMLWindow = window;
	resizedUpdate();
}

void commandfield::resizedUpdate(){
	rectangle.setPosition(sf::Vector2f(30.f, SFMLWindow->getSize().y - 100));
	rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 20, 40));


	userInput.setPosition(sf::Vector2f(35.f, SFMLWindow->getSize().y - 98));
	userInput.setCharacterSize(30);
}

void commandfield::draw(){
	SFMLWindow->draw(rectangle);
	SFMLWindow->draw(userInput);
}

void commandfield::getPastedString(string content){
	userInput.setString(content);
}

void commandfield::backSpace(){
	string temp;
	string temp2 = userInput.getString();
	if (!temp2.empty()){
		temp = temp2.substr(0, temp2.size() - 1);
		userInput.setString(temp);
	}
}

void commandfield::addCharacter(char content){
	userInput.setString(userInput.getString() + content);
}

std::string commandfield::getCommandFieldContent(){
	return userInput.getString();
}


void commandfield::eventHandler(sf::Event event, sf::Vector2f mouse){
	switch (event.type){
		case sf::Event::MouseButtonPressed:
			if (mouse.x > rectangle.getPosition().x &&
				mouse.x < (rectangle.getPosition().x + rectangle.getSize().x) &&
				mouse.y > rectangle.getPosition().y &&
				mouse.y < (rectangle.getPosition().y + rectangle.getSize().y)){
				setActive(true);
			}
			else{
				setActive(false);
			}
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F1){
				if (b_Enable)
					setActive(false);
				else
					setActive(true);
			}
			if (b_Enable){
				if (event.key.code == sf::Keyboard::Return){
					State state;
					if (userInput.getString().getSize() > 0){
						if (userInput.getString().toAnsiString().substr(0, 7) == "/delete"){
							state = LogicExecutor::getNewState("/delete "
								+ agenda::Instance()->returnRealIndex(stoi(
							userInput.getString().toAnsiString().substr(7, userInput.getString().toAnsiString().size())
							)-1));
						}
						else if (userInput.getString().toAnsiString().substr(0, 5) == "/edit"){
							int count = 0;
							string index;
							istringstream iss(userInput.getString().toAnsiString());
							while (iss >> index){
								count++;
							}
							try{
								throw count;
							}
							catch (int e){
								cout << "An exception occurred. Exception Nr. " << e << '\n';
							}
							/*
							istringstream iss(userInput.getString().toAnsiString());
							string word;
							string index, new_name;
							iss >> index;
							iss >> index;
							state = LogicExecutor::getNewState("/edit "
								+ agenda::Instance()->returnRealIndex(stoi(index) - 1)
								+ userInput.getString()
								);
							*/
						}
						else{
							state = LogicExecutor::getNewState(userInput.getString());
						}
						agenda::Instance()->readFromState(state);
						calendar::Instance()->readFromState(state);
						string empty;
						userInput.setString(empty);
					}
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
			if (b_Enable){
				if (event.key.code == sf::Keyboard::LControl){
					b_LCtrl = 0;
				}
			}
			break;

		case sf::Event::TextEntered:
			if (b_Enable){
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
		b_Enable = true;
		rectangle.setFillColor(CMD_ACTIVE_COLOUR);
		searchbar::Instance()->setActive(false);
	}
	else{
		b_Enable = false;
		rectangle.setFillColor(CMD_INACTIVE_COLOUR);
	}
}
