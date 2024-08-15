#include "OpenGLVertexShader.h"

namespace Picayune
{
	bool CreateOpenGLVertexShader(OpenGLVertexShader** shaderOut, CreateOpenGLShaderParams params)
	{
		GLenum error;
		OpenGLVertexShader* shader = new OpenGLVertexShader;
		if (!shader)
		{
			return false;
		}

		GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
		if (shaderId == 0 || (error = glGetError()) != GL_NO_ERROR)
		{
			delete shader;
			return false;
		}

		shader->SetId(shaderId);
		if (!CompileOpenGLShader(params))
		{
			glDeleteShader(shaderId);
			delete shader;
			return false;
		}

		return true;
	}
	
	void DestroyOpenGLVertexShader(OpenGLVertexShader* shader)
	{
		if (shader)
		{
			glDeleteShader(shader->GetId());
			delete shader;
		}
	}
}