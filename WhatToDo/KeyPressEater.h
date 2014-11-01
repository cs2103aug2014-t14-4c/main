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
