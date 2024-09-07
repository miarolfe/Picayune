#include <glad/glad.h>
//#include <EASTL/tuple.h>
//#include <EASTL/hash_map.h>
#include <map>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLInputLayout.h"
#include "../../InputLayoutManager.h"

namespace Picayune
{
	class OpenGLInputLayoutManager : public InputLayoutManager
	{
	private:
		// eastl::hash_map<eastl::tuple<GLuint, GLuint>, OpenGLInputLayout*> m_inputLayouts;
		std::map<std::tuple<GLuint, GLuint>, OpenGLInputLayout*> m_inputLayouts;

	public:
		bool Init();
		void Shutdown();
		void Bind(void* params);
		void Unbind();

		bool CreateManagedInputLayout(void* params);
		void DestroyManagedInputLayout(void* params);
		// OpenGLInputLayout* GetLayout(OpenGLInputLayoutManagerKey key);
		// void SetLayout(OpenGLInputLayoutManagerKey, OpenGLInputLayout layout)
	};

	struct OpenGLInputLayoutManagerKey
	{
		GLuint vertexBufferObject;
		GLuint shaderId;
	};

	struct CreateManagedOpenGLInputLayoutParams
	{
		OpenGLVertexBuffer* vertexBuffer;
		OpenGLIndexBuffer* indexBuffer;
		GLuint shaderId;
	};

	bool CreateOpenGLInputLayoutManager(OpenGLInputLayoutManager** inputLayoutManagerOut);
	void DestroyOpenGLInputLayoutManager(OpenGLInputLayoutManager* inputLayoutManager);
}