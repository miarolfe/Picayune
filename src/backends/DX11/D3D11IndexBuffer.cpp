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
			delete indexBuffer;
			return false;
		}

		indexBuffer->SetBuffer((void*) buffer);
		*indexBufferOut = indexBuffer;

		return true;
	}

	void DestroyD3D11IndexBuffer(D3D11IndexBuffer* indexBuffer)
	{
		if (indexBuffer)
		{
			ID3D11Buffer* buffer = (ID3D11Buffer*) indexBuffer->GetBuffer();
			if (buffer)
			{
				buffer->Release();
			}

			delete indexBuffer;
		}
	}
}