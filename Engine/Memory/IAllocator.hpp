#pragma once

#include <cstdlib>

namespace orion
{
	class IAllocator
	{
	public:
		virtual void* allocate(std::size_t size, std::size_t alignment = 0) = 0;
		virtual void free(void* pointer) = 0;

		[[nodiscard]] virtual std::size_t getTotalSize() const noexcept = 0;
		[[nodiscard]] virtual std::size_t getFreeSize() const noexcept = 0;
		[[nodiscard]] virtual std::size_t getAllocatedSize() const noexcept = 0;
	};
}