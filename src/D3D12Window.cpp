#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <d3d12.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx12.h"
#include "D3D12Window.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Picayune
{
	bool D3D12Window::Init(HWND hWnd)
	{
		m_hWnd = hWnd;

		return true;
	}

	bool D3D12Window::InitDebugUI()
	{
		return true;
	}

	void D3D12Window::Shutdown()
	{

	}

	void D3D12Window::ShutdownDebugUI()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX12_Shutdown();
		ImGui::DestroyContext();
	}

	void D3D12Window::ClearScreen()
	{

	}

	void D3D12Window::UpdateScreen()
	{

	}

	void D3D12Window::UpdateDebugUI()
	{

	}

	void D3D12Window::OnResize()
	{

	}

	LRESULT CALLBACK D3D12Window::WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wparam, lparam))
			return true;

		LRESULT result = 0;

		switch (msg)
		{
		case WM_SIZE:
		{
			break;
		}
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
			result = DefWindowProcW(hWnd, msg, wparam, lparam);
		}

		return result;
	}
}