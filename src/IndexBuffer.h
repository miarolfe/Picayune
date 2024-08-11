#pragma once

namespace Picayune
{
	class IndexBuffer
	{
	public:
		virtual void* GetBuffer() { return nullptr; };
		virtual void SetBuffer(void* buffer) { };
	};
}