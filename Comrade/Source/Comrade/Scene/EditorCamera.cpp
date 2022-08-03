#include "comradepch.h"
#include "Comrade/Scene/EditorCamera.h"
#include "Comrade/Input/Input.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Comrade
{
	EditorCamera::EditorCamera(float fovDeg, float aspect, float zNear, float zFar)
		: m_ViewMatrix(glm::mat4(1.0f)),
		m_Translation(glm::vec3(0.0f, 0.0f, 4.0f)), m_Rotation({ 0.0f, 0.0f, 0.0f }), m_Scale({ 1.0f, 1.0f, 1.0f }),
		m_AspectRatio(aspect), m_PerspectiveFOV(fovDeg), m_PerspectiveNear(zNear), m_PerspectiveFar(zFar),
		m_TranslationSpeed(1.0f), m_RotationSpeed(1.0f)

	{
		CalculateProjection();
	}

	void EditorCamera::SetProjection(float fovDeg, float zNear, float zFar)
	{
		m_PerspectiveFOV = fovDeg;
		m_PerspectiveNear = zNear;
		m_PerspectiveFar = zFar;
		CalculateProjection();
	}

	void EditorCamera::SetViewPort(int width, int height)
	{
		m_AspectRatio = (float)width / (float)height;
		CalculateProjection();
	}

	void EditorCamera::OnUpdate(DeltaTime dt)
	{
		if (Input::IsKeyPressed(KeyCode::W))
			m_Translation.y += m_TranslationSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::S))
			m_Translation.y -= m_TranslationSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::A))
			m_Translation.x -= m_TranslationSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::D))
			m_Translation.x += m_TranslationSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::Q))
			m_Rotation += m_RotationSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::E))
			m_Rotation -= m_RotationSpeed * dt;

		CalculateProjection();
	}

	void EditorCamera::OnEvent(Event& event)
	{
	}

	void EditorCamera::CalculateProjection()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Translation) * glm::toMat4(glm::quat(m_Rotation)) * glm::scale(glm::mat4(1.0f), m_Scale);
		m_Projection = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_Projection * m_ViewMatrix;
	}
}
