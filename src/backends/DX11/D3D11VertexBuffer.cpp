#include <cstdlib>
#include "D3D11VertexBuffer.h"

namespace Picayune
{
	void* D3D11VertexBuffer::GetBuffer()
	{
		return (void*) m_buffer;
	}

	void D3D11VertexBuffer::SetBuffer(void* buffer)
	{
		return;

		//if (buffer)
		//{
		//	m_buffer = (ID3D11Buffer*) buffer;
		//}
	}

	bool CreateD3D11VertexBuffer(D3D11VertexBuffer** vertexBufferOut, CreateD3D11VertexBufferParams params)
	{
		D3D11VertexBuffer* vertexBuffer = new D3D11VertexBuffer(); // (D3D11VertexBuffer*) malloc(sizeof(D3D11VertexBuffer));
		if (!vertexBuffer)
		{
			return false;
		}

		ID3D11Buffer* buffer = nullptr;

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