#pragma once

#include "glm/glm.hpp"

namespace Picayune
{
	class Camera
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_worldUp;
		float m_yaw;
		float m_pitch;

	public:
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;

	public:
		void SetPosition(float x, float y, float z);
		void SetWorldUp(float x, float y, float z);
		void SetYaw(float yaw);
		void SetPitch(float pitch);

	private:
		void OnPositionChange();
		void OnWorldUpChange();
		void OnYawChange();
		void OnPitchChange();
		
	};

	struct CreateCameraParams
	{
		float positionX;
		float positionY;
		float positionZ;
		float worldUpX;
		float worldUpY;
		float worldUpZ;
		float yaw;
		float pitch;
	};

	bool CreateCamera(Camera** cameraOut, CreateCameraParams params);
	void DestroyCamera(Camera* camera);
}