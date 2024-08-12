#include "OpenGLVertexBuffer.h"

namespace Picayune
{
	void* OpenGLVertexBuffer::GetBuffer()
	{
		return (void*) &m_vertexBufferObject;
	}

	void OpenGLVertexBuffer::SetBuffer(void* buffer)
	{
		if (buffer)
		{
			unsigned int* vertexBufferObjectPtr = (unsigned int*) buffer;
			m_vertexBufferObject = (unsigned int) *vertexBufferObjectPtr;
		}
	}

	bool CreateOpenGLVertexBuffer(OpenGLVertexBuffer** vertexBufferOut, CreateOpenGLVertexBufferParams params)
	{
		OpenGLVertexBuffer* vertexBuffer = new OpenGLVertexBuffer();
		if (!vertexBuffer)
		{
			return false;
		}

		GLenum error;

		unsigned int vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexBufferObject);
			return false;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(params.vertices), params.vertices, GL_STATIC_DRAW);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexBufferObject);
			return false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vertexBuffer->SetBuffer((void*) &vertexBufferObject);
		*vertexBufferOut = vertexBuffer;

		return true;
	}
}