#include "OpenGLShaderProgram.h"

namespace Picayune
{
	void OpenGLShaderProgram::Bind()
	{
		glUseProgram(m_id);
	}

	void OpenGLShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	GLuint OpenGLShaderProgram::GetId()
	{
		return m_id;
	}

	void OpenGLShaderProgram::SetId(GLuint id)
	{
		m_id = id;
	}

	bool CreateOpenGLShaderProgram(OpenGLShaderProgram** shaderProgramOut, CreateOpenGLShaderProgramParams params)
	{
		GLenum error;

		OpenGLShaderProgram* shaderProgram = new OpenGLShaderProgram;
		if (!shaderProgram)
		{
			return false;
		}

		GLuint shaderProgramId = glCreateProgram();
		if (shaderProgramId == 0)
		{
			delete shaderProgram;
			return false;
		}

		glAttachShader(shaderProgramId, params.vertexShader->GetId());
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteProgram(shaderProgramId);
			delete shaderProgram;
			return false;
		}

		glAttachShader(shaderProgramId, params.pixelShader->GetId());
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteProgram(shaderProgramId);
			delete shaderProgram;
			return false;
		}

		glLinkProgram(shaderProgramId);
		GLint success = 0;
		glGetProgramiv(shaderProgramId, GL_LINK_STATUS, (int*) &success);
		if (success == GL_FALSE)
		{
			glDeleteProgram(shaderProgramId);
			delete shaderProgram;
			return false;
		}

		glDetachShader(shaderProgramId, params.pixelShader->GetId());
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteProgram(shaderProgramId);
			delete shaderProgram;
			return false;
		}

		glDetachShader(shaderProgramId, params.vertexShader->GetId());
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			glDeleteProgram(shaderProgramId);
			delete shaderProgram;
			return false;
		}

		return true;
	}
	
	void DestroyOpenGLShaderProgram(OpenGLShaderProgram* shaderProgram)
	{
		if (shaderProgram)
		{
			glDeleteProgram(shaderProgram->GetId());
			delete shaderProgram;
		}
	}
}