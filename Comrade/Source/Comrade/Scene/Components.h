#pragma once

#include <string>

namespace Comrade
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};
}
