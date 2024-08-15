#include <cstdlib>
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Vertex.h"
#include "ShaderProgram.h"
#include "Model.h"

#ifdef OPENGL_BUILD
#include "backends/OpenGL/OpenGLInputLayoutManager.h"
#include "backends/OpenGL/OpenGLShaderProgram.h"
#endif

namespace Picayune
{
	bool Model::CreateMeshArray(int numMeshes)
	{
		DestroyMeshArray();

		m_numMeshes = numMeshes;

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
		for (int i = 0; i < m_numMeshes; i++)
		{
			DestroyMesh(m_meshes + i);
		}
	}

	Mesh Model::GetMesh(int index)
	{
		return m_meshes[index];
	}

	void Model::SetMesh(int index, Mesh mesh)
	{
		m_meshes[index] = mesh; 
	}

	void Model::DrawMesh(Mesh mesh, ShaderProgram* shaderProgran)
	{
#ifdef OPENGL_BUILD
		OpenGLShaderProgram* openGLShaderProgram = (OpenGLShaderProgram*)shaderProgran;
		OpenGLInputLayoutManagerKey key =
		{
			*((GLuint*)mesh.vertexBuffer->GetBuffer()),
			openGLShaderProgram->GetId()
		};
		m_inputLayoutManager->Bind((void*) &key);
		openGLShaderProgram->Bind();

		// glDrawArrays(GL_TRIANGLES, 0, mesh.vertexBuffer.)

		openGLShaderProgram->Unbind();
		m_inputLayoutManager->Unbind();
#endif
	}

	void Model::Draw(ShaderProgram* shaderProgram)
	{
		for (int i = 0; i < m_numMeshes; i++)
		{
			DrawMesh(m_meshes[i], shaderProgram);
		}
	}

	bool CreateModel(Model** modelOut, CreateModelParams params)
	{
		Model* model = new Model;
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
			Mesh* mesh;

			aiMesh* rawMesh = rawScene->mMeshes[i];

			CreateMeshParams meshParams =
			{
				rawMesh,
				rawScene,
				params.window,

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
			delete model;
		}
	}
}