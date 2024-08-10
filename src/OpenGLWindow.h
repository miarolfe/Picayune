#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>
#include "Window.h"

namespace Picayune
{
	class OpenGLWindow : public Window
	{
	private:
		HDC m_hDeviceContext; // HDC = handle to device context
		HGLRC m_hRenderingContext; // HLGRC = handle to OpenGL rendering context
		HWND m_hWnd;

	public:
		bool Init(HWND hWnd);
		bool InitDebugUI();
		void Shutdown();
		void ShutdownDebugUI();
		void ClearScreen();
		void UpdateScreen();
		void UpdateDebugUI();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		bool CreateGLDevice();
		void DestroyGLDevice();
	};

	
}