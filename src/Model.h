#pragma once

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "InputLayoutManager.h"

namespace Picayune
{
	class Model
	{
	private:
		Mesh* m_meshes = nullptr;
		int m_numMeshes = -1;
		Texture* m_texture = nullptr;
		InputLayoutManager* m_inputLayoutManager = nullptr;

	public:
		bool CreateMeshArray(int numMeshes);
		void DestroyMeshArray();
		Mesh GetMesh(int index);
		void SetMesh(int index, Mesh mesh);
		void DrawMesh(Mesh mesh, ShaderProgram* shaderProgram);
		void Draw(ShaderProgram* shaderProgram);
	};

	struct CreateModelParams
	{
		const char* filepath;
		unsigned int importerFlags;
		Window* window;
		InputLayoutManager* inputLayoutManager;
	};

	bool CreateModel(Model** modelOut, CreateModelParams params);
	void DestroyModel(Model* model);
}