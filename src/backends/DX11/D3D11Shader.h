#pragma once

#include <d3d11_1.h>
#include "../../Shader.h"

namespace Picayune
{
	class D3D11Shader : public Shader
	{
	private:
		ID3DBlob* m_blob;

	public:
		ID3DBlob* GetBlob();
		void SetBlob(ID3DBlob* blob);

	};

	struct CreateD3D11ShaderParams
	{
		LPCWSTR filePath;
		const char* entryPoint;
		ID3D11Device1* device;
	};

	bool CreateD3D11Shader(D3D11Shader** shaderOut, CreateD3D11ShaderParams params);
	void DestroyD3D11Shader(D3D11Shader* shader);
}