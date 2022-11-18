#pragma once

namespace Comrade
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void OnImGuiRender() = 0;
	};
}
