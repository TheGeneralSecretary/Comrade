#pragma once

#include "Comrade/Renderer/Camera.h"

namespace Comrade
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();

		void SetOrthographic(float size, float zNear, float zFar);
		void SetPerspective(float fovDeg, float zNear, float zFar);
		void SetViewPort(int width, int height);

		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicSize = size; CalculateProjection(); }
		inline float GetOrthographicNear() const { return m_OrthographicNear; }
		inline void SetOrthographicNear(float zNear) { m_OrthographicNear = zNear; CalculateProjection(); }
		inline float GetOrthographicFar() const { return m_OrthographicFar; }
		inline void SetOrthographicFar(float zFar) { m_OrthographicFar = zFar; CalculateProjection(); }

		inline float GetPerspectiveFOV() const { return m_PerspectiveFOV; }
		inline void SetPerspectiveFOV(float fov) { m_PerspectiveFOV = fov; CalculateProjection(); }
		inline float GetPerspectiveNear() const { return m_PerspectiveNear; }
		inline void SetPerspectiveNear(float zNear) { m_PerspectiveNear = zNear; CalculateProjection(); }
		inline float GetPerspectiveFar() const { return m_PerspectiveFar; }
		inline void SetPerspectiveFar(float zFar) { m_PerspectiveFar = zFar; CalculateProjection(); }

		inline CameraProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(CameraProjectionType type) { m_ProjectionType = type; }

	private:
		void CalculateProjection();

	private:
		CameraProjectionType m_ProjectionType;		
		float m_AspectRatio;
		float m_OrthographicSize, m_OrthographicNear, m_OrthographicFar;
		float m_PerspectiveFOV, m_PerspectiveNear, m_PerspectiveFar;
	};
}
