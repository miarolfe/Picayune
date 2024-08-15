#include <d3d11_1.h>
#include <d3dcompiler.h>
#include "D3D11Shader.h"

namespace Picayune
{
	ID3DBlob* D3D11Shader::GetBlob()
	{
		return m_blob;
	}

	void D3D11Shader::SetBlob(ID3DBlob* blob)
	{
		if (blob)
		{
			m_blob = blob;
		}
	}

	bool CreateD3D11Shader(D3D11Shader** shaderOut, CreateD3D11ShaderParams params)
	{
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)
		flags |= D3DCOMPILE_DEBUG;
#endif
		// Prefer higher CS shader profile when possible as CS 5.0 provides better performance on 11-class hardware.
		LPCSTR profile = (params.device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";
		
		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT hResult = D3DCompileFromFile
		(
			params.filePath,					// file path
			nullptr,							// shader macro defines
			D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ID3DInclude to handle include files
			params.entryPoint,					// entry point function name
			profile,							// target to compile against
			flags,								// shader compile options
			0,									// effect compile options
			&shaderBlob,						// compiled shader blob
			&errorBlob							// error blob
		);
		if (FAILED(hResult))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*) errorBlob->GetBufferPointer());
				errorBlob->Release();
			}

			if (shaderBlob)
			{
				shaderBlob->Release();
			}

			return false;
		}
	}

	void DestroyD3D11Shader(D3D11Shader* shader)
	{
		ID3DBlob* blob = shader->GetBlob();
		if (blob)
		{
			blob->Release();
			free(blob);
		}
	}
}