#pragma once

#include <d3d11_1.h>
#include "D3D11Shader.h"

namespace Picayune
{
	class D3D11PixelShader : public D3D11Shader
	{

	};

	struct CreateD3D11PixelShaderParams
	{

	};

	bool CreateD3D11PixelShader(D3D11PixelShader** pixelShaderOut, CreateD3D11PixelShaderParams params);
	void DestroyD3D11PixelShader(D3D11PixelShader* pixelShader);
}