#include <cstdlib>
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#ifdef DX11_BUILD
#include "backends/DX11/D3D11VertexBuffer.h"
#include "backends/DX11/D3D11IndexBuffer.h"
#include "backends/DX11/D3D11Window.h"
#endif

#ifdef DX12_BUILD
#include "backends/DX12/D3D12VertexBuffer.h"
#include "backends/DX12/D3D12IndexBuffer.h"
#endif

#ifdef OPENGL_BUILD
#include "backends/OpenGL/OpenGLVertexBuffer.h"
#include "backends/OpenGL/OpenGLIndexBuffer.h"
#endif

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

		Vertex* vertices = (Vertex*) malloc(numVertices * sizeof(Vertex));
		if (!vertices)
		{
			return false;
		}

		int numIndices = 0;
		for (int i = 0; i < params.rawMesh->mNumFaces; i++)
		{
			numIndices += params.rawMesh->mFaces[i].mNumIndices;
		}

		unsigned int* indices = (unsigned int*) malloc(numIndices * sizeof(unsigned int));
		if (!indices)
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

			vertices[i] = vertex;
		}

		// Load indices
		int currentIndex = 0;
		for (int i = 0; i < params.rawMesh->mNumFaces; i++)
		{
			aiFace face = params.rawMesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices[currentIndex++] = face.mIndices[j];
			}
		}

		// TODO: Load materials and get mat count
		mesh->textures = nullptr;

#ifdef DX11_BUILD
		D3D11Window* window = (D3D11Window*) params.window;
		ID3D11Device1* device = window->GetD3DDevice();
		// ID3D11Device1* device = (ID3D11Device1*) params.window->GetDevice();

		D3D11VertexBuffer* vertexBuffer;

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = numVertices * sizeof(Vertex);
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CreateD3D11VertexBufferParams vertexBufferParams =
		{
			device,
			vertexBufferDesc,
			vertexBufferData
		};

		if (!CreateD3D11VertexBuffer(&vertexBuffer, vertexBufferParams))
		{
			return false;
		}
		
		D3D11IndexBuffer* indexBuffer;

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = numIndices * sizeof(unsigned int);
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		CreateD3D11IndexBufferParams indexBufferParams =
		{
			device,
			indexBufferDesc,
			indexBufferData
		};

		if (!CreateD3D11IndexBuffer(&indexBuffer, indexBufferParams))
		{
			return false;
		}

		mesh->vertexBuffer = vertexBuffer;
		mesh->indexBuffer = indexBuffer;
		
#endif

#ifdef DX12_BUILD
#endif

#ifdef OPENGL_BUILD
		OpenGLVertexBuffer* vertexBuffer;

		CreateOpenGLVertexBufferParams vertexBufferParams =
		{
			vertices
		};

		if (!CreateOpenGLVertexBuffer(&vertexBuffer, vertexBufferParams))
		{
			return false;
		}

		OpenGLIndexBuffer* indexBuffer;

		CreateOpenGLIndexBufferParams indexBufferParams =
		{
			indices
		};

		if (!CreateOpenGLIndexBuffer(&indexBuffer, indexBufferParams))
		{
			return false;
		}

		mesh->vertexBuffer = vertexBuffer;
		mesh->indexBuffer = indexBuffer;
#endif
		free(vertices);
		free(indices);

		*meshOut = mesh;

		return true;
	}

	void DestroyMesh(Mesh* mesh)
	{
		// TODO: NOT FINISHED!!!
		if (mesh->vertexBuffer) free(mesh->vertexBuffer);
		if (mesh->indexBuffer) free(mesh->indexBuffer);
		if (mesh->textures) free(mesh->textures);
		if (mesh) free(mesh);
	}
}