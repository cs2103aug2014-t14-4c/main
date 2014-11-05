//****************************************************************************
//@Poh Zhi Chao A0110648L
// 
// This is the KeyPressEater class, which is reponsible for intercepting all 
// key events for certain QWidgets for which it is installed, and determining if
// certain keys have been entered.
//
// It intercepts only the "Key_Return" and the "Key_Tab" keypress, and emits a 
// signal when this happens. Otherwise, all other key presses are ignored.
//
//****************************************************************************

#pragma once
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

class KeyPressEater : public QObject {
	
	Q_OBJECT

	public:
		KeyPressEater();
		~KeyPressEater(void);
		bool eventFilter(QObject *obj, QEvent *event);

	signals:
		void enterPressed(QObject *obj);
		void tabPressed();

};
