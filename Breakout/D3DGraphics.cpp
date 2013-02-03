#include "StdAfx.h"
#include "D3DGraphics.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"


using namespace DirectX;
D3DGraphics::D3DGraphics()	
{

	m_D3D =0;
	m_Camera =0;
	m_ColorShader =0;
	m_TextureShader  =0;
	m_ballSprite =0;
	m_batSprite = 0;
	m_barSprites =0;
}
D3DGraphics::D3DGraphics( HWND hWnd )
{

}


D3DGraphics::~D3DGraphics(void)
{

}

// this function initializes and prepares Direct3D for use

bool D3DGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3D;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->InitD3D(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	//load shaders,models,etc. 
	// Create the bitmap object.
	m_ballSprite = new Sprite;
	if(!m_ballSprite)
	{
		return false;
	}
	m_bgSprite = new Sprite;
	m_barSprites= new Sprite;
	m_batSprite = new Sprite;
	// Initialize the bitmap object.
	result = m_ballSprite->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Breakout/engine/data/swirl_ball_282px.png", 16, 16);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sprite object.", L"Error", MB_OK);
		return false;
	}

	result = m_bgSprite->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Breakout/engine/data/background_texture.jpg", screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sprite object.", L"Error", MB_OK);
		return false;
	}
	result = m_batSprite->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Breakout/engine/data/breakout_bat.png", 120, 38);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sprite object.", L"Error", MB_OK);
		return false;
	}
	
	//depending on level?? switch statement maybe..
	//HRESULT hr = S_OK;
	//hr = CreateWICTextureFromFile(m_D3D->GetDevice(),m_D3D->GetDeviceContext(),L"images/stars.jpg",NULL,&background,NULL);
/*	
   if( FAILED(hr) )
    {
        return false;
    
	}*/
   return true;
	
}

bool D3DGraphics::Render(float rotation, float playerX, float playerY)
{
	
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	//3D Render goes here

	//2D Render
	 m_D3D->GetOrthoMatrix(orthoMatrix);
	 // Turn off the Z buffer to begin all 2D rendering.
	 m_D3D->TurnZBufferOff();
	 //render vertices and shaders here
	 //render background
	 result = m_bgSprite->Render(m_D3D->GetDeviceContext(), 0, 0);
	 if(!result)
	 {
		return false;
	 }
	 result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_bgSprite->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_bgSprite->GetTexture());
	 if(!result)
	 {
		return false;
  	}
	 result = RenderPaddle(worldMatrix, viewMatrix, projectionMatrix, orthoMatrix,rotation,playerX,playerY);
	 result = RenderSprite(worldMatrix, viewMatrix, projectionMatrix, orthoMatrix,rotation,playerX,playerY);
	 // Turn the Z buffer back on now that all 2D rendering has completed.
	 m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndFrame();

	return true;
}

bool D3DGraphics::RenderSprite(D3DXMATRIX worldMatrix,D3DXMATRIX viewMatrix,
	D3DXMATRIX  projectionMatrix,D3DXMATRIX orthoMatrix, float rotation,float playerX, float playerY)
{
	bool result;
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	float x=400,y=400;
	if (m_ballSprite->IsRender())
	{
		x = m_ballSprite->m_previousPosX + playerX;
	    y = m_ballSprite->m_previousPosY + playerY;
	}
	result = m_ballSprite->Render(m_D3D->GetDeviceContext(), x, y);
	if(!result)
	{
		return false;
	}

	D3DXMATRIX newWorld;
	//D3DXMatrixRotationZ( &worldMatrix, rotation );
	D3DXVECTOR2 *midPt = new D3DXVECTOR2();
	//D3DXMatrixRotationAxis(&worldMatrix,m_ballSprite->GetMiddlePoint(midPt),rotation);
	D3DXVECTOR2 test(0.0f,0.0f);
	m_ballSprite->GetMiddlePoint(midPt);
	
		D3DXMatrixAffineTransformation2D(&worldMatrix,1.0f,m_ballSprite->GetMiddlePoint(midPt),rotation,&test);
	
	delete midPt;
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_ballSprite->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_ballSprite->GetTexture());
	if(!result)
	{
		return false;
	}
	return true;
}
bool D3DGraphics::RenderPaddle(D3DXMATRIX worldMatrix,D3DXMATRIX viewMatrix,
	D3DXMATRIX  projectionMatrix,D3DXMATRIX orthoMatrix, float rotation,float playerX, float playerY)
{
	bool result;
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	float x=300,y=400;

	if (m_batSprite->IsRender())
	{
		x = m_batSprite->m_previousPosX + playerX;
	    y = m_batSprite->m_previousPosY;
	}
	result = m_batSprite->Render(m_D3D->GetDeviceContext(), x, y);
	if(!result)
	{
		return false;
	}

	D3DXMATRIX newWorld;
	//D3DXMatrixRotationZ( &worldMatrix, rotation );
	D3DXVECTOR2 *midPt = new D3DXVECTOR2();
	//D3DXMatrixRotationAxis(&worldMatrix,m_ballSprite->GetMiddlePoint(midPt),rotation);
	D3DXVECTOR2 test(0,0);
	m_ballSprite->GetMiddlePoint(midPt);
	
	delete midPt;
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_batSprite->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_batSprite->GetTexture());
	if(!result)
	{
		return false;
	}
	return true;
}
/*

void D3DGraphics::RenderTestBackground()
{
	
   //setup spriteBatch 
	std::unique_ptr<SpriteBatch> mySprites(new SpriteBatch(pDirect3D));
	mySprites->Begin();
	RECT dest = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	XMFLOAT2 origin1;
	origin1.x = 0.0f;
	origin1.y = 0.0f;
	mySprites->Draw(background,dest,DirectX::FXMVECTOR(Colors::White));
	mySprites->End();

	
	//
}
*/


// this is the function that cleans up Direct3D and COM
void D3DGraphics::Shutdown(void)
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}


	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	if(m_ballSprite)
	{
		m_ballSprite->Shutdown();
		delete m_ballSprite;
		m_ballSprite = 0;
	}

	if (m_batSprite )
	{
		m_batSprite->Shutdown();
		delete m_ballSprite;
		m_ballSprite = 0;
	}
	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
		// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

}