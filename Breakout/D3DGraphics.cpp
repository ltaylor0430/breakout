#include "StdAfx.h"
#include "D3DGraphics.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"


using namespace DirectX;
D3DGraphics::D3DGraphics()
{}
D3DGraphics::D3DGraphics( HWND hWnd )
{

}


D3DGraphics::~D3DGraphics(void)
{
	CleanD3D(); //make sure memory is clear.
}

// this function initializes and prepares Direct3D for use
void D3DGraphics::InitD3D(HWND hWnd, UINT _SCREEN_HEIGHT, UINT _SCREEN_WIDTH)
{

	HRESULT hr = S_OK;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;
	SCREEN_WIDTH = _SCREEN_WIDTH;
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );


    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                   // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
    scd.BufferDesc.Width = _SCREEN_WIDTH;                   // set the back buffer width
    scd.BufferDesc.Height = _SCREEN_HEIGHT;                 // set the back buffer height
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
    scd.OutputWindow = hWnd;                               // the window to be used
    scd.SampleDesc.Count = 4;                              // how many multisamples
    scd.Windowed = TRUE;                                   // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
   
    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &scd, &swapchain, &pDevice, &g_featureLevel, &pDirect3D );
        if( SUCCEEDED( hr ) )
            break;
    }
  

    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    pDirect3D->OMSetRenderTargets(1, &backbuffer, NULL);


    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)SCREEN_WIDTH;
    viewport.Height = (float)SCREEN_HEIGHT;

    pDirect3D->RSSetViewports(1, &viewport);

    }

void D3DGraphics::InitPipeline()
{
	//load shaders,models,etc. 
	//depending on level?? switch statement maybe..
	HRESULT hr = S_OK;
	hr = CreateWICTextureFromFile(pDevice,pDirect3D,L"images/stars.jpg",NULL,&background,NULL);
	
   if( FAILED(hr) )
    {
        return;
    
	}
	
}

void D3DGraphics::BeginFrame(float r, float g, float b, float a)
{
	 // clear the back buffer 
	pDirect3D->ClearRenderTargetView(backbuffer, D3DXCOLOR(r, g, b, a));

}

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
void D3DGraphics::EndFrame()
{
	// switch the back buffer and the front buffer
    swapchain->Present(1, 0);
}


// this is the function that cleans up Direct3D and COM
void D3DGraphics::CleanD3D(void)
{
	if (swapchain)
	    swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

  
	if (swapchain)
	{
		swapchain->Release();
		swapchain = NULL;
	}
	if (backbuffer)
	{
		backbuffer->Release();
		backbuffer = NULL;
	}
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
}