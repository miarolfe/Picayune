#pragma once

#include "Mesh.h"

namespace Picayune
{
	class Model
	{
	private:
		Mesh* m_meshes = nullptr;
		Texture* m_texture = nullptr;

	public:
		bool CreateMeshArray(int numMeshes);
		void DestroyMeshArray();
		Mesh GetMesh(int index);
		void SetMesh(int index, Mesh mesh);
	};

	struct CreateModelParams
	{
		const char* filepath;
		unsigned int importerFlags;
	};

	bool CreateModel(Model** modelOut, CreateModelParams params);
	void DestroyModel(Model* model);
}