#include "stdafx.h"
#include "MainWindow.h"

HINSTANCE hInst;			// current instance

MainWindow::MainWindow(){
	sfmlManager.init();
}


MainWindow::~MainWindow(){
}

//Main function
int MainWindow::mainLoop(){
	while (!sfmlManager.exit){
		sfmlManager.eventHandler();
		sfmlManager.windowRender();
	}
	return 0;
}
