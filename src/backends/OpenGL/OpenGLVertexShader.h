#pragma once

#include "OpenGLShader.h"

namespace Picayune
{
	class OpenGLVertexShader : public OpenGLShader
	{

	};

	bool CreateOpenGLVertexShader(OpenGLVertexShader** shaderOut, CreateOpenGLShaderParams params);
	void DestroyOpenGLVertexShader(OpenGLVertexShader* shader);
}