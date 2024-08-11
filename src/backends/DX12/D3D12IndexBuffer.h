#pragma once

#include "../../IndexBuffer.h"

namespace Picayune
{
	class D3D12IndexBuffer : public IndexBuffer
	{
	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateD3D12IndexBufferParams
	{

	};

	static bool CreateD3D12IndexBuffer(D3D12IndexBuffer** indexBufferOut, CreateD3D12IndexBufferParams params);
}