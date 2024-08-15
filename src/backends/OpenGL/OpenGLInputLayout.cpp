#include "OpenGLInputLayout.h"

namespace Picayune
{
	bool CreateOpenGLInputLayout(OpenGLInputLayout** inputLayoutOut, CreateOpenGLInputLayoutParams params)
	{
		GLenum error;

		GLuint* vertexBufferObjectPtr = (GLuint*) params.vertexBuffer->GetBuffer();
		GLuint* elementBufferObjectPtr = (GLuint*) params.indexBuffer->GetBuffer();

		glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObjectPtr);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementBufferObjectPtr);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		OpenGLInputLayout* inputLayout = new OpenGLInputLayout();
		if (!inputLayout)
		{
			return false;
		}

		unsigned int vertexAttributeObject;
		glGenVertexArrays(1, &vertexAttributeObject);
		if (vertexAttributeObject == 0)
		{
			return false;
		}

		glBindVertexArray(vertexAttributeObject);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexAttributeObject);
			return false;
		}

		glEnableVertexAttribArray(0);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::position));
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glEnableVertexAttribArray(1);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::normal));
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			int i = 1;
		}

		glEnableVertexAttribArray(2);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::uv));
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glBindVertexArray(0);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		inputLayout->vertexAttributeObject = vertexAttributeObject;
		*inputLayoutOut = inputLayout;

		return true;
	}

	void DestroyOpenGLInputLayout(OpenGLInputLayout* inputLayout)
	{
		if (inputLayout)
		{
			GLuint vertexAttributeObject = inputLayout->vertexAttributeObject;
			if (vertexAttributeObject != 0)
			{
				glBindVertexArray(0);
				glDeleteVertexArrays(1, &inputLayout->vertexAttributeObject);
			}
		}
	}
}