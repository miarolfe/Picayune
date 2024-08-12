#pragma once

#include <glad/glad.h>
#include "../../Vertex.h"
#include "../../InputLayout.h"

namespace Picayune
{
	class OpenGLInputLayout : public InputLayout
	{
	private:
		GLuint m_vertexAttributeObject;

	public:
		void* GetLayout();
		void SetLayout(void* layout);
	};

	struct CreateOpenGLInputLayoutParams
	{

	};

	bool CreateOpenGLInputLayout(OpenGLInputLayout** inputLayoutOut, CreateOpenGLInputLayoutParams params);
}