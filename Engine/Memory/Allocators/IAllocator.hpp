#pragma once

#include <cstdlib>
#include "Engine/engine.hpp"

namespace orion
{
	class ORION_API IAllocator
	{
	public:		
		virtual void* allocate(Size_t size, Size_t alignment) noexcept = 0;
		virtual void free(void* pointer) noexcept = 0;

		[[nodiscard]] virtual Size_t getTotalSize() const noexcept = 0;
		[[nodiscard]] virtual Size_t getFreeSize() const noexcept = 0;
		[[nodiscard]] virtual Size_t getAllocatedSize() const noexcept = 0;
	};
}