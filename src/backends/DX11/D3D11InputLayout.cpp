#include <cstdlib>
#include "../../Vertex.h"
#include "D3D11InputLayout.h"

namespace Picayune
{
	bool CreateD3D11InputLayout(D3D11InputLayout** inputLayoutOut, CreateD3D11InputLayoutParams params)
	{
		D3D11InputLayout* inputLayout = (D3D11InputLayout*) malloc(sizeof(D3D11InputLayout));
		if (!inputLayout)
		{
			return false;
		}

		ID3D11InputLayout* d3d11Layout;

		const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				offsetof(Vertex, Vertex::position),
				D3D11_INPUT_PER_VERTEX_DATA,
				0,
			},
			{
				"NORMAL",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				offsetof(Vertex, Vertex::normal),
				D3D11_INPUT_PER_VERTEX_DATA,
				0,
			},
			{
				"UV", 
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				offsetof(Vertex, Vertex::uv),
				0,
				D3D11_INPUT_PER_VERTEX_DATA,
				0,
			}
		};
		
		// Modify this if changing the inputElementDesc
		const int numInputElements = 3;

		HRESULT hResult;
		hResult = params.device->CreateInputLayout
		(
			inputElementDesc,
			numInputElements,
			nullptr,
			nullptr,
			&d3d11Layout
		);

		return true;
	}

	void DestroyD3D11InputLayout(D3D11InputLayout* inputLayout)
	{
		if (inputLayout)
		{
			
		}
	}
}