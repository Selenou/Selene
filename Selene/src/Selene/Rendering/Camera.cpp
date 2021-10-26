#include "slnpch.h"
#include "Camera.h"

#include "Selene/Core/KeyCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Selene
{
	/*void Camera::Update(Timestep ts)
	{
		// Position
		if (Input::IsKeyPressed(Key::A))
		{
			m_Position -= GetRightDirection() * m_Speed * (float)ts;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position += GetRightDirection() * m_Speed * (float)ts;
		}

		if (m_ProjectionType == ProjectionType::Perspective)
		{
			if (Input::IsKeyPressed(Key::W))
			{
				m_Position += GetForwardDirection() * m_Speed * (float)ts;
			}
			else if (Input::IsKeyPressed(Key::S))
			{
				m_Position -= GetForwardDirection() * m_Speed * (float)ts;
			}
		}
		else //ProjectionType::Orthographic
		{
			if (Input::IsKeyPressed(Key::W))
			{
				m_Position += GetUpDirection() * m_Speed * (float)ts;
			}
			else if (Input::IsKeyPressed(Key::S))
			{
				m_Position -= GetUpDirection() * m_Speed * (float)ts;
			}
		}
		

		// Orientation
		if (Input::IsMouseButtonPressed(MouseButton::Button0))
		{
			float yaw = glm::radians((m_LastMousePosition.X - m_NextMousePosition.X) * m_RotationSpeed); 
			float pitch = glm::radians((m_LastMousePosition.Y - m_NextMousePosition.Y) * m_RotationSpeed);

			glm::quat qPitch = glm::normalize(glm::angleAxis(pitch, m_RightVector));
			glm::quat qYaw = glm::normalize(glm::angleAxis(yaw, m_UpVector));

			m_Orientation = qYaw * m_Orientation * qPitch; // gimbal locked on purpose, fps style, no roll
		}

		m_LastMousePosition = m_NextMousePosition;

		UpdateView();
	}*/

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
		m_Orientation = glm::quat(glm::radians(rotation));
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