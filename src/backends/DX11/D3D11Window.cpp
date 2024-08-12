#define WIN32_LEAN_AND_MEAN
#define UNICODE 
#include <windows.h>
#include <d3d11_1.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "D3D11Window.h"

/*

HINSTANCE = handle to an instance
WNDCLASSEXW = window class, EX = has two extra members (size of structure, handle to small icon), W = wide (Unicode) strings
CS_HREDRAW, CS_VREDRAW = flags to tell window to redraw when resized,
LRESULT = signed result of message processing
VK_ = virtual keycode
HWND = (H)andle to a (W)i(ND)ow
*/

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Picayune
{
	bool D3D11Window::Init(HWND hWnd)
	{
		m_hWnd = hWnd;

		Picayune::CreateD3D11DeviceAndContextParams d3d11DeviceAndContextParams;
		d3d11DeviceAndContextParams.creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG)
		d3d11DeviceAndContextParams.creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		d3d11DeviceAndContextParams.featureLevels = featureLevels;
		d3d11DeviceAndContextParams.numFeatureLevels = 1;

		if (!Picayune::CreateD3D11DeviceAndContext(&m_d3d11Device, &m_d3d11DeviceContext, d3d11DeviceAndContextParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 device and context", L"Fatal Error", MB_OK);
			return false;
		}

#ifdef DEBUG
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

		Picayune::CreateD3D11SwapChainParams d3d11SwapChainParams;
		d3d11SwapChainParams.device = m_d3d11Device;
		d3d11SwapChainParams.hWnd = m_hWnd;
		d3d11SwapChainParams.desc = d3d11SwapChainDesc;
		if (!CreateD3D11SwapChain(&m_d3d11SwapChain, d3d11SwapChainParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 swap chain", L"Fatal Error", MB_OK);
			return false;
		}

		Picayune::CreateD3D11FramebufferRenderTargetParams d3d11FramebufferRenderTargetParams;
		d3d11FramebufferRenderTargetParams.swapChain = m_d3d11SwapChain;
		d3d11FramebufferRenderTargetParams.d3d11device = m_d3d11Device;
		if (!Picayune::CreateD3D11FramebufferRenderTarget(&m_d3d11framebufferRenderTarget, d3d11FramebufferRenderTargetParams))
		{
			MessageBoxW(0, L"Failed to create D3D11 swap chain", L"Fatal Error", MB_OK);
			return false;
		}

		SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

		return true;
	}

	bool D3D11Window::InitDebugUI()
	{
		ImGui_ImplWin32_EnableDpiAwareness();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		if (!ImGui_ImplDX11_Init(m_d3d11Device, m_d3d11DeviceContext)) return false;
		if (!ImGui_ImplWin32_Init(m_hWnd)) return false;

		return true;
	}

	void D3D11Window::Shutdown() 
	{
		DestroyD3D11FramebufferRenderTarget(m_d3d11framebufferRenderTarget);
		DestroyD3D11SwapChain(m_d3d11SwapChain);
		DestroyD3D11DeviceAndContext(m_d3d11Device, m_d3d11DeviceContext);
	}

	void D3D11Window::ShutdownDebugUI()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();

	}

	void D3D11Window::ClearScreen()
	{
		FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
		m_d3d11DeviceContext->OMSetRenderTargets(1, &m_d3d11framebufferRenderTarget, nullptr);
		m_d3d11DeviceContext->ClearRenderTargetView(m_d3d11framebufferRenderTarget, backgroundColor);
	}

	void D3D11Window::ClearDebugUI()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void D3D11Window::UpdateScreen()
	{
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		m_d3d11SwapChain->Present(1, 0);
	}

	void D3D11Window::UpdateDebugUI()
	{		
		ImGui::Render();
	}

	void D3D11Window::OnResize()
	{
		if (m_d3d11SwapChain)
		{
			m_d3d11DeviceContext->OMSetRenderTargets(0, 0, 0); // ???
			DestroyD3D11FramebufferRenderTarget(m_d3d11framebufferRenderTarget);

			HRESULT hResult;
			
			// Keep existing buffer count, format; resize buffers to hWnd client rect
			hResult = m_d3d11SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			if (FAILED(hResult))
			{
				MessageBoxW(0, L"Couldn't resize D3D11 buffers", L"Error", MB_OK);
			}

			if (!CreateD3D11FramebufferRenderTarget
			(
				&m_d3d11framebufferRenderTarget,
				{
					m_d3d11SwapChain,
					m_d3d11Device
				}
			)) 
			{
				MessageBoxW(0, L"Couldn't create D3D11 framebuffer render target", L"Error", MB_OK);
			}
		}
	}

	ID3D11Device1* D3D11Window::GetD3DDevice()
	{
		return m_d3d11Device;
	}

	LRESULT CALLBACK D3D11Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		D3D11Window* window = (D3D11Window*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		LRESULT result = 0;

		switch (msg)
		{
		case WM_SIZE:
		{
			if (window) window->OnResize();
			break;
		}
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE) PostQuitMessage(0);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			result = DefWindowProcW(hWnd, msg, wParam, lParam);
		}

		return result;
	}

	bool CreateD3D11DeviceAndContext(ID3D11Device1** d3d11DeviceOut,
		ID3D11DeviceContext1** d3d11DeviceContextOut, CreateD3D11DeviceAndContextParams params)
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

	bool CreateD3D11SwapChain(IDXGISwapChain1** d3d11SwapChainOut, CreateD3D11SwapChainParams params)
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
			params.hWnd,
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

	bool CreateD3D11FramebufferRenderTarget(ID3D11RenderTargetView** d3d11FramebufferRenderTargetOut, CreateD3D11FramebufferRenderTargetParams params)
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

	void DestroyD3D11DeviceAndContext(ID3D11Device1* device, ID3D11DeviceContext1* deviceContext)
	{
		device->Release();
		deviceContext->Release();
	}

	void DestroyD3D11SwapChain(IDXGISwapChain1* swapChain)
	{
		swapChain->Release();
	}

	void DestroyD3D11FramebufferRenderTarget(ID3D11RenderTargetView* framebufferRenderTarget)
	{
		framebufferRenderTarget->Release();
	}
}

