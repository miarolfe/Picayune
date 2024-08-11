#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Vertex.h"
#include "Texture.h"

namespace Picayune
{
	struct Mesh
	{
		Vertex* vertices;
		unsigned int* indices;
		Texture* textures;
	};

	struct CreateMeshParams
	{
		aiMesh* rawMesh;
		const aiScene* rawScene;
	};

	bool CreateMesh(Mesh** meshOut, CreateMeshParams params);
	void DestroyMesh(Mesh* mesh);
}
