#include "OpenGLIndexBuffer.h"

namespace Picayune
{
	void* OpenGLIndexBuffer::GetBuffer()
	{
		return (void*) &m_elementBufferObject;
	}

	void OpenGLIndexBuffer::SetBuffer(void* buffer)
	{
		if (buffer)
		{
			GLuint* elementBufferObjectPtr = (GLuint*) buffer;
			m_elementBufferObject = *elementBufferObjectPtr;
		}
	}

	bool CreateOpenGLIndexBuffer(OpenGLIndexBuffer** indexBufferOut, CreateOpenGLIndexBufferParams params)
	{
		GLenum error;

		OpenGLIndexBuffer* indexBuffer = new OpenGLIndexBuffer();
		if (!indexBuffer)
		{
			return false;
		}

		GLuint elementBufferObject;
		glGenBuffers(1, &elementBufferObject);

		if (elementBufferObject == 0)
		{
			delete indexBuffer;
			return false;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &elementBufferObject);
			delete indexBuffer;
			return false;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, params.numIndices * sizeof(unsigned int), params.indices, GL_STATIC_DRAW);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &elementBufferObject);
			delete indexBuffer;
			return false;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &elementBufferObject);
			delete indexBuffer;
			return false;
		}

		indexBuffer->SetBuffer((void*) &elementBufferObject);
		*indexBufferOut = indexBuffer;

		return true;
	}

	void DestroyOpenGLIndexBuffer(OpenGLIndexBuffer* indexBuffer)
	{
		if (indexBuffer)
		{
			GLuint* elementBufferObjectPtr = (GLuint*) indexBuffer->GetBuffer();
			if (elementBufferObjectPtr)
			{
				GLuint elementBufferObject = *elementBufferObjectPtr;

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glDeleteBuffers(1, &elementBufferObject);
			}
			
			delete indexBuffer;
		}
	}
}