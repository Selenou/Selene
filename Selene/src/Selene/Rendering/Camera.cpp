#include "slnpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Selene
{
	Camera::Camera()
	{
		//todo: / viewport update 
	}

	void Camera::SetPerspective(float verticalFOV, float zNear, float zFar)
	{
		m_ProjectionType = ProjectionType::Perspective;

		m_PerspectiveFOV = verticalFOV;
		m_NearClip = zNear;
		m_FarClip = zFar;

		UpdateProjection();
	}

	void Camera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_ProjectionType = ProjectionType::Orthographic;

		m_OrthographicSize = size;
		m_NearClip = zNear;
		m_FarClip = zFar;

		UpdateProjection();
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position; 
		UpdateView();
	}

	void Camera::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		UpdateView();
	}

	void Camera::SetViewportSize(uint32_t width, uint32_t height)
	{ 
		m_AspectRatio = (width > 0 && height > 0) ? (float)width / (float)height : 0.0f;
		UpdateProjection(); 
	}

	void Camera::UpdateProjection()
	{
		switch (m_ProjectionType)
		{
			case ProjectionType::Perspective:
				m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_NearClip, m_FarClip);
				break;
			case ProjectionType::Orthographic:
				float orthoH = m_OrthographicSize * m_AspectRatio * 0.5f;
				float orthoV = m_OrthographicSize * 0.5f;
				m_ProjectionMatrix = glm::ortho(-orthoH, orthoH, -orthoV, orthoV, m_NearClip, m_FarClip);
				break;
		}

		UpdateViewProjection();
	}

	void Camera::UpdateView()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetForwardDirection(), GetUpDirection());
		UpdateViewProjection();
	}

	void Camera::UpdateViewProjection()
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}