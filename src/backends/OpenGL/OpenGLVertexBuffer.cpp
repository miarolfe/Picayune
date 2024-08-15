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
		GLenum error;

		OpenGLVertexBuffer* vertexBuffer = new OpenGLVertexBuffer();
		if (!vertexBuffer)
		{
			return false;
		}

		GLuint vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);

		if (vertexBufferObject == 0)
		{
			delete vertexBuffer;
			return false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexBufferObject);
			delete vertexBuffer;
			return false;
		}

		glBufferData(GL_ARRAY_BUFFER, params.numVertices * sizeof(Vertex), params.vertices, GL_STATIC_DRAW);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexBufferObject);
			delete vertexBuffer;
			return false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vertexBuffer->SetBuffer((void*) &vertexBufferObject);
		*vertexBufferOut = vertexBuffer;

		return true;
	}

	void DestroyOpenGLVertexBuffer(OpenGLVertexBuffer* vertexBuffer)
	{
		if (vertexBuffer)
		{
			GLuint* vertexBufferObjectPtr = (GLuint*) vertexBuffer->GetBuffer();
			if (vertexBufferObjectPtr)
			{
				GLuint vertexBufferObject = *vertexBufferObjectPtr;

				if (vertexBufferObject != 0)
				{
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glDeleteBuffers(1, vertexBufferObjectPtr);
				}
			}

			delete vertexBuffer;
		}
	}
}