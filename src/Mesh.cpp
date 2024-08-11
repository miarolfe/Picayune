#include <cstdlib>
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Vertex.h"

namespace Picayune
{
	bool CreateMesh(Mesh** meshOut, CreateMeshParams params)
	{
		Mesh* mesh = (Mesh*) malloc(sizeof(Mesh));
		if (!mesh)
		{
			return false;
		}

		int numVertices = params.rawMesh->mNumVertices;

		mesh->vertices = (Vertex*) malloc(numVertices * sizeof(Vertex));
		if (!mesh->vertices)
		{
			return false;
		}

		int numIndices = 0;
		for (int i = 0; i < params.rawMesh->mNumFaces; i++)
		{
			numIndices += params.rawMesh->mFaces[i].mNumIndices;
		}

		mesh->indices = (unsigned int*) malloc(numIndices * sizeof(unsigned int));
		if (!mesh->indices)
		{
			return false;
		}
		
		// Load vertices
		for (int i = 0; i < numVertices; i++)
		{
			Vertex vertex;

			vertex.position = glm::vec3
			(
				params.rawMesh->mVertices[i].x,
				params.rawMesh->mVertices[i].y,
				params.rawMesh->mVertices[i].z
			);

			vertex.normal = glm::vec3
			(
				params.rawMesh->mNormals[i].x,
				params.rawMesh->mNormals[i].y,
				params.rawMesh->mNormals[i].z
			);

			if (params.rawMesh->mTextureCoords[0])
			{
				vertex.uv = glm::vec2
				(
					params.rawMesh->mTextureCoords[0][i].x,
					params.rawMesh->mTextureCoords[0][i].y
				);
			}
			else
			{
				vertex.uv = glm::vec2(0.0f, 0.0f);
			}

			mesh->vertices[i] = vertex;
		}

		// Load indices
		int currentIndex = 0;
		for (int i = 0; i < params.rawMesh->mNumFaces; i++)
		{
			aiFace face = params.rawMesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				mesh->indices[currentIndex++] = face.mIndices[j];
			}
		}

		// TODO: Load materials and get mat count
		mesh->textures = nullptr;

		*meshOut = mesh;

		return true;
	}

	void DestroyMesh(Mesh* mesh)
	{
		if (mesh) free(mesh);
	}
}