#include "OpenGLInputLayoutManager.h"

namespace Picayune
{
	bool OpenGLInputLayoutManager::Init()
	{
		return true;
	}

	void OpenGLInputLayoutManager::Shutdown()
	{
		for (const std::pair<const std::tuple<GLuint, GLuint>, OpenGLInputLayout*> inputLayout : m_inputLayouts)
		{
			// DestroyOpenGLInputLayout(inputLayout.second);
		}
	}

	void OpenGLInputLayoutManager::Bind(void* params)
	{
		OpenGLInputLayoutManagerKey key = *((OpenGLInputLayoutManagerKey*)params);

		OpenGLInputLayout* inputLayout = m_inputLayouts[std::tuple(key.vertexBufferObject, key.shaderId)];
		// glBindVertexArray(inputLayout->vertexAttributeObject);
	}

	void OpenGLInputLayoutManager::Unbind()
	{
		glBindVertexArray(0);
	}

	bool OpenGLInputLayoutManager::CreateManagedInputLayout(void* params)
	{
		CreateManagedOpenGLInputLayoutParams managedInputLayoutParams = *((CreateManagedOpenGLInputLayoutParams*)params);

		OpenGLInputLayoutManagerKey key =
		{
			*((GLuint*)managedInputLayoutParams.vertexBuffer->GetBuffer()),
			managedInputLayoutParams.shaderId
		};

		if (m_inputLayouts.contains(std::tuple(key.vertexBufferObject, key.shaderId)))
		{
			return false;
		}

		//OpenGLInputLayout* inputLayout = nullptr;
		//CreateOpenGLInputLayoutParams inputLayoutParams =
		//{
		//	managedInputLayoutParams.vertexBuffer,
		//	managedInputLayoutParams.indexBuffer
		//};

		//if (!CreateOpenGLInputLayout(&inputLayout, inputLayoutParams))
		//{
		//	return false;
		//}

		//m_inputLayouts[std::tuple(key.vertexBufferObject, key.shaderId)] = inputLayout;

		return true;
	}

	void OpenGLInputLayoutManager::DestroyManagedInputLayout(void* params)
	{
		OpenGLInputLayoutManagerKey* key = (OpenGLInputLayoutManagerKey*)params;
		std::pair<GLuint, GLuint> hashmapKey = std::pair(key->vertexBufferObject, key->shaderId);
		if (m_inputLayouts.contains(hashmapKey))
		{
			// DestroyOpenGLInputLayout(m_inputLayouts[hashmapKey]);
			m_inputLayouts.erase(std::tuple(key->vertexBufferObject, key->shaderId));
		}
	}

	bool CreateOpenGLInputLayoutManager(OpenGLInputLayoutManager** inputLayoutManagerOut)
	{
		OpenGLInputLayoutManager* inputLayoutManager = new OpenGLInputLayoutManager;
		if (!inputLayoutManager)
		{
			return false;
		}

		*inputLayoutManagerOut = inputLayoutManager;
	}

	void DestroyOpenGLInputLayoutManager(OpenGLInputLayoutManager* inputLayoutManager)
	{
		if (inputLayoutManager)
		{
			inputLayoutManager->Shutdown();
			delete inputLayoutManager;
		}
	}
}