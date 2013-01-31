#include "stdafx.h"
#include "Game.h"


Game::Game()

{}

Game::~Game(){}

void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;
  //initalize window
   Window myWindow;
   HWND hWnd = myWindow.Create(1024,768,L"Breakout!");

  //initialize graphics
   gfx.InitD3D(hWnd,1024,768);
   gfx.InitPipeline(); // load textures,etc.
  _gameState = Game::Playing;  //We are now done initializing,changing game state
  
  while(!IsExiting())
  {
    GameLoop();
  }
  gfx.CleanD3D();
  myWindow.Close(L"Breakout!");
}

bool Game::IsExiting()
{
  if(_gameState == Game::Exiting) 
    return true;
  else 
    return false;
}

void Game::GameLoop()
{
    MSG msg;
    ZeroMemory( &msg,sizeof( msg ) );
    while( TRUE)
    {
        if( PeekMessage( &msg,NULL,0,0,PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
			  if(msg.message == WM_QUIT)
			  {	 
				_gameState = Game::Exiting;
                break;
			  }
        }
        else
		{
			switch(_gameState)
			{
				case Game::Playing:
				{
					//render frame
					gfx.BeginFrame(0.0f,0.0f,0.0f,1.0f);
					//Draw Objects
					gfx.RenderTestBackground();
					gfx.EndFrame();
				}
			}
			
		}
    }


}


Game::GameState Game::_gameState = Uninitialized;
