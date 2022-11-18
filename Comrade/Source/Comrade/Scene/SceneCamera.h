#pragma once

#include "Comrade/Renderer/Camera.h"

namespace Comrade
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();

		void SetOrthographic(float size, float zNear, float zFar);
		void SetViewPort(int width, int height);

		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicSize = size; CalculateProjection(); }

		inline float GetOrthographicNear() const { return m_OrthographicNear; }
		inline void SetOrthographicNear(float zNear) { m_OrthographicNear = zNear; CalculateProjection(); }

		inline float GetOrthographicFar() const { return m_OrthographicFar; }
		inline void SetOrthographicFar(float zFar) { m_OrthographicFar = zFar; CalculateProjection(); }

		inline CameraProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(CameraProjectionType type) { m_ProjectionType = type; }

	private:
		void CalculateProjection();

	private:
		float m_OrthographicSize;
		float m_OrthographicNear, m_OrthographicFar;
		float m_AspectRatio;
		CameraProjectionType m_ProjectionType;		
	};
}
