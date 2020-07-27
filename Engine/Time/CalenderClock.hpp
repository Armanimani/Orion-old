#pragma once

#include <chrono>

#include "Engine/engine.hpp"

namespace orion
{
	struct ORION_API CalenderInformation
	{
		Int32 year{};
		Int32 moth{};
		Int32 day{};
		Int32 hour{};
		Int32 minute{};
		Int32 second{};
	};

	class ORION_API CalenderClock
	{
	public:
		using clock_type = std::chrono::system_clock;
		
		static CalenderInformation getCalenderInformation() noexcept;
	};
}