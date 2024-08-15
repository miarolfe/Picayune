#include "OpenGLShader.h"

namespace Picayune
{
	GLuint OpenGLShader::GetId()
	{
		return m_id;
	}

	void OpenGLShader::SetId(GLuint id)
	{
		m_id = id;
	}

	bool CompileOpenGLShader(CreateOpenGLShaderParams params)
	{
		GLenum error;

		glShaderSource(params.id, 1, &params.source, nullptr);
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			return false;
		}

		GLint success = 0;
		glCompileShader(params.id);
		glGetShaderiv(params.id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			return false;
		}

		return true;
	}
}