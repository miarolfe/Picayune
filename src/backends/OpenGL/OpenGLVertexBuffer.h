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
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateOpenGLVertexBufferParams
	{
		Vertex* vertices;
	};

	bool CreateOpenGLVertexBuffer(OpenGLVertexBuffer** vertexBufferOut, CreateOpenGLVertexBufferParams params);
}