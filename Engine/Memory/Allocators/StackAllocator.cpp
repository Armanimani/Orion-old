#include "Engine/Memory/Allocators/StackAllocator.hpp"
#include "Engine/Memory/Allocators/allocator_utilities.hpp"

namespace orion
{
	Bool StackAllocatorMarker::isValid() const noexcept
	{
		if (!address)
			return false;

		if (!allocator)
			return false;

		return true;
	}

	StackAllocator::StackAllocator(const Size_t total_size)
		: total_size {total_size}
	{
		allocateBuffer();
	}

	StackAllocator::~StackAllocator()
	{
		delete[] buffer;
	}

	void StackAllocator::reset() noexcept
	{		
		current_offset = 0;
	}

	StackAllocatorMarker StackAllocator::getMarker() const noexcept
	{
		const StackAllocatorMarker marker {this, getCurrentHeadAddress()};
		return marker;
	}
	
	void StackAllocator::resetToMarker(const StackAllocatorMarker& marker) noexcept
	{
		ORION_ASSERT(marker.isValid());
		ORION_ASSERT(marker.allocator == this);
		
		current_offset = marker.address - start_address;
	}

	void* StackAllocator::allocate(const Size_t size, const Size_t alignment) noexcept
	{
		auto* address = getCurrentHeadAddress();
		const auto padding = calculatePadding(address, alignment);

		if (!canAllocate(size, padding))
			return nullptr;

		current_offset += size + padding;
		return static_cast<void*>(address);
	}

	void StackAllocator::free(void* pointer) noexcept
	{
		/* The free operation is a no-op operation for stack allocator */
		return; 
	}
	
	Size_t StackAllocator::getTotalSize() const noexcept
	{
		return total_size;
	}
	
	Size_t StackAllocator::getFreeSize() const noexcept
	{
		return getTotalSize() - getAllocatedSize();
	}
	
	Size_t StackAllocator::getAllocatedSize() const noexcept
	{
		return getCurrentHeadAddress() - start_address;
	}

	void StackAllocator::allocateBuffer() noexcept
	{
		buffer = new Byte[total_size];
		start_address = &buffer[0];
	}

	Byte* StackAllocator::getCurrentHeadAddress() const noexcept
	{
		return start_address + current_offset;
	}

	Bool StackAllocator::canAllocate(const Size_t size, const Size_t padding) const noexcept
	{
		return getAllocatedSize() + size + padding < total_size;
	}
}
