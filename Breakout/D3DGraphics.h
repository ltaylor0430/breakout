#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dcompiler.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class D3DGraphics
{
public:
	D3DGraphics();
	D3DGraphics(HWND hWnd);
	~D3DGraphics(void);

    void InitD3D(HWND hWnd,UINT SCREEN_HEIGHT, UINT SCREEN_WIDTH);    // sets up and initializes Direct3D	
	// function prototypes
	void CleanD3D(void);        // closes Direct3D and releases memory
	void BeginFrame(float r, float g, float b, float a);
	void EndFrame();

	//Render Functions
	void RenderTestBackground();
	void InitPipeline();
	private:
	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
	ID3D11Device *pDevice;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *pDirect3D;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer;		// the pointer that holds all the information about the render target.
	ID3D11VertexShader *pVS;    // the vertex shader
	ID3D11PixelShader *pPS;     // the pixel shader
	ID3D11Buffer *pVBuffer;     // the vertex buffer
	ID3D11InputLayout *pLayout;    // global
	ID3D11ShaderResourceView *background; //background image
	UINT SCREEN_WIDTH;
	UINT SCREEN_HEIGHT;
	
	
};

