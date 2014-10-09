#pragma once
#include <QWidget>
#include <QGraphicsObject>
#include <vector>
#include <string>
#include <sstream>
#include "ui_anothergui.h"
#include "State.h"
#include "Task.h"
#include "LogicExecutor.h"
#include <boost/algorithm/string.hpp>
using namespace std;

class AnotherGUI;

class Storage : public QWidget {

	Q_OBJECT

	public:
		Storage(void);
		~Storage(void);
		void setUI(Ui::AnotherGUIClass ui);
		void setindex(int index);
		void setlist(vector<Task> hello);

	public slots:
		void commandLineInput();
		void toggleCalandarview();
		void toggleAgendaview();
		void searchInput();
		void GUIUndo();
		void GUIRedo();

	signals:
		void dataChanged(State newState);

	private:
		Ui::AnotherGUIClass _ui;
		static State _currState;
		int _index;
		vector<Task> _hello;
		/*
		void commandAdd(string toAdd);
		void commandDelete(int index);
		void commandClear();
		void commandEdit(int index, string toAdd);
		void commandSearch();
		void commandRefresh();
		*/

};

