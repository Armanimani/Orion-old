#pragma once

#include "Engine/engine.hpp"

namespace orion
{
	struct ORION_API Entity
	{
		explicit Entity(const UInt64 id) : id{id} {}
		
		UInt64 id {};
	};
}
