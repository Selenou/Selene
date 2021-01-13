#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

namespace Selene
{
	class Camera
	{
	public:
		enum class ProjectionType 
		{ 
			Perspective = 0, 
			Orthographic = 1 
		};
	public:
		Camera();
	public:
		void SetPerspective(float verticalFOV, float zNear = 0.01f, float zFar = 1000.0f);
		void SetOrthographic(float size, float zNear = -1.0f, float zFar = 1.0f);
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetViewportSize(uint32_t width, uint32_t height);
	public:
		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		inline float GetNearClip() const { return m_NearClip; }
		inline float GetFarClip() const { return m_FarClip; }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline glm::vec3& GetRotation() { return m_Rotation; } // const ?
		inline const glm::quat GetRotationQuat() const { return glm::quat(m_Rotation); }
		inline const glm::vec3 GetForwardDirection() const { return GetRotationQuat() * glm::vec3({ 0.0f, 0.0f, -1.0f }); }
		inline const glm::vec3 GetRightDirection() const { return GetRotationQuat() * glm::vec3({ 1.0f, 0.0f, 0.0f }); }
		inline const glm::vec3 GetUpDirection() const { return GetRotationQuat() * glm::vec3({ 0.0f, 1.0f, 0.0f }); }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void UpdateProjection();
		void UpdateView();
		void UpdateViewProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_PerspectiveFOV = 45.0f;
		float m_OrthographicSize = 10.0f;
		float m_NearClip = -1.0f;
		float m_FarClip = 1.0f;

		float m_AspectRatio;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
	};
}