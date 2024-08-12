#pragma once

#include "Shader.h"

namespace Picayune
{
	class ShaderProgram
	{
	private:
		Shader* m_pixelShader;
		Shader* m_vertexShader;
	};
}