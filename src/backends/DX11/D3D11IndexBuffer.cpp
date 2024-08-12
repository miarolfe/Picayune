#include "D3D11IndexBuffer.h"

namespace Picayune
{
	void* D3D11IndexBuffer::GetBuffer()
	{
		return (void*) m_buffer;
	}

	void D3D11IndexBuffer::SetBuffer(void* buffer)
	{
		if (buffer)
		{
			m_buffer = (ID3D11Buffer*) buffer;
		}
	}

	bool CreateD3D11IndexBuffer(D3D11IndexBuffer** indexBufferOut, CreateD3D11IndexBufferParams params)
	{
		D3D11IndexBuffer* indexBuffer = new D3D11IndexBuffer(); // (D3D11IndexBuffer*) malloc(sizeof(D3D11IndexBuffer));
		ID3D11Buffer* buffer = nullptr;

		if (!indexBuffer)
		{
			return false;
		}

		HRESULT hResult;
		hResult = params.device->CreateBuffer(&params.desc, &params.data, &buffer);
		if (FAILED(hResult))
		{
			return false;
		}

		indexBuffer->SetBuffer((void*) buffer);
		*indexBufferOut = indexBuffer;

		return true;
	}

	// TODO: Destroy
}