#pragma once

#include "../../VertexBuffer.h"

namespace Picayune
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateOpenGLVertexBufferParams
	{

	};

	static bool CreateOpenGLVertexBuffer(OpenGLVertexBuffer** vertexBufferOut, CreateOpenGLVertexBufferParams params);
}