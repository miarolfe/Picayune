#include "OpenGLBackend.h"
#include "OpenGLWindow.h"
#include "OpenGLInputLayoutManager.h"

namespace Picayune
{
	bool CreateOpenGLBackend(OpenGLBackend** openGLBackendOut, HWND hWnd)
	{
		OpenGLBackend* openGLBackend = new OpenGLBackend;
		if (!openGLBackend)
		{
			return false;
		}

		if (!openGLBackend->GetWindow()->Init(hWnd))
		{
			MessageBoxW(0, L"Failed to initialize window", L"Fatal Error", MB_OK);
			return false;
		}

		if (!openGLBackend->GetWindow()->InitDebugUI())
		{
			MessageBoxW(0, L"Failed to initialize debug UI", L"Fatal Error", MB_OK);
			return false;
		}

		OpenGLInputLayoutManager* inputLayoutManager;
		if (!CreateOpenGLInputLayoutManager(&inputLayoutManager))
		{
			MessageBoxW(0, L"Failed to create OpenGL Input Layout Manager", L"Fatal Error", MB_OK);
			return false;
		}

		openGLBackend->SetInputLayoutManager((InputLayoutManager*) inputLayoutManager);

		if (!openGLBackend->GetInputLayoutManager()->Init())
		{
			MessageBoxW(0, L"Failed to initialize OpenGL Input Layout Manager", L"Fatal Error", MB_OK);
			return false;
		}

		*openGLBackendOut = openGLBackend;

		return true;
	}

	void DestroyOpenGLBackend(OpenGLBackend* openGLBackend)
	{
		if (openGLBackend)
		{
			openGLBackend->GetWindow()->ShutdownDebugUI();
			openGLBackend->GetWindow()->Shutdown();
			openGLBackend->GetInputLayoutManager()->Shutdown();
			DestroyOpenGLInputLayoutManager((OpenGLInputLayoutManager*) openGLBackend->GetInputLayoutManager());

			delete openGLBackend;
		}
	}
}