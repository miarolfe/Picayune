#pragma once

#include "OpenGLShader.h"

namespace Picayune
{
	class OpenGLPixelShader : public OpenGLShader
	{
		
	};

	bool CreateOpenGLPixelShader(OpenGLPixelShader** shaderOut, CreateOpenGLShaderParams params);
	void DestroyOpenGLPixelShader(OpenGLPixelShader* shader);
}