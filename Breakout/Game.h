#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Window.h"
class Game
{

public:
    Game();
   ~Game();
   void Start();

private:
  Window myWindow;
  static bool IsExiting();
  void GameLoop();

  enum GameState { Uninitialized, ShowingSplash, Paused, 
          ShowingMenu, Playing, Exiting };
  
  static GameState _gameState;
  /******************
  /* User Functions */
private:
    D3DGraphics gfx;
	Window _mainWindow;
};
