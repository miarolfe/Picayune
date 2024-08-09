#define WIN32_LEAN_AND_MEAN
#define UNICODE 
#include <windows.h>
#include <d3d11_1.h>
#include <assert.h>

#include "D3D11Window.h"

/*

HINSTANCE = handle to an instance
WNDCLASSEXW = window class, EX = has two extra members (size of structure, handle to small icon), W = wide (Unicode) strings
CS_HREDRAW, CS_VREDRAW = flags to tell window to redraw when resized,
LRESULT = signed result of message processing
VK_ = virtual keycode
HWND = (H)andle to a (W)i(ND)ow
*/

namespace Picayune
{
	bool GetWin32Window(HWND* windowHandleOut, Win32WindowParams params)
	{
		WNDCLASSEXW winClass = {};
		winClass.cbSize = sizeof(WNDCLASSEXW);
		winClass.style = CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc = params.windowProc;
		winClass.hInstance = params.hInstance;
		winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
		winClass.hCursor = LoadCursorW(0, IDC_ARROW);
		winClass.lpszClassName = L"WindowClass";
		winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

		if (!RegisterClassExW(&winClass))
		{
			return false;
		}

		RECT initialRect = { 0, 0, 960, 540 };
		AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
		LONG initialWidth = initialRect.right - initialRect.left;
		LONG initialHeight = initialRect.bottom - initialRect.top;

		HWND hwnd = CreateWindowExW
		(
			WS_EX_OVERLAPPEDWINDOW,
			winClass.lpszClassName,
			params.windowName,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			initialWidth,
			initialHeight,
			0,
			0,
			params.hInstance,
			0
		);

		if (!hwnd)
		{
			return false;
		}

		*windowHandleOut = hwnd;
		return true;
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		LRESULT result = 0;

		switch (msg)
		{
		case WM_KEYDOWN:
		{
			if (wparam == VK_ESCAPE) PostQuitMessage(0);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			result = DefWindowProcW(hwnd, msg, wparam, lparam);
		}

		return result;
	}

	bool CreateD3D11DeviceAndContext(ID3D11Device1** d3d11DeviceOut,
		ID3D11DeviceContext1** d3d11DeviceContextOut, D3D11DeviceAndContextParams params)
	{
		ID3D11Device* baseDevice;
		ID3D11DeviceContext* baseDeviceContext;

		HRESULT hResult = D3D11CreateDevice
		(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			params.creationFlags,
			params.featureLevels,
			params.numFeatureLevels,
			D3D11_SDK_VERSION,
			&baseDevice,
			0,
			&baseDeviceContext
		);

		if (FAILED(hResult))
		{
			return false;
		}

		ID3D11Device1* d3d11Device;
		ID3D11DeviceContext1* d3d11DeviceContext;

		hResult = baseDevice->QueryInterface
		(
			__uuidof(ID3D11Device1),
			(void**)&d3d11Device
		);

		if (FAILED(hResult))
		{
			return false;
		}
		baseDevice->Release();

		hResult = baseDeviceContext->QueryInterface
		(
			__uuidof(ID3D11DeviceContext1),
			(void**)&d3d11DeviceContext
		);

		if (FAILED(hResult))
		{
			return false;
		}
		baseDeviceContext->Release();

		*d3d11DeviceOut = d3d11Device;
		*d3d11DeviceContextOut = d3d11DeviceContext;

		return true;
	}

	bool CreateD3D11SwapChain(IDXGISwapChain1** d3d11SwapChainOut, D3D11SwapChainParams params)
	{
		IDXGISwapChain1* d3d11SwapChain;
		IDXGIFactory2* dxgiFactory;
		IDXGIDevice1* dxgiDevice;
		HRESULT hResult = params.device->QueryInterface
		(
			__uuidof(IDXGIDevice1),
			(void**)&dxgiDevice
		);
		if (FAILED(hResult)) return false;

		IDXGIAdapter* dxgiAdapter;
		hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
		dxgiDevice->Release();
		if (FAILED(hResult)) return false;

		hResult = dxgiAdapter->GetParent
		(
			__uuidof(IDXGIFactory2),
			(void**)&dxgiFactory
		);
		dxgiAdapter->Release();
		if (FAILED(hResult)) return false;

		hResult = dxgiFactory->CreateSwapChainForHwnd
		(
			params.device,
			params.hwnd,
			&params.desc,
			0,
			0,
			&d3d11SwapChain
		);
		dxgiFactory->Release();
		if (FAILED(hResult)) return false;

		*d3d11SwapChainOut = d3d11SwapChain;
		return true;
	}

	bool CreateD3D11FramebufferRenderTarget(ID3D11RenderTargetView** d3d11FramebufferRenderTargetOut, D3D11FramebufferRenderTargetParams params)
	{
		ID3D11RenderTargetView* d3d11FramebufferRenderTarget;
		ID3D11Texture2D* d3d11FrameBuffer;
		HRESULT hResult = params.swapChain->GetBuffer
		(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&d3d11FrameBuffer
		);
		if (FAILED(hResult)) return false;

		hResult = params.d3d11device->CreateRenderTargetView
		(
			d3d11FrameBuffer,
			0,
			&d3d11FramebufferRenderTarget
		);
		d3d11FrameBuffer->Release();
		if (FAILED(hResult)) return false;

		*d3d11FramebufferRenderTargetOut = d3d11FramebufferRenderTarget;

		return true;
	}

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
	{
		Win32WindowParams windowParams =
		{
			&WindowProc,
			hInstance,
			L"PicayuneD3D11"
		};

		HWND hwnd;
		if (!GetWin32Window(&hwnd, windowParams))
		{
			MessageBoxW(0, L"Failed to create window", L"Fatal Error", MB_OK);
			return GetLastError();
		}

		ID3D11Device1* d3d11Device = nullptr;
		ID3D11DeviceContext1* d3d11DeviceContext = nullptr;
		IDXGISwapChain1* d3d11SwapChain = nullptr;
		ID3D11RenderTargetView* d3d11framebufferRenderTarget = nullptr;

		D3D11DeviceAndContextParams d3d11DeviceAndContextParams;
		d3d11DeviceAndContextParams.creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG_BUILD)
		d3d11DeviceAndContextParams.creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		d3d11DeviceAndContextParams.featureLevels = featureLevels;
		d3d11DeviceAndContextParams.numFeatureLevels = 1;

		if (!CreateD3D11DeviceAndContext(&d3d11Device, &d3d11DeviceContext, d3d11DeviceAndContextParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 device and context", L"Fatal Error", MB_OK);
			return GetLastError();
		}

#ifdef DEBUG_BUILD
		ID3D11Debug* d3dDebug = nullptr;
		d3d11Device->QueryInterface(
			__uuidof(ID3D11Debug),
			(void**)&d3dDebug
		);

		if (d3dDebug)
		{
			ID3D11InfoQueue* d3dInfoQueue = nullptr;
			if (SUCCEEDED(d3dDebug->QueryInterface(
				__uuidof(ID3D11InfoQueue),
				(void**)&d3dInfoQueue
			)) {
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
				d3dInfoQueue->Release();
			}
			d3dDebug->Release();
		}
#endif

		DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
		d3d11SwapChainDesc.Width = 0; // use window width
		d3d11SwapChainDesc.Height = 0; // use window height
		d3d11SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		d3d11SwapChainDesc.SampleDesc.Count = 1;
		d3d11SwapChainDesc.SampleDesc.Quality = 0;
		d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		d3d11SwapChainDesc.BufferCount = 2;
		d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		d3d11SwapChainDesc.Flags = 0;

		D3D11SwapChainParams d3d11SwapChainParams;
		d3d11SwapChainParams.device = d3d11Device;
		d3d11SwapChainParams.hwnd = hwnd;
		d3d11SwapChainParams.desc = d3d11SwapChainDesc;
		if (!CreateD3D11SwapChain(&d3d11SwapChain, d3d11SwapChainParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 swap chain", L"Fatal Error", MB_OK);
			return GetLastError();
		}

		D3D11FramebufferRenderTargetParams d3d11FramebufferRenderTargetParams;
		d3d11FramebufferRenderTargetParams.swapChain = d3d11SwapChain;
		d3d11FramebufferRenderTargetParams.d3d11device = d3d11Device;
		if (!CreateD3D11FramebufferRenderTarget(&d3d11framebufferRenderTarget, d3d11FramebufferRenderTargetParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 swap chain", L"Fatal Error", MB_OK);
			return GetLastError();
		}

		bool running = true;
		while (running)
		{
			MSG msg = {};
			while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) running = false;
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
			d3d11DeviceContext->ClearRenderTargetView(d3d11framebufferRenderTarget, backgroundColor);
			d3d11SwapChain->Present(1, 0);
		}

		return 0;
	}
}