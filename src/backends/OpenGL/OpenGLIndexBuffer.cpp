#include "OpenGLIndexBuffer.h"

namespace Picayune
{
	void* OpenGLIndexBuffer::GetBuffer()
	{
		return (void*)&m_elementBufferObject;
	}

	void OpenGLIndexBuffer::SetBuffer(void* buffer)
	{
		if (buffer)
		{
			unsigned int* elementBufferObjectPtr = (unsigned int*)buffer;
			m_elementBufferObject = (unsigned int)*elementBufferObjectPtr;
		}
	}

	bool CreateOpenGLIndexBuffer(OpenGLIndexBuffer** indexBufferOut, CreateOpenGLIndexBufferParams params)
	{
		OpenGLIndexBuffer* indexBuffer = new OpenGLIndexBuffer();
		if (!indexBuffer)
		{
			return false;
		}

		GLenum error;

		unsigned int elementBufferObject;
		glGenBuffers(1, &elementBufferObject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &elementBufferObject);
			return false;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(params.indices), params.indices, GL_STATIC_DRAW);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &elementBufferObject);
			return false;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		indexBuffer->SetBuffer((void*) &elementBufferObject);
		*indexBufferOut = indexBuffer;

		return true;
	}
}