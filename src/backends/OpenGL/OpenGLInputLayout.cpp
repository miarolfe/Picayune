#include "OpenGLInputLayout.h"

namespace Picayune
{
	void* OpenGLInputLayout::GetLayout()
	{
		return (void*) &m_vertexAttributeObject;
	}

	void OpenGLInputLayout::SetLayout(void* layout)
	{
		if (layout)
		{
			unsigned int* vertexAttributeObjectPtr = (unsigned int*) layout;
			m_vertexAttributeObject = (unsigned int) *vertexAttributeObjectPtr;
		}
	}

	bool CreateOpenGLInputLayout(OpenGLInputLayout** inputLayoutOut, CreateOpenGLInputLayoutParams params)
	{
		OpenGLInputLayout* inputLayout = new OpenGLInputLayout();
		if (!inputLayout)
		{
			return false;
		}

		GLenum error;

		unsigned int vertexAttributeObject;
		glGenVertexArrays(1, &vertexAttributeObject);
		if (vertexAttributeObject == 0)
		{
			return false;
		}

		glBindVertexArray(vertexAttributeObject);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &vertexAttributeObject);
			return false;
		}

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::uv));

		glBindVertexArray(0);

		inputLayout->SetLayout((void*) &vertexAttributeObject);
		*inputLayoutOut = inputLayout;

		return true;
	}
}