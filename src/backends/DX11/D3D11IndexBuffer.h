#pragma once

#include <d3d11_1.h>
#include "../../IndexBuffer.h"

namespace Picayune
{
	class D3D11IndexBuffer : public IndexBuffer
	{
	private:
		ID3D11Buffer* m_buffer = nullptr;

	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateD3D11IndexBufferParams
	{
		ID3D11Device1* device;
		D3D11_BUFFER_DESC desc;
		D3D11_SUBRESOURCE_DATA data;
	};

	bool CreateD3D11IndexBuffer(D3D11IndexBuffer** indexBufferOut, CreateD3D11IndexBufferParams params);
	void DestroyD3D11IndexBuffer(D3D11IndexBuffer* indexBuffer);
}