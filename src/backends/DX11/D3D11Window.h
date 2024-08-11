#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11_1.h>
#include "../../Window.h"

namespace Picayune
{
	class D3D11Window : public Window
	{
	private:
		HWND m_hWnd = nullptr;
		ID3D11Device1* m_d3d11Device = nullptr;
		ID3D11DeviceContext1* m_d3d11DeviceContext = nullptr;
		IDXGISwapChain1* m_d3d11SwapChain = nullptr;
		ID3D11RenderTargetView* m_d3d11framebufferRenderTarget = nullptr;

	public:
		bool Init(HWND hWnd);
		bool InitDebugUI();
		void Shutdown();
		void ShutdownDebugUI();
		void ClearScreen();
		void ClearDebugUI();
		void UpdateScreen();
		void UpdateDebugUI();
		void OnResize();
		bool LoadModels(Model* models, int numModels);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	struct CreateD3D11DeviceAndContextParams
	{
		UINT creationFlags;
		D3D_FEATURE_LEVEL* featureLevels;
		UINT numFeatureLevels;
	};

	struct CreateD3D11SwapChainParams
	{
		ID3D11Device1* device;
		HWND hWnd;
		DXGI_SWAP_CHAIN_DESC1 desc;
	};

	struct CreateD3D11FramebufferRenderTargetParams
	{
		IDXGISwapChain1* swapChain;
		ID3D11Device1* d3d11device;
	};

	bool CreateD3D11DeviceAndContext(ID3D11Device1** d3d11DeviceOut,
		ID3D11DeviceContext1** d3d11DeviceContextOut, CreateD3D11DeviceAndContextParams params);
	bool CreateD3D11SwapChain(IDXGISwapChain1** d3d11SwapChainOut, CreateD3D11SwapChainParams params);
	bool CreateD3D11FramebufferRenderTarget(ID3D11RenderTargetView** d3d11FramebufferRenderTargetOut, 
		CreateD3D11FramebufferRenderTargetParams params);

	void DestroyD3D11DeviceAndContext(ID3D11Device1* device, ID3D11DeviceContext1* deviceContext);
	void DestroyD3D11SwapChain(IDXGISwapChain1* swapChain);
	void DestroyD3D11FramebufferRenderTarget(ID3D11RenderTargetView* framebufferRenderTarget);
}