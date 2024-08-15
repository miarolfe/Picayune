#pragma once

#include <d3d11_1.h>
#include "D3D11VertexBuffer.h"
#include "D3D11IndexBuffer.h"
#include "D3D11ShaderProgram.h"
#include "../../InputLayout.h"

namespace Picayune
{
	struct D3D11InputLayout : public InputLayout
	{
		ID3D11InputLayout* layout;
	};

	struct CreateD3D11InputLayoutParams
	{
		ID3D11Device1* device;
		D3D11VertexBuffer* vertexBuffer;
		D3D11ShaderProgram* shaderProgram;
	};

	bool CreateD3D11InputLayout(D3D11InputLayout** inputLayoutOut, CreateD3D11InputLayoutParams params);
	void DestroyD3D11InputLayout(D3D11InputLayout* inputLayout);
}