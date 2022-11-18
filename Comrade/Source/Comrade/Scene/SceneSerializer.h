#pragma once

#include "Comrade/Scene/Scene.h"
#include "Comrade/Utils/Memory.h"

namespace Comrade
{
	class SceneSerializer
	{
	public:
		static bool Serialize(const MemoryRef<Scene>& scene, const std::string& outpath);
		static bool Deserialize(const MemoryRef<Scene>& scene, const std::string& inpath);
	};
}
