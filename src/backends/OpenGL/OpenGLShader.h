#pragma once

#include <glad/glad.h>
#include "../../Shader.h"

namespace Picayune
{
	class OpenGLShader : public Shader
	{
	private:
		GLuint m_id;

	public:
		GLuint GetId();
		void SetId(GLuint id);
	};

	struct CreateOpenGLShaderParams
	{
		GLuint id;
		const char* source;
	};

	bool CompileOpenGLShader(CreateOpenGLShaderParams params);
}