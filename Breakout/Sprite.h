////////////////////////////////////////////////////////////////////////////////
// Filename: Sprite.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SPRITE_H_
#define _SPRITE_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Sprite
////////////////////////////////////////////////////////////////////////////////
class Sprite
{
private:

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Sprite();
	Sprite(const Sprite&);
	~Sprite();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);
	bool IsRender();
	D3DXVECTOR2 *GetMiddlePoint(D3DXVECTOR2*);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	
public:
	int m_previousPosX, m_previousPosY;
	
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
//The Sprite will need to maintain some extra information that a 3D model wouldn't such as the screen size, the bitmap size, and the last place it was rendered. We have added extra private variables here to track that extra information.

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	bool m_IsDrawn;
	D3DXVECTOR2 m_bitmapMiddle;
};

#endif