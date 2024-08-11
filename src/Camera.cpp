#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

namespace Picayune
{
	glm::vec3 Camera::GetPosition()
	{
		return m_position;
	}

	glm::vec3 Camera::GetWorldUp()
	{
		return m_worldUp;
	}

	float Camera::GetYaw()
	{
		return m_yaw;
	}

	float Camera::GetPitch()
	{
		return m_pitch;
	}

	float Camera::GetVerticalFOV()
	{
		return m_verticalFOV;
	}

	float Camera::GetAspectRatio()
	{
		return m_aspectRatio;
	}

	float Camera::GetNearPlane()
	{
		return m_nearPlane;
	}

	float Camera::GetFarPlane()
	{
		return m_farPlane;
	}

	glm::vec3 Camera::GetFront()
	{
		return m_front;
	}

	glm::vec3 Camera::GetUp()
	{
		return m_up;
	}

	glm::vec3 Camera::GetRight()
	{
		return m_right;
	}

	glm::mat4 Camera::GetProjection()
	{
		return m_projection;
	}

	glm::mat4 Camera::GetView()
	{
		return m_view;
	}

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

	void Camera::SetVerticalFOV(float verticalFOV)
	{
		m_verticalFOV = verticalFOV;
		OnVerticalFOVChange();
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		m_aspectRatio = aspectRatio;
		OnAspectRatioChange();
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		m_nearPlane = nearPlane;
		OnNearPlaneChange();
	}

	void Camera::SetFarPlane(float farPlane)
	{
		m_farPlane = farPlane;
		OnFarPlaneChange();
	}

	void Camera::OnPositionChange()
	{
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Camera::OnWorldUpChange()
	{
		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Camera::OnYawChange()
	{
		m_front.x = cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		// m_front.y only relies on m_pitch, so we can leave it as-is
		m_front.z = sin(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front = glm::normalize(m_front);

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Camera::OnPitchChange()
	{
		m_front.x = cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
		m_front = glm::normalize(m_front);

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Camera::OnVerticalFOVChange()
	{
		m_projection = glm::perspective(glm::radians(m_verticalFOV), m_aspectRatio, m_nearPlane, m_farPlane); 
	}

	void Camera::OnAspectRatioChange()
	{
		m_projection = glm::perspective(glm::radians(m_verticalFOV), m_aspectRatio, m_nearPlane, m_farPlane);
	}

	void Camera::OnNearPlaneChange()
	{
		m_projection = glm::perspective(glm::radians(m_verticalFOV), m_aspectRatio, m_nearPlane, m_farPlane);
	}

	void Camera::OnFarPlaneChange()
	{
		m_projection = glm::perspective(glm::radians(m_verticalFOV), m_aspectRatio, m_nearPlane, m_farPlane);
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
		camera->SetVerticalFOV(params.verticalFOV);
		camera->SetAspectRatio(params.aspectRatio);
		camera->SetNearPlane(params.nearPlane);
		camera->SetFarPlane(params.farPlane);

		*cameraOut = camera;
		
		return true;
	}

	void DestroyCamera(Camera* camera)
	{
		if (camera) free(camera);
	}
}