#pragma once

#include "Model.h"

namespace Picayune
{
	class Window
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		virtual bool Init(HWND hWnd) { return true; };
		virtual bool InitDebugUI() { return true; };
		virtual void Shutdown() { };
		virtual void ShutdownDebugUI() { };
		virtual void ClearScreen() { };
		virtual void ClearDebugUI() { };
		virtual void UpdateScreen() { };
		virtual void UpdateDebugUI() { };
		virtual void OnResize() { };
		
		virtual bool LoadModels(Model* models, int numModels) { return true; };
	};
}