#pragma once

#include "Comrade/Renderer/Camera.h"
#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Events/Event.h"

#include <glm/glm.hpp>

namespace Comrade
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera(float fovDeg, float aspect, float zNear, float zFar);

		void SetProjection(float fovDeg, float zNear, float zFar);
		void SetViewPort(int width, int height);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& event);

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

	private:
		void CalculateProjection();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;
		glm::vec3 m_Translation, m_Rotation, m_Scale;
		float m_AspectRatio, m_PerspectiveFOV, m_PerspectiveNear, m_PerspectiveFar;
		float m_TranslationSpeed, m_RotationSpeed;
	};
}
