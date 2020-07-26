#pragma once

#include <type_traits>

#include "Engine/engine.hpp"
#include "Engine/Memory/Allocators/IAllocator.hpp"

namespace orion
{
	class ORION_API StackAllocator;

	
	struct ORION_API StackAllocatorMarker
	{
		const StackAllocator* allocator {nullptr};
		Byte* address {nullptr};

		[[nodiscard]] Bool isValid() const noexcept;
	};

	
	class ORION_API StackAllocator final : public IAllocator
	{
	public:
		explicit StackAllocator(Size_t total_size);
		~StackAllocator();

		StackAllocator(const StackAllocator& other) = delete;
		StackAllocator(StackAllocator&& other) noexcept = delete;
		StackAllocator& operator=(const StackAllocator& other) = delete;
		StackAllocator& operator=(StackAllocator&& other) noexcept = delete;
		
		void* allocate(Size_t size, Size_t alignment) noexcept override;

		template<typename T>
		void* allocate() noexcept;
		
		void free(void* pointer) noexcept override;
		void reset() noexcept;

		[[nodiscard]] StackAllocatorMarker getMarker() const noexcept;
		void resetToMarker(const StackAllocatorMarker& marker) noexcept;
		
		[[nodiscard]] Size_t getTotalSize() const noexcept override;
		[[nodiscard]] Size_t getFreeSize() const noexcept override;
		[[nodiscard]] Size_t getAllocatedSize() const noexcept override;
	private:
		Size_t total_size {};
		Size_t current_offset {};
		Byte* start_address {};
		
		Byte* buffer {nullptr};

		void allocateBuffer() noexcept;
		
		[[nodiscard]] Byte* getCurrentHeadAddress() const noexcept;
		[[nodiscard]] Bool canAllocate(Size_t size, Size_t padding) const noexcept;
	};


	template <typename T>
	void* StackAllocator::allocate() noexcept
	{
		const auto size = sizeof(T);
		const auto alignment = std::alignment_of_v<T>;
		return allocate(size, alignment);
	}
}
