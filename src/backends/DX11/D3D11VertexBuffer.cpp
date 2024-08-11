#include "D3D11VertexBuffer.h"

namespace Picayune
{
	void* D3D11VertexBuffer::GetBuffer()
	{
		return (void*) m_buffer;
	}

	void D3D11VertexBuffer::SetBuffer(void* buffer)
	{
		if (buffer)
		{
			m_buffer = (ID3D11Buffer*) buffer;
		}
	}

	bool CreateD3D11VertexBufffer(D3D11VertexBuffer** vertexBufferOut, CreateD3D11VertexBufferParams params)
	{
		D3D11VertexBuffer* vertexBuffer = (D3D11VertexBuffer*) malloc(sizeof(D3D11VertexBuffer));
		ID3D11Buffer* buffer = nullptr;

		if (!vertexBuffer)
		{
			return false;
		}

		HRESULT hResult;
		hResult = params.device->CreateBuffer(&params.desc, &params.data, &buffer);
		if (FAILED(hResult))
		{
			return false;
		}

		vertexBuffer->SetBuffer((void*) buffer);
		*vertexBufferOut = vertexBuffer;

		return true;
	}
}