#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <wchar.h>
#include "Keyboard.h"
#include "D3DGraphics.h"
#define WIN32_LEAN_AND_MEAN

class Window
{

public:
	static KeyboardServer kServ;
	Window(void);
	~Window(void);
    HWND Create(int& screenWidth, int& screenHeight, LPCTSTR Name, WNDPROC );
    void Close();
	void ShutdownWindow();
    WNDCLASSEX *wcPointer; 
	
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hWnd; 
};

