#pragma once

namespace Picayune
{
	class VertexBuffer
	{
	public:
		virtual void* GetBuffer() { };
		virtual void SetBuffer(void* buffer) { };
	};
}