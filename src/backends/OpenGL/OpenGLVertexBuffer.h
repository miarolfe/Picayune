#pragma once

#include "glad/glad.h"
#include "../../Vertex.h"
#include "../../VertexBuffer.h"

namespace Picayune
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		GLuint m_vertexBufferObject;

	public:
		void Bind();
		void Unbind();
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateOpenGLVertexBufferParams
	{
		Vertex* vertices;
		int numVertices;
	};

	bool CreateOpenGLVertexBuffer(OpenGLVertexBuffer** vertexBufferOut, CreateOpenGLVertexBufferParams params);
	void DestroyOpenGLVertexBuffer(OpenGLVertexBuffer* vertexBuffer);
}