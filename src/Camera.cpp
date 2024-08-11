#include <cstdlib>
#include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

namespace Picayune
{
	void Camera::SetPosition(float x, float y, float z)
	{
		m_position = glm::vec3(x, y, z);
		OnPositionChange();
	}

	void Camera::SetWorldUp(float x, float y, float z)
	{
		m_worldUp = glm::vec3(x, y, z);
		OnWorldUpChange();
	}

	void Camera::SetYaw(float yaw)
	{
		m_yaw = yaw;
		OnYawChange();
	}

	void Camera::SetPitch(float pitch)
	{
		m_pitch = pitch;
		OnPitchChange();
	}

	void Camera::OnPositionChange()
	{

	}

	void Camera::OnWorldUpChange()
	{
		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

	void Camera::OnYawChange()
	{
		m_front.x = cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		// m_front.y only relies on m_pitch, so we can leave it as-is
		m_front.z = sin(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front = glm::normalize(m_front);

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

	void Camera::OnPitchChange()
	{
		m_front.x = cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front = glm::normalize(m_front);

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

	bool CreateCamera(Camera** cameraOut, CreateCameraParams params)
	{
		Camera* camera = (Camera*) malloc(sizeof(Camera));
		if (!camera)
		{
			return false;
		}

		camera->SetPosition(params.positionX, params.positionY, params.positionZ);
		camera->SetWorldUp(params.worldUpX, params.worldUpY, params.worldUpZ);
		camera->SetYaw(params.yaw);
		camera->SetPitch(params.pitch);

		*cameraOut = camera;
		
		return true;
	}

	void DestroyCamera(Camera* camera)
	{
		if (camera) free(camera);
	}
}