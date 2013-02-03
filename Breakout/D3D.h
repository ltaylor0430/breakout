#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dcompiler.h>

// include the Direct3D Library file
#pragma comment(lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class D3D
{
public:
	D3D();
	D3D(HWND hWnd);
	~D3D(void);

    bool InitD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);    // sets up and initializes Direct3D	
	// function prototypes
	void Shutdown(void);        // closes Direct3D and releases memory
	
	//Render Functions
	void BeginFrame(float r, float g, float b, float a);
	void EndFrame();
	void TurnZBufferOn();
	void TurnZBufferOff();
	
	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);
	ID3D11DeviceContext* GetDeviceContext(); //get device context
	ID3D11Device* GetDevice();         //get device interface
	private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
	ID3D11Device *pDevice;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *pDirect3D;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer;		// the pointer that holds all the information about the render target.
	ID3D11VertexShader *pVS;    // the vertex shader
	ID3D11PixelShader *pPS;     // the pixel shader
	ID3D11Buffer *pVBuffer;     // the vertex buffer
	ID3D11InputLayout *pLayout;    // global
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilState *m_depthStencilState;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RasterizerState *m_rasterState;
	UINT SCREEN_WIDTH;
	UINT SCREEN_HEIGHT;
	D3DXMATRIX m_projectionMatrix;  //projection
	D3DXMATRIX m_worldMatrix;   //world matrix
	D3DXMATRIX m_orthoMatrix;  //ortho matrix used for 2D Drawing
	ID3D11DepthStencilState *m_depthDisabledStencilState; //Used for 2D Drawing disable Z buffer
	
};

