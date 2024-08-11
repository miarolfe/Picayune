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
		float m_verticalFOV;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;

	// Derived values
	private:
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::mat4 m_projection;
		glm::mat4 m_view;

	public:
		glm::vec3 GetPosition();
		glm::vec3 GetWorldUp();
		float GetYaw();
		float GetPitch();
		float GetVerticalFOV();
		float GetAspectRatio();
		float GetNearPlane();
		float GetFarPlane();

	public:
		glm::vec3 GetFront();
		glm::vec3 GetUp();
		glm::vec3 GetRight();
		glm::mat4 GetProjection();
		glm::mat4 GetView();

	public:
		void SetPosition(float x, float y, float z);
		void SetWorldUp(float x, float y, float z);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		void SetVerticalFOV(float verticalFOV);
		void SetAspectRatio(float aspectRatio);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

	private:
		void OnPositionChange();
		void OnWorldUpChange();
		void OnYawChange();
		void OnPitchChange();
		void OnVerticalFOVChange();
		void OnAspectRatioChange();
		void OnNearPlaneChange();
		void OnFarPlaneChange();
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
		float verticalFOV;
		float aspectRatio;
		float nearPlane;
		float farPlane;
	};

	bool CreateCamera(Camera** cameraOut, CreateCameraParams params);
	void DestroyCamera(Camera* camera);
}