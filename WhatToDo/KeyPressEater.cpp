#include "KeyPressEater.h"


KeyPressEater::KeyPressEater() {
}

KeyPressEater::~KeyPressEater(void) {
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Return) {
			emit enterPressed(obj);
			return true;
		}
		else if (keyEvent->key() == Qt::Key_Tab) {
			emit tabPressed();
			return true;
		}
		else {
			return QObject::eventFilter(obj, event);
		}
	}
	else {
		return QObject::eventFilter(obj, event);
	}
}
