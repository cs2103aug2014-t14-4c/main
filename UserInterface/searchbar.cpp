#include "searchbar.h"
#include "agenda.h"
#include "calendar.h"
#include "commandfield.h"

searchbar* searchbar::m_pInstance = NULL;

searchbar* searchbar::Instance(){
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new searchbar;
	return m_pInstance;
}

searchbar::searchbar(){
	font.loadFromFile("NotoSansHant-Black.otf");
	userInput.setFont(font);
	userInput.setColor(sf::Color(255, 255, 255, 255));
	rectangle.setFillColor(SEARCH_INACTIVE_COLOUR);
	b_LCtrl = false;
	b_Enable = false;
}

void searchbar::init(sf::RenderWindow* window){
	SFMLWindow = window;
	resizedUpdate();
}

void searchbar::resizedUpdate(){
	rectangle.setPosition(sf::Vector2f(500.f, 10.f));
	rectangle.setSize(sf::Vector2f(SFMLWindow->getSize().x - 550, 40));

	userInput.setPosition(sf::Vector2f(505.f, 12.f));
	userInput.setCharacterSize(30);
}

void searchbar::updateView(){
	State state;
	if (userInput.getString().getSize() > 0){
		state = LogicExecutor::getNewState("/search " + userInput.getString());
	}
	else{
		state = LogicExecutor::getNewState("/clear");
	}
	agenda::Instance()->readFromState(state);
	calendar::Instance()->readFromState(state);
}

void searchbar::draw(){
	SFMLWindow->draw(rectangle);
	SFMLWindow->draw(userInput);
}

void searchbar::getPastedString(string content){
	userInput.setString(content);
}

void searchbar::backSpace(){
	string temp;
	string temp2 = userInput.getString();
	if (!temp2.empty()){
		temp = temp2.substr(0, temp2.size() - 1);
		userInput.setString(temp);
	}
}

void searchbar::addCharacter(char content){
	userInput.setString(userInput.getString() + content);

}

std::string searchbar::getCommandFieldContent(){
	return userInput.getString();
}

void searchbar::eventHandler(sf::Event event, sf::Vector2f mouse){
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
		if (event.key.code == sf::Keyboard::F5){
			if (b_Enable)
				setActive(false);
			else{
				setActive(true);
			}
		}
		if (b_Enable){
			if (event.key.code == sf::Keyboard::Return){
			}
			if (event.key.code == sf::Keyboard::BackSpace){
				backSpace();
				updateView();
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
		updateView();
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

void searchbar::setActive(bool active){
	if (active){
		b_Enable = true;
		rectangle.setFillColor(SEARCH_ACTIVE_COLOUR);
		commandfield::Instance()->setActive(false);
	}
	else{
		b_Enable = false;
		rectangle.setFillColor(SEARCH_INACTIVE_COLOUR);
	}
}