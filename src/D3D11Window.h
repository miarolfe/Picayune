#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11_1.h>

namespace Picayune
{
	struct Win32WindowParams
	{
		LRESULT(CALLBACK* windowProc)(HWND, UINT, WPARAM, LPARAM);
		HINSTANCE hInstance;
		LPCWSTR windowName;
	};

	struct D3D11DeviceAndContextParams
	{
		UINT creationFlags;
		D3D_FEATURE_LEVEL* featureLevels;
		UINT numFeatureLevels;
	};

	struct D3D11SwapChainParams
	{
		ID3D11Device1* device;
		HWND hwnd;
		DXGI_SWAP_CHAIN_DESC1 desc;
	};

	struct D3D11FramebufferRenderTargetParams
	{
		IDXGISwapChain1* swapChain;
		ID3D11Device1* d3d11device;
	};

	bool GetWin32Window(HWND* windowHandleOut, Win32WindowParams params);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool CreateD3D11DeviceAndContext(ID3D11Device1** d3d11DeviceOut,
		ID3D11DeviceContext1** d3d11DeviceContextOut, D3D11DeviceAndContextParams params);
	bool CreateD3D11SwapChain(IDXGISwapChain1** d3d11SwapChainOut, D3D11SwapChainParams params);
	bool CreateD3D11FramebufferRenderTarget(ID3D11RenderTargetView** d3d11FramebufferRenderTargetOut, 
		D3D11FramebufferRenderTargetParams params);
}