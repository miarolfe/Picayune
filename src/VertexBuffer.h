#pragma once

namespace Picayune
{
	class VertexBuffer
	{
	public:
		virtual void* GetBuffer() { return nullptr; };
		virtual void SetBuffer(void* buffer) { };
	};
}