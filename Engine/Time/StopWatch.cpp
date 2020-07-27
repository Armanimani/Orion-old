#include "Engine/Time/StopWatch.hpp"

namespace orion
{
	void StopWatch::start() noexcept
	{
		ORION_ASSERT(!is_running);

		start_time = clock_type::now();
		is_running = true;
	}
	
	void StopWatch::stop() noexcept
	{
		ORION_ASSERT(is_running);

		const auto now = clock_type::now();
		elapsed_duration += std::chrono::duration_cast<duration_type>(now - start_time);
		is_running = false;
	}
	
	void StopWatch::reset() noexcept
	{
		elapsed_duration = {};
		start_time = clock_type::now();
	}
	
	StopWatch::duration_type StopWatch::getElapsedTime() const noexcept
	{
		if (!is_running)
			return elapsed_duration;

		const auto now = clock_type::now();
		const auto current_duration = std::chrono::duration_cast<duration_type>(now - start_time);
		return elapsed_duration + current_duration;
	}
}
