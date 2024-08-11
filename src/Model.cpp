#include <cstdlib>
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Vertex.h"
#include "Model.h"

namespace Picayune
{
	bool Model::CreateMeshArray(int numMeshes)
	{
		// DestroyMeshArray();

		Mesh* meshes = (Mesh*) malloc(numMeshes * sizeof(Mesh));
		if (!meshes)
		{
			return false;
		}

		m_meshes = meshes;

		return true;	
	}

	void Model::DestroyMeshArray()
	{
		if (m_meshes) free(m_meshes);
	}

	Mesh Model::GetMesh(int index)
	{
		return m_meshes[index];
	}

	void Model::SetMesh(int index, Mesh mesh)
	{
		m_meshes[index] = mesh; 
	}

	bool CreateModel(Model** modelOut, CreateModelParams params)
	{
		Model* model = (Model*) malloc(sizeof(Model));
		if (!model)
		{
			return false;
		}

		Assimp::Importer importer;
		const aiScene* rawScene = importer.ReadFile(params.filepath, params.importerFlags);

		if (!rawScene) return false;
		if (!rawScene->mRootNode) return false;
		// if (!rawScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) return false;

		int numMeshes = rawScene->mNumMeshes;
		model->CreateMeshArray(numMeshes);

		for (int i = 0; i < numMeshes; i++)
		{
			aiMesh* rawMesh = rawScene->mMeshes[i];

			Mesh* mesh;
			CreateMeshParams meshParams =
			{
				rawMesh,
				rawScene,
				params.window
			};
			if (!CreateMesh(&mesh, meshParams))
			{
				return false;
			}
			model->SetMesh(i, *mesh);
		}

		*modelOut = model;

		return true;
	}

	void DestroyModel(Model* model)
	{
		if (model)
		{
			model->DestroyMeshArray();
			free(model);
		}
	}
}