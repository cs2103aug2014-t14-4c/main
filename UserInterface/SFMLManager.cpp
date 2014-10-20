#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "SFMLManager.h"
#include "LogicExecutor.h"

SFMLManager::SFMLManager(){
}

SFMLManager::~SFMLManager(){
}

void SFMLManager::init(){
	SFMLWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "WhatToDo");
	SFMLWindow->setFramerateLimit(60);

	buttonInit();
	ready();

	calendar::Instance()->init(SFMLWindow);
	agenda::Instance()->init(SFMLWindow);
	commandfield.init(SFMLWindow);
	searchbar::Instance()->init(SFMLWindow);

	view = 1;		// 1 = agenda, 0 = calendar
	exit = false;
	b_dragging = false;
}

void SFMLManager::positionUpdate(){
	viewTop.setSize(sf::Vector2f(SFMLWindow->getSize().x, SFMLWindow->getSize().y));
	viewTop.setCenter(sf::Vector2f(SFMLWindow->getSize().x / 2, SFMLWindow->getSize().y / 2));

	viewTasksCalendarTimeLine.setSize(sf::Vector2f(SFMLWindow->getSize().x, SFMLWindow->getSize().y));
	viewTasksCalendarTimeLine.setViewport(sf::FloatRect(1 - ((float)(SFMLWindow->getSize().x - 100) / (float)SFMLWindow->getSize().x), 1 - ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y), 1, ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y)));
	viewTasksCalendarTimeLine.setCenter(sf::Vector2f(SFMLWindow->getSize().x / 2, SFMLWindow->getSize().y / 2));

	viewTasksCalendarDateLine.setSize(sf::Vector2f(SFMLWindow->getSize().x, SFMLWindow->getSize().y));
	viewTasksCalendarDateLine.setViewport(sf::FloatRect(0, 1 - ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y), 1, ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y)));
	viewTasksCalendarDateLine.setCenter(sf::Vector2f(SFMLWindow->getSize().x / 2, SFMLWindow->getSize().y / 2));
	
	viewTasksAgenda.setSize(sf::Vector2f(SFMLWindow->getSize().x, SFMLWindow->getSize().y));
	viewTasksAgenda.setViewport(sf::FloatRect(0, 1 - ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y), 1, ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y)));
	viewTasksAgenda.setCenter(sf::Vector2f(SFMLWindow->getSize().x / 2, SFMLWindow->getSize().y / 2));

	viewTasksCalendar.setSize(sf::Vector2f(SFMLWindow->getSize().x, SFMLWindow->getSize().y));
	viewTasksCalendar.setViewport(sf::FloatRect(1 - ((float)(SFMLWindow->getSize().x - 100) / (float)SFMLWindow->getSize().x), 1 - ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y), 1, ((float)(SFMLWindow->getSize().y - 60) / (float)SFMLWindow->getSize().y)));
	viewTasksCalendar.setCenter(sf::Vector2f(SFMLWindow->getSize().x / 2, SFMLWindow->getSize().y / 2));


	sprite_background_darker.setPosition(sf::Vector2f(0, 0));
	sprite_background.setPosition(sf::Vector2f(0, 60));
	sprite_background_trans.setPosition(sf::Vector2f(SFMLWindow->getSize().x - 200, 60));
	sprite_background.setScale(sf::Vector2f(1, (float)((float)(SFMLWindow->getSize().y - 120) / (float)SFMLWindow->getSize().y)));

}

void SFMLManager::ready(void){

	//Prepare background images
	texture_background.loadFromFile("image.jpg");

	//for Task
	sprite_background.setTexture(texture_background);

	//for UI
	sprite_background_darker.setTexture(texture_background);
	sprite_background_darker.setColor(sf::Color(150, 150, 150, 255));

	//for unfinished
	sprite_background_trans.setTexture(texture_background);
	sprite_background_trans.setColor(sf::Color(130, 130, 130, 255));

	positionUpdate();
}

void SFMLManager::buttonHandler(void){
	if (btn_toggleView.isClickingOn(SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop))){
		view = !view;
	}
	if (btn_delete.isClickingOn(SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop))){
		cout << "Clicked on Delete" << endl;
	}
	if (btn_redo.isClickingOn(SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop))){
		State state = LogicExecutor::getNewState("/redo");
		agenda::Instance()->readFromState(state);
		calendar::Instance()->readFromState(state);
	}
	if (btn_undo.isClickingOn(SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop))){
		State state = LogicExecutor::getNewState("/undo");
		agenda::Instance()->readFromState(state);
		calendar::Instance()->readFromState(state);
	}
}

void SFMLManager::eventHandler(void){
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			b_dragging = false;
	}
	sf::Event event;
	while (SFMLWindow->pollEvent(event)){
		switch (event.type){
		case sf::Event::MouseWheelMoved:
			if (!view){
				viewTasksCalendarDateLine.move(0, event.mouseWheel.delta * -20);
				viewTasksCalendar.move(0, event.mouseWheel.delta * -20);
			}
			else{
				viewTasksAgenda.move(sf::Vector2f(0, event.mouseWheel.delta * -20));
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left){
				buttonHandler();
				commandfield.eventHandler(event, SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop));
				searchbar::Instance()->eventHandler(event, SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop));
				// to cover one small bug in sfml(click on the window to make it foreground window)
				if (SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop).x > 0 &&
					SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop).x < SFMLWindow->getSize().x &&
					SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop).y > 0 &&
					SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop).y < SFMLWindow->getSize().y
					){
					SetForegroundWindow(SFMLWindow->getSystemHandle());
				}
				dragging_start = sf::Mouse::getPosition();
				b_dragging = true;
			}
			break;
		case sf::Event::MouseMoved:
			if (b_dragging){
				if (view){
					viewTasksAgenda.move(0, -(sf::Mouse::getPosition().y - dragging_start.y));
					dragging_start = sf::Mouse::getPosition();
				}
				else{
					viewTasksCalendarDateLine.move(0, -(sf::Mouse::getPosition().y - dragging_start.y));
					viewTasksCalendarTimeLine.move(-(sf::Mouse::getPosition().x - dragging_start.x), 0);
					viewTasksCalendar.move(-(sf::Mouse::getPosition().x - dragging_start.x), -(sf::Mouse::getPosition().y - dragging_start.y));
					
					
					dragging_start = sf::Mouse::getPosition();
				}
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Tab){
				view = !view;
			}
			if (event.key.code == sf::Keyboard::F4){
				//State state = LogicExecutor::getNewState("/delete" + current_selecting_task);
			}
			if (event.key.code == sf::Keyboard::F3){
				State state = LogicExecutor::getNewState("/redo");
				agenda::Instance()->readFromState(state);
				calendar::Instance()->readFromState(state);
			}
			if (event.key.code == sf::Keyboard::F2){
				State state = LogicExecutor::getNewState("/undo");
				agenda::Instance()->readFromState(state);
				calendar::Instance()->readFromState(state);
			}
		case sf::Event::KeyReleased:
		case sf::Event::TextEntered:
			commandfield.eventHandler(event, SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop));
			searchbar::Instance()->eventHandler(event, SFMLWindow->mapPixelToCoords(sf::Mouse::getPosition(*SFMLWindow), viewTop));
			break;

		case sf::Event::Resized:
			// update the view to the new size of the window
			positionUpdate();
			agenda::Instance()->resizedUpdate();
			commandfield.resizedUpdate();
			searchbar::Instance()->resizedUpdate();
			break;

		case sf::Event::Closed:
			exit = true;
			SFMLWindow->close();
			break;

		default:
			break;
		}
	}
}

void SFMLManager::windowRender(void){
	SFMLWindow->clear();
	drawUI();				//Start to draw UI (buttons, text fields etc) and background image
	drawTasks();			//Start do draw agenda/calendar view
	//drawUnfinishedTasks();	//draw right hand side unfinished tasks reminder

	SFMLWindow->setView(viewTop);
	commandfield.draw();
	searchbar::Instance()->draw();

	SFMLWindow->display();
}

void SFMLManager::drawUI(){
	SFMLWindow->setView(viewTop);
	SFMLWindow->draw(sprite_background_darker);

	btn_toggleView.draw(SFMLWindow);
	btn_undo.draw(SFMLWindow);
	btn_redo.draw(SFMLWindow);
	btn_delete.draw(SFMLWindow);
	SFMLWindow->draw(sprite_background);
}

void SFMLManager::drawTasks(){
	if (!view){
		//draw grid and tasks first so that they can be hided from the hori/verti bars
		SFMLWindow->setView(viewTasksCalendar);
		calendar::Instance()->draw();

		//draw timeline
		SFMLWindow->setView(viewTasksCalendarTimeLine);
		calendar::Instance()->drawVerticalFloating();

		//draw dateline
		SFMLWindow->setView(viewTasksCalendarDateLine);
		calendar::Instance()->drawHorizontalFloating();
	}
	else {
		SFMLWindow->setView(viewTasksAgenda);
		agenda::Instance()->draw(SFMLWindow);
	}

}

void SFMLManager::drawUnfinishedTasks(){
	//SFMLWindow->setView(viewUnfinished);
	//SFMLWindow->draw(sprite_background_trans);
}

void SFMLManager::buttonInit(){
	btn_toggleView.init(0.f, 5.f, "Toggle", NULL);
	btn_undo.init(12 + 12*6, 5.f, "Undo", NULL);
	btn_redo.init(24 + 12 * 6 + 12 * 4, 5.f, "Redo", NULL);
	btn_delete.init(36 + 12 * 6 + 12 * 4 + 12 * 4, 5.f, "Delete", NULL);
}
