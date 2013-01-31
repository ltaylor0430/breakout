#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <wchar.h>
#include "Keyboard.h"
#include "D3DGraphics.h"
class Window
{
public:
	Window(void);
	~Window(void);
    HWND Create(int width, int height, LPCTSTR Name);
    void Close(LPCTSTR Name);
    WNDCLASSEX *wcPointer; 
	
};

