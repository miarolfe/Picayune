#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Win32Window.h"
#include "imgui/imgui.h"
#include "Window.h"

#ifdef DX11_BUILD
#include "D3D11Window.h"
#endif

#ifdef DX12_BUILD
#include "D3D12Window.h"
#endif

#ifdef OPENGL_BUILD
#include "OpenGLWindow.h"
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{

#ifdef DX11_BUILD
	Picayune::D3D11Window window;
	const LPCWSTR windowName = L"PicayuneDX11";
#endif

#ifdef DX12_BUILD
	Picayune::D3D12Window window;
	const LPCWSTR windowName = L"PicayuneDX12";
#endif

#ifdef OPENGL_BUILD
	// TODO: Known issue, DPI scaling doesn't work properly
	Picayune::OpenGLWindow window;
	const LPCWSTR windowName = L"PicayuneOpenGL";
#endif

#ifndef DX11_BUILD
#ifndef DX12_BUILD
#ifndef OPENGL_BUILD
	Picayune::Window window;
	const LPCWSTR windowName = L"PicayuneUndefined";

#endif
#endif
#endif

	Picayune::Win32WindowParams windowParams =
	{
		&window,
		&window.WindowProc,
		windowName,
		hInstance
	};

	

	HWND hWnd;
	if (!Picayune::GetWin32Window(&hWnd, windowParams))
	{
		MessageBoxW(0, L"Failed to create window", L"Fatal Error", MB_OK);
		return GetLastError();
	}

	if (!window.Init(hWnd))
	{
		MessageBoxW(0, L"Failed to initialize window", L"Fatal Error", MB_OK);
		return 1;
	}

	if (!window.InitDebugUI())
	{
		MessageBoxW(0, L"Failed to initialize debug UI", L"Fatal Error", MB_OK);
		return 1;
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

		window.ClearScreen();
		window.UpdateDebugUI();
		window.UpdateScreen();
	}

	window.Shutdown();
	window.ShutdownDebugUI();
	ImGui::DestroyContext();

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}