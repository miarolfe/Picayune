#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <glad/glad.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "OpenGLWindow.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Picayune
{
	bool OpenGLWindow::Init(HWND hWnd)
	{
		m_hWnd = hWnd;
		if (!CreateGLDevice())
		{
			MessageBoxW(0, L"Failed to initialize OpenGL Device", L"Fatal Error", MB_OK);
			return false;
		}

		SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

		return true;
	}

	bool OpenGLWindow::InitDebugUI()
	{
		ImGui_ImplWin32_EnableDpiAwareness();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		if (!ImGui_ImplOpenGL3_Init()) return false;
		if (!ImGui_ImplWin32_InitForOpenGL(m_hWnd)) return false;

		return true;
	}

	void OpenGLWindow::Shutdown()
	{
		DestroyGLDevice();
	}

	void OpenGLWindow::ShutdownDebugUI()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
	}

	void OpenGLWindow::ClearScreen()
	{
		glClearColor(0.1f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLWindow::ClearDebugUI()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGLWindow::UpdateScreen()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SwapBuffers(m_hDeviceContext);
	}

	void OpenGLWindow::UpdateDebugUI()
	{
		ImGui::Render();
	}

	void OpenGLWindow::OnResize()
	{
		RECT rect;
		if (GetWindowRect(m_hWnd, &rect))
		{
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;		
		}
	}

	LRESULT CALLBACK OpenGLWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wparam, lparam))
			return true;

		OpenGLWindow* window = (OpenGLWindow*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		LRESULT result = 0;

		switch (msg)
		{
		case WM_SIZE:
		{
			if (window) window->OnResize();
			break;
		}
		case WM_KEYDOWN:
		{
			if (wparam == VK_ESCAPE) PostQuitMessage(0);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			result = DefWindowProcW(hWnd, msg, wparam, lparam);
		}

		return result;
	}

	bool OpenGLWindow::CreateGLDevice()
	{
		m_hDeviceContext = GetDC(m_hWnd);
		PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		const int pixelFormat = ChoosePixelFormat(m_hDeviceContext, &pixelFormatDescriptor);
		if (pixelFormat == 0)
		{
			MessageBoxW(NULL, L"ChoosePixelFormat failed", L"Fatal Error", MB_OK);
			return false;
		}

		if (SetPixelFormat(m_hDeviceContext, pixelFormat, &pixelFormatDescriptor) == FALSE) return false;

		m_hRenderingContext = wglCreateContext(m_hDeviceContext);
		wglMakeCurrent(m_hDeviceContext, m_hRenderingContext);

		if (!gladLoadGL())
		{
			MessageBoxW(m_hWnd, L"Failed to initialize GLAD", L"Fatal Error", MB_OK);
			return false;
		}

		glEnable(GL_FRAMEBUFFER_SRGB);

		//if (!gladLoadGLLoader((GLADloadproc)wglGetProcAddress))
		//{
		//	MessageBoxW(m_hWnd, L"Failed to initialize GLAD GL Loader", L"Fatal Error", MB_OK);
		//	return false;
		//}

		return true;
	}

	void OpenGLWindow::DestroyGLDevice()
	{
		wglMakeCurrent(nullptr, nullptr);
		ReleaseDC(m_hWnd, m_hDeviceContext);
		m_hDeviceContext = nullptr;
		m_hRenderingContext = nullptr;
	}
}