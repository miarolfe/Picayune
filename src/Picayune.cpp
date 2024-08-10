#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Win32Window.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "Window.h"

#ifdef DX11_BUILD
#include "D3D11Window.h"
#include "imgui/backends/imgui_impl_dx11.h"
#endif

#ifdef DX12_BUILD
#include "imgui/backends/imgui_impl_dx12.h"
#endif

#ifdef OPENGL_BUILD
#include <GL/GL.h>
#include "imgui/backends/imgui_impl_opengl3.h"
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
	ImGui_ImplWin32_EnableDpiAwareness();

#ifdef DX11_BUILD
	Picayune::D3D11Window window;
#endif

#ifndef DX11_BUILD
	Picayune::Window window;
#endif

	Picayune::Win32WindowParams windowParams =
	{
		&window.WindowProc,
		L"Picayune",
		hInstance,
		&window
	};

	HWND hWnd;
	if (!Picayune::GetWin32Window(&hWnd, windowParams))
	{
		MessageBoxW(0, L"Failed to create window", L"Fatal Error", MB_OK);
		return GetLastError();
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);

	window.Init(hWnd);
	
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

		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Render();
		
		window.UpdateScreen();
	}

	window.Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}