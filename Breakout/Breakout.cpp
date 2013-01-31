// Breakout.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Game.h"




int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR,INT )
{
	Game breakout1;
	breakout1.Start();
	return 0;
}