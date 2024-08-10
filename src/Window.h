#pragma once

namespace Picayune
{
	class Window
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		virtual bool Init(HWND hWnd) { return true; };
		virtual void Shutdown() { } ;
		virtual void ClearScreen() { } ;
		virtual void UpdateScreen() { } ;
	};
}