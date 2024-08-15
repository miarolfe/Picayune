#pragma once

#include <glad/glad.h>
#include "../../Vertex.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "../../InputLayout.h"

namespace Picayune
{
	struct OpenGLInputLayout : public InputLayout
	{
		GLuint vertexAttributeObject;
	};

	struct CreateOpenGLInputLayoutParams
	{
		OpenGLVertexBuffer* vertexBuffer;
		OpenGLIndexBuffer* indexBuffer;
	};

	bool CreateOpenGLInputLayout(OpenGLInputLayout** inputLayoutOut, CreateOpenGLInputLayoutParams params);
	void DestroyOpenGLInputLayout(OpenGLInputLayout* inputLayout);
}