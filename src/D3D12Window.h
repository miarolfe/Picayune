#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d12.h>
#include "Window.h"

namespace Picayune
{
	class D3D12Window : public Window
	{
	private:
		HWND m_hWnd;
		

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
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	};
}