#include "comradepch.h"
#include "Comrade/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Comrade
{
	SceneCamera::SceneCamera()
		: m_ProjectionType(CameraProjectionType::Perspective), m_AspectRatio(1.3f),
		m_OrthographicSize(1.0f), m_OrthographicNear(-1.0f), m_OrthographicFar(1.0f),
		m_PerspectiveFOV(45.0f), m_PerspectiveNear(0.1f), m_PerspectiveFar(100.0f)
	{
		CalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_ProjectionType = CameraProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = zNear;
		m_OrthographicFar = zFar;
		CalculateProjection();
	}

	void SceneCamera::SetPerspective(float fovDeg, float zNear, float zFar)
	{
		m_ProjectionType = CameraProjectionType::Perspective;
		m_PerspectiveFOV = fovDeg;
		m_PerspectiveNear = zNear;
		m_PerspectiveFar = zFar;
		CalculateProjection();
	}

	void SceneCamera::SetViewPort(int width, int height)
	{
		m_AspectRatio = (float)width / (float)height;
		CalculateProjection();
	}

	void SceneCamera::CalculateProjection()
	{
		if(m_ProjectionType == CameraProjectionType::Orthographic)
			m_Projection = glm::ortho(-m_AspectRatio * m_OrthographicSize * 0.5f, m_AspectRatio * m_OrthographicSize * 0.5f, -m_OrthographicSize * 0.5f, m_OrthographicSize * 0.5f, m_OrthographicNear, m_OrthographicFar);

		if (m_ProjectionType == CameraProjectionType::Perspective)
			m_Projection = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
	}
}
