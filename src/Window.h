#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#pragma once

namespace Picayune
{
	class Window
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

		virtual bool Init(HWND hWnd) { return true; };
		virtual bool InitDebugUI() { return true; };
		virtual void Shutdown() { };
		virtual void ShutdownDebugUI() { };
		virtual void ClearScreen() { };
		virtual void ClearDebugUI() { };
		virtual void UpdateScreen() { };
		virtual void UpdateDebugUI() { };
		virtual void OnResize() { };
		virtual void* GetDevice() = 0;
	};
}