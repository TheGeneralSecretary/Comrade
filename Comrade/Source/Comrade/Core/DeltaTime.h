#pragma once

namespace Comrade
{
	class DeltaTime
	{
	public:
		DeltaTime()
			: m_Time(0)
		{}

		DeltaTime(double time)
			: m_Time(time)
		{}

		operator double() const { return m_Time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliSeconds() const { return m_Time * 1000.0f; }

	private:
		double m_Time;
	};
};
