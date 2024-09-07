#include "GraphicsBackend.h"

namespace Picayune
{
	Window* GraphicsBackend::GetWindow()
	{
		return m_window;
	}

	void GraphicsBackend::SetWindow(Window* window)
	{
		m_window = window;
	}

	InputLayoutManager* GraphicsBackend::GetInputLayoutManager()
	{
		return m_inputLayoutManager;
	}

	void GraphicsBackend::SetInputLayoutManager(InputLayoutManager* inputLayoutManager)
	{
		m_inputLayoutManager = inputLayoutManager;
	}
}