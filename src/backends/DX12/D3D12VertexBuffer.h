#pragma once

#include "../../VertexBuffer.h"

namespace Picayune
{
	class D3D12VertexBuffer : public VertexBuffer
	{
	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateD3D12VertexBufferParams
	{

	};

	static bool CreateD3D12VertexBuffer(D3D12VertexBuffer** vertexBufferOut, CreateD3D12VertexBufferParams params);
}