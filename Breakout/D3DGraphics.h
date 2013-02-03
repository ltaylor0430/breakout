#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dcompiler.h>
#include "D3D.h"
#include "CameraClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h" 
#include "Sprite.h"
// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


//globals
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;

class D3DGraphics
{
public:
	D3DGraphics();
	D3DGraphics(HWND hWnd);
	~D3DGraphics(void);

  	// function prototypes
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void EndFrame();
	void Shutdown();
	//Render Functions
	bool Render(float rotation,float playerX,float playerY);
	//Paddle Sprite needs to accept offsets for player movement
private:
	bool RenderSprite(D3DXMATRIX worldMatrix,D3DXMATRIX viewMatrix,D3DXMATRIX 
						projectionMatrix,D3DXMATRIX  orthoMatrix,float rotation,float playerX, float playerY);
	bool RenderPaddle(D3DXMATRIX worldMatrix,D3DXMATRIX viewMatrix,D3DXMATRIX 
						projectionMatrix,D3DXMATRIX  orthoMatrix,float rotation,float playerX, float playerY);
private:
	
	D3D *m_D3D;  //Direct 3d class  
	CameraClass* m_Camera; //camera
	//models//////////////
	//Sprites* m_Model;
	Sprite* m_ballSprite;
	Sprite* m_bgSprite;
	Sprite* m_barSprites;
	Sprite* m_batSprite;
	//shaders
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	ID3D11ShaderResourceView *background; //background image
};

