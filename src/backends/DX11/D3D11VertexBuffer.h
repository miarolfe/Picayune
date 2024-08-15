#pragma once

#include <d3d11_1.h>
#include "../../VertexBuffer.h"

namespace Picayune
{
	class D3D11VertexBuffer : public VertexBuffer
	{
	private:
		ID3D11Buffer* m_buffer;

	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateD3D11VertexBufferParams
	{
		ID3D11Device1* device;
		D3D11_BUFFER_DESC desc;
		D3D11_SUBRESOURCE_DATA data;
	};

	bool CreateD3D11VertexBuffer(D3D11VertexBuffer** vertexBufferOut, CreateD3D11VertexBufferParams params);
	void DestroyD3D11VertexBuffer(D3D11VertexBuffer* vertexBuffer);
}