#pragma once

namespace Picayune
{
	class InputLayoutManager
	{
	public:
		virtual bool Init() { return true; };
		virtual void Shutdown() { };
		virtual void Bind(void* params) { };
		virtual void Unbind() { };
		bool CreateManagedInputLayout(void* params) { return true; };
		void DestroyManagedInputLayout(void* params);
	};
}

/*

D3D11
each input layout can be used with multiple shaders
so we need a map structure OR it's configured at startup

ShaderProgram -> InputLayout

so

---

map<InputSignature, InputLayout> inputLayouts;

for shaderProgram in shaderPrograms:
	if shaderProgram.inputSignature in inputLayouts:
		shaderProgram.inputLayout = inputLayouts[shaderProgram.inputSignature]
	else:
		InputLayout inputLayout = Create ...
		inputLayouts[shaderProgram.inputSignature] = inputLayout

---
OpenGL
---

map<tuple<ShaderProgram, VertexBuffer>, InputLayout> inputLayouts;
for shaderProgram in shaderPrograms:
	for vertexBuffer in vertexBuffers:
		inputLayouts[(shaderProgram, vertexBuffer)] = Create ...


*/