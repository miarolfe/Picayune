#include "OpenGLPixelShader.h"

namespace Picayune
{
	bool CreateOpenGLPixelShader(OpenGLPixelShader** shaderOut, CreateOpenGLShaderParams params)
	{
		GLenum error;
		OpenGLPixelShader* shader = new OpenGLPixelShader;
		if (!shader)
		{
			return false;
		}

		// OpenGL calls pixel shaders fragment shaders
		GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
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

	void DestroyOpenGLPixelShader(OpenGLPixelShader* shader)
	{
		if (shader)
		{
			glDeleteShader(shader->GetId());
			delete shader;
		}
	}
}