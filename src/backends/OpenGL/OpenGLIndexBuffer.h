#pragma once

#include "glad/glad.h"
#include "../../IndexBuffer.h"

namespace Picayune
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		GLuint m_elementBufferObject;

	public:
		void Bind();
		void Unbind();
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateOpenGLIndexBufferParams
	{
		unsigned int* indices;
		int numIndices;
	};

	bool CreateOpenGLIndexBuffer(OpenGLIndexBuffer** indexBufferOut, CreateOpenGLIndexBufferParams params);
	void DestroyOpenGLIndexBuffer(OpenGLIndexBuffer* indexBuffer);
}