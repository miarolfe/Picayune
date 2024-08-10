#include "Win32Window.h"

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

		RECT initialRect = { 0, 0, 2560, 1440 };
		AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
		LONG initialWidth = initialRect.right - initialRect.left;
		LONG initialHeight = initialRect.bottom - initialRect.top;

		HWND hWnd = CreateWindowExW
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
			params.window
		);

		if (!hWnd)
		{
			return false;
		}

		*windowHandleOut = hWnd;
		return true;
	}
}