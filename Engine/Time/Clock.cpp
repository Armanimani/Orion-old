#include "Engine/Time/Clock.hpp"

namespace orion
{
	void Clock::start() noexcept
	{
		ORION_ASSERT(!is_running);

		const auto now = clock_type::now();
		start_time = now;
		last_tick_time = now;
		
		is_running = true;
	}
	
	void Clock::stop() noexcept
	{
		ORION_ASSERT(is_running);

		tick();
		is_running = false;
	}
	
	void Clock::tick() noexcept
	{
		ORION_ASSERT(is_running);

		update();
	}
	
	Clock::duration_type Clock::getElapsedTime() const noexcept
	{
		return elapsed_duration;
	}
	
	Clock::duration_type Clock::getLastTickTime() const noexcept
	{
		return last_tick_duration;
	}
	
	Int64 Clock::getNumberOfTicks() const noexcept
	{
		return number_of_ticks;
	}


	void Clock::update() noexcept
	{
		ORION_ASSERT(is_running);

		// Calculate previous frame state
		const auto now = clock_type::now();
		last_tick_duration = std::chrono::duration_cast<duration_type>(now - last_tick_time);
		last_tick_duration = std::chrono::duration_cast<duration_type>(now - last_tick_time);

		// Update current state;
		last_tick_time = now;
		number_of_ticks++;
	}
}
