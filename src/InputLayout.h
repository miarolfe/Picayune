#pragma once

namespace Picayune
{
	class InputLayout
	{
	public:
		virtual void* GetLayout() { return nullptr; };
		virtual void SetLayout(void* layout) { };
	};
}