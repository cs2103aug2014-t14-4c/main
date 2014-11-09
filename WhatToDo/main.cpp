//****************************************************************************
//@author A0110648L

#include "whattodo.h"
#include <QtWidgets/QApplication>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string exeDirectory;
	QApplication mainApplication(argc, argv);
	exeDirectory = mainApplication.applicationDirPath().toStdString();
	WhatToDo mainWindow(exeDirectory);
	mainWindow.show();
	return mainApplication.exec();
}
