#ifndef ANOTHERGUI_H
#define ANOTHERGUI_H
 
#include <QtWidgets/QMainWindow>
#include <QGraphicsObject>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <string>
#include <vector>
#include "ui_anothergui.h"
#include "Storage.h"
#include "KeyPressEater.h"
#include "LogicExecutor.h"
#include "State.h"
#include "Task.h"
#include "boost\date_time.hpp"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class AnotherGUI : public QMainWindow
{
	Q_OBJECT

	public:
		AnotherGUI(QWidget *parent = 0);
		~AnotherGUI();
		static int getNoOfIndexes();

	public slots:
		void updateView(State latestState);
		void setSuggestionList();

	private:
		Ui::AnotherGUIClass ui;
		Storage* _myStorage;
		KeyPressEater* _myKeyPressEater;
		QListView* _listView;
		void connectAllSlots();
		void createSuggestionList();
		int getSuggestionListHeight(QStringList* List);
		int getSuggestionListWidth(QStringList* List);
		string convertStateToHtml(State inputState);
		vector<Task> sortTasksByDate(vector<Task> toSort);
		static int _size;
		string changeDayToDay(int day);
		string changeMonthToMonth(int month);
		string changeDateToString(ptime x);
		string getShowTime(ptime one, ptime two);
		string getampm(ptime one);
		vector<Task> specialSortByDeadline(vector<Task> toSort);

};

#endif // ANOTHERGUI_H
