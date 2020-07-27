#pragma once

#include "Engine/engine.hpp"

namespace orion
{
	enum class ORION_API LoggingLevel : UInt8
	{
		critical = 1 << 1,
		warning = 1 << 2,
		information = 1 << 3,
		debug = 1 << 4
	};
}
