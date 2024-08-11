#pragma once

#include "../../IndexBuffer.h"

namespace Picayune
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		void* GetBuffer();
		void SetBuffer(void* buffer);
	};

	struct CreateOpenGLIndexBufferParams
	{

	};

	static bool CreateOpenGLIndexBuffer(OpenGLIndexBuffer** indexBufferOut, CreateOpenGLIndexBufferParams params);
}