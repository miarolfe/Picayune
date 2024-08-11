#pragma once

namespace Picayune
{
	class IndexBuffer
	{
	public:
		virtual void* GetBuffer() { };
		virtual void SetBuffer(void* buffer) { };
	};
}