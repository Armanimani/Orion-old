#pragma once

#include "Engine/engine.hpp"

namespace orion
{
	inline Size_t calculatePadding(Byte* address, const Size_t alignment)
	{
		const auto base_address = reinterpret_cast<Size_t>(address);
		const auto multiplier = (base_address / alignment);
		const auto aligned_address = multiplier * alignment;
		const auto padding = base_address - aligned_address;
		return padding;
	}

	inline Size_t calculatePadding(Byte* address, const Size_t alignment, const Size_t extra_byte)
	{
		const auto padding = calculatePadding(address, alignment);
		const auto required_space = (extra_byte > padding) ? extra_byte - padding : 0;
		
		if (required_space % alignment > 0)
			return padding + alignment * (1 + (required_space / alignment));
		else
			return padding + alignment * (required_space / alignment);
	}
}
