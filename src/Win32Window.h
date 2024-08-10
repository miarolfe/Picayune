#define WIN32_LEAN_AND_MEAN
#define UNICODE 
#include <windows.h>
#include "Window.h"

namespace Picayune
{
	struct Win32WindowParams
	{
		Window* window;
		LRESULT(CALLBACK* windowProc)(HWND, UINT, WPARAM, LPARAM);
		LPCWSTR windowName;
		HINSTANCE hInstance;
	};

	bool GetWin32Window(HWND* windowHandleOut, Win32WindowParams params);
}