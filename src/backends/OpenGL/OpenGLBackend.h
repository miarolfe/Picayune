#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../../GraphicsBackend.h"
#include <Windows.h>

namespace Picayune
{
	class OpenGLBackend : public GraphicsBackend
	{
	public:
		Window* GetWindow();
		void SetWindow(Window* window);
		InputLayoutManager* GetInputLayoutManager();
		void SetInputLayoutManager(InputLayoutManager* inputLayoutManager);
	};

	bool CreateOpenGLBackend(HWND hWnd);
	void DestroyOpenGLBackend();
}