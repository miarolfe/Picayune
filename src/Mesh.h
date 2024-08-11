#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Texture.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#ifdef DX11_BUILD
#include "backends/DX11/D3D11VertexBuffer.h"
#include "backends/DX11/D3D11IndexBuffer.h"
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
	struct Mesh
	{
		VertexBuffer* vertexBuffer = nullptr;
		Vertex* vertices = nullptr;
		unsigned int* indices = nullptr;
		Texture* textures = nullptr;
	};

	struct CreateMeshParams
	{
		aiMesh* rawMesh;
		const aiScene* rawScene;
	};

	bool CreateMesh(Mesh** meshOut, CreateMeshParams params);
	void DestroyMesh(Mesh* mesh);
}
