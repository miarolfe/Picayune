#pragma once

#include "Window.h"
#include "InputLayoutManager.h"

namespace Picayune
{
	class GraphicsBackend
	{
	private:
		Window* m_window;
		InputLayoutManager* m_inputLayoutManager;

	public:
		Window* GetWindow();
		void SetWindow(Window* window);
		InputLayoutManager* GetInputLayoutManager();
		void SetInputLayoutManager(InputLayoutManager* inputLayoutManager);
	};
}