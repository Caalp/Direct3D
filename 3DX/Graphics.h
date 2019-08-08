#pragma once
#include <d3d11.h>
#include<memory>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearFrame(float red,float gren,float blue);
private:
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwapChain;
	ID3D11DeviceContext* pImmediateContext;
	ID3D11RenderTargetView* pTarget;
};