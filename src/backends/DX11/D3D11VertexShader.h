#pragma once

#include <d3d11_1.h>
#include "D3D11Shader.h"

namespace Picayune
{
	class D3D11VertexShader : public D3D11Shader
	{

	};

	struct CreateD3D11VertexShaderParams
	{

	};

	bool CreateD3D11VertexShader(D3D11VertexShader** pixelShaderOut, CreateD3D11VertexShaderParams params);
}