#pragma once

#include <d3d11_1.h>
#include "D3D11PixelShader.h"
#include "D3D11VertexShader.h"
#include "ShaderProgram.h"

namespace Picayune
{
	class D3D11ShaderProgram : public ShaderProgram
	{
	
	};

	struct CreateD3D11ShaderProgramParams
	{
		D3D11PixelShader* pixelShader;
		D3D11VertexShader* vertexShader;
	};

	bool CreateD3D11ShaderProgram(D3D11ShaderProgram** shaderProgramOut, CreateD3D11ShaderProgramParams params);
}