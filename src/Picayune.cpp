#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Win32Window.h"
#include "imgui/imgui.h"
#include "Window.h"
#include "Camera.h"
#include "Model.h"

#ifdef DX11_BUILD
#include "D3D11Window.h"
#endif

#ifdef DX12_BUILD
#include "D3D12Window.h"
#endif

#ifdef OPENGL_BUILD
#include "OpenGLWindow.h"
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
	SetProcessDPIAware();

#ifdef DX11_BUILD
	Picayune::D3D11Window window;
	const LPCWSTR windowName = L"PicayuneDX11";
#endif

#ifdef DX12_BUILD
	Picayune::D3D12Window window;
	const LPCWSTR windowName = L"PicayuneDX12";
#endif

#ifdef OPENGL_BUILD
	// TODO: Known issue, DPI scaling doesn't work properly
	Picayune::OpenGLWindow window;
	const LPCWSTR windowName = L"PicayuneOpenGL";
#endif

#ifndef DX11_BUILD
#ifndef DX12_BUILD
#ifndef OPENGL_BUILD
	Picayune::Window window;
	const LPCWSTR windowName = L"PicayuneUndefined";

#endif
#endif
#endif

	Picayune::Win32WindowParams windowParams =
	{
		&window,
		&window.WindowProc,
		windowName,
		hInstance
	};

	HWND hWnd;
	if (!Picayune::GetWin32Window(&hWnd, windowParams))
	{
		MessageBoxW(0, L"Failed to create window", L"Fatal Error", MB_OK);
		return GetLastError();
	}

	if (!window.Init(hWnd))
	{
		MessageBoxW(0, L"Failed to initialize window", L"Fatal Error", MB_OK);
		return 1;
	}

	if (!window.InitDebugUI())
	{
		MessageBoxW(0, L"Failed to initialize debug UI", L"Fatal Error", MB_OK);
		return 1;
	}

	Picayune::Camera* camera;
	Picayune::CreateCameraParams cameraParams =
	{
		0.0f, 0.0f, -10.0f, // position
		0.0f, 1.0f, 0.0f,	// worldUp
		-90.0f,				// yaw
		0.0f,				// pitch
		45.0f,				// vertical FOV
		16.0f / 9.0f,		// aspect ratio TODO: derive this
		0.1f,				// near plane
		100.0f				// far plane
	};


	if (!Picayune::CreateCamera(&camera, cameraParams))
	{
		MessageBoxW(0, L"Failed to create camera", L"Fatal Error", MB_OK);
		return 1;
	}

	Picayune::Model* model;
	Picayune::CreateModelParams modelParams =
	{
		"assets/sphere.fbx",
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
	};
	if (!Picayune::CreateModel(&model, modelParams))
	{
		MessageBoxW(0, L"Failed to create model", L"Fatal Error", MB_OK);
		return 1;
	}
	
	bool running = true;
	while (running)
	{
		MSG msg = {};
		while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) running = false;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		window.ClearScreen();
		window.ClearDebugUI();

		ImGui::Begin("Test", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Test");
		glm::vec3 vertexPos = model->GetMesh(0).vertices[0].position;
		ImGui::Text("%f %f %f", vertexPos.x, vertexPos.y, vertexPos.z);
		ImGui::Text("%d %d %d", model->GetMesh(0).indices[0], model->GetMesh(0).indices[100], model->GetMesh(0).indices[2]);
		ImGui::End();

		window.UpdateDebugUI();
		window.UpdateScreen();
	}

	Picayune::DestroyCamera(camera);
	window.Shutdown();
	window.ShutdownDebugUI();

	return 0;
}