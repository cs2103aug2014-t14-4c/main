#include "whattodo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WhatToDo w;
	w.show();
	return a.exec();
}
