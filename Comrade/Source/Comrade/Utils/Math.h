#pragma once

#include <glm/glm.hpp>

namespace Comrade
{
	namespace Math
	{
		bool MatrixDecompose(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}
}
