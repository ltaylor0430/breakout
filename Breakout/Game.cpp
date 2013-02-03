#include "stdafx.h"
#include "Game.h"

static KeyboardServer kServ;
Game::Game()
{}

Game::~Game(){}
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpPressed();
				break;
			case VK_DOWN:
				kServ.OnDownPressed();
				break;
			case VK_LEFT:
				kServ.OnLeftPressed();
				break;
			case VK_RIGHT:
				kServ.OnRightPressed();
				break;
			case VK_SPACE:
                kServ.OnSpacePressed();
				break;
			case VK_RETURN:
				kServ.OnEnterPressed();
				break;
			}
			break;
		case WM_KEYUP:
   			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpReleased();
				break;
			case VK_DOWN:
				kServ.OnDownReleased();
				break;
			case VK_LEFT:
				kServ.OnLeftReleased();
				break;
			case VK_RIGHT:
				kServ.OnRightReleased();
				break;
			case VK_SPACE:
				kServ.OnSpaceReleased();
				break;
			case VK_RETURN:
				kServ.OnEnterReleased();
				break;
			}
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}
void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;
  //initalize window
  int screenWidth = 0;
  int screenHeight = 0;
   HWND hWnd = myWindow.Create(screenWidth,screenHeight,L"Breakout!",MsgProc);
  
  //initialize graphics
   gfx.Initialize(screenWidth,screenHeight,hWnd);
  
  _gameState = Game::Playing;  //We are now done initializing,changing game state
  
  while(!IsExiting())
  {
    GameLoop();
  }
  gfx.Shutdown();

  myWindow.ShutdownWindow();

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
    KeyboardClient kb(kServ);
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
			if(kb.EnterIsPressed())
			{
				_gameState = Game::Exiting;
				break;
			}
			switch(_gameState)
			{
				case Game::Playing:
				{
					static float rotation = 0.0f;
					static float playerXPosSteps;
					static float playerYPosSteps;
					// Check if the user pressed escape and wants to exit the application.
					

					// Update the rotation variable each frame.
					rotation += (float)D3DX_PI * 0.005f;
					if(rotation > 360.0f)
					{
						rotation -= 360.0f;
					}
					//render frame
					if (kb.RightIsPressed())
					{
						//lets move oject
						playerXPosSteps =3.5;
					}
					else if (kb.LeftIsPressed())
					{
						playerXPosSteps = -3.5;
					}
					else
					{
						playerXPosSteps = 0;
					}
					if (kb.DownIsPressed())
					{
						playerYPosSteps = 3.5; 
					}
					else if (kb.UpIsPressed())
					{
						playerYPosSteps = -3.5; 
					}
					else
					{
						playerYPosSteps = 0;
					}
					gfx.Render(rotation,playerXPosSteps,playerYPosSteps);
					  
				}
			}
			
		}
    }


}


Game::GameState Game::_gameState = Uninitialized;
