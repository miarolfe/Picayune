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

	};

	bool CreateOpenGLShader(OpenGLShader** shaderOut, CreateOpenGLShaderParams params);
	void DestroyOpenGLShader(OpenGLShader* shader);
}