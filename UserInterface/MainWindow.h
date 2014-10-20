#pragma once
#include "resource.h"
#include "SFMLManager.h"

#define MAX_LOADSTRING 100

class MainWindow
{
	public:
		MainWindow();
		~MainWindow();
		int mainLoop();

private:
	SFMLManager sfmlManager;

};