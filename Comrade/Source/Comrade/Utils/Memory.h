#pragma once

#include <memory>

namespace Comrade
{
	template<typename T>
	using MemoryRef = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr MemoryRef<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using MemoryScope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr MemoryScope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
