#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Texture.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Window.h"

namespace Picayune
{
	struct Mesh
	{
		VertexBuffer* vertexBuffer = nullptr;
		IndexBuffer* indexBuffer = nullptr;
		Texture* textures = nullptr;
	};

	struct CreateMeshParams
	{
		aiMesh* rawMesh;
		const aiScene* rawScene;
		Window* window;
	};

	bool CreateMesh(Mesh** meshOut, CreateMeshParams params);
	void DestroyMesh(Mesh* mesh);
}
