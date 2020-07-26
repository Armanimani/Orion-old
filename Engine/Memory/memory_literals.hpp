#pragma once

#include "Engine/engine.hpp"

namespace orion
{
	namespace details
	{
		constexpr auto k_memory_kilo_size_coefficient = 1024;
	}
	
	constexpr Size_t operator"" _KB(const Size_t value) noexcept
	{
		return value * details::k_memory_kilo_size_coefficient;
	}

	constexpr Size_t operator"" _MB(const Size_t value) noexcept
	{
		return value * details::k_memory_kilo_size_coefficient * details::k_memory_kilo_size_coefficient;
	}

	constexpr Size_t operator"" _GB(const Size_t value) noexcept
	{
		return value * details::k_memory_kilo_size_coefficient * details::k_memory_kilo_size_coefficient * details::k_memory_kilo_size_coefficient;
	}
}
