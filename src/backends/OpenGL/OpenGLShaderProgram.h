#pragma once

#include <glad/glad.h>
#include "OpenGLPixelShader.h"
#include "OpenGLVertexShader.h"
#include "../../ShaderProgram.h"

namespace Picayune
{
	class OpenGLShaderProgram : public ShaderProgram
	{
	private:
		OpenGLPixelShader* m_pixelShader;
		OpenGLVertexShader* m_vertexShader;
		GLuint m_id;

	public:
		void Bind();
		void Unbind();
		GLuint GetId();
		void SetId(GLuint id);
	};

	struct CreateOpenGLShaderProgramParams
	{
		OpenGLPixelShader* pixelShader;
		OpenGLVertexShader* vertexShader;
	};

	bool CreateOpenGLShaderProgram(OpenGLShaderProgram** shaderProgramOut, CreateOpenGLShaderProgramParams params);
	void DestroyOpenGLShaderProgram(OpenGLShaderProgram* shaderProgram);
}