#include "comradepch.h"
#include "Comrade/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Comrade
{
	SceneCamera::SceneCamera()
		: m_OrthographicSize(1.0f), m_OrthographicNear(-1.0f), m_OrthographicFar(1.0f), m_AspectRatio(1.0f), m_ProjectionType(CameraProjectionType::Orthographic)
	{
	}

	void SceneCamera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = zNear;
		m_OrthographicFar = zFar;
		CalculateProjection();
	}

	void SceneCamera::SetViewPort(int width, int height)
	{
		m_AspectRatio = (float)width / (float)height;
		CalculateProjection();
	}

	void SceneCamera::CalculateProjection()
	{
		m_Projection = glm::ortho(-m_AspectRatio * m_OrthographicSize, m_AspectRatio * m_OrthographicSize, -m_OrthographicSize, m_OrthographicSize, m_OrthographicNear, m_OrthographicFar);
	}
}
