#pragma once
#include "resource.h"
#include <SFML\Graphics.hpp>

#define MAX_LOADSTRING 100

class MainWindow
{
	public:
		MainWindow();
		~MainWindow();
		int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ LPTSTR    lpCmdLine,
			_In_ int       nCmdShow);

	private:

		// Forward declarations of functions included in this code module:
		ATOM				MyRegisterClass(HINSTANCE hInstance);
		BOOL				InitInstance(HINSTANCE, int);
		static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
		static INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
		void SfmlReady(void);
		void SfmlEventHandler(void);
		void SfmlWindowRender(void);

		// Global Variables:
		TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
		TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

		// SFML
		sf::RenderWindow SFMLWindow;
		sf::Texture texture;
		sf::Sprite sprite;
};

