#include "gtest/gtest.h"

#include <Engine/Memory/Allocators/StackAllocator.hpp>
#include <Engine/Memory/memory_literals.hpp>

using namespace orion;

TEST(StackAllocator, construction)
{
	StackAllocator allocator(10_MB);
}

TEST(StackAllocator, sizes)
{
	StackAllocator allocator(100_MB);
	
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB, allocator.getFreeSize());
	ASSERT_EQ(0, allocator.getAllocatedSize());
}

TEST(StackAllocator, allocation)
{
	StackAllocator allocator(100_MB);
	const auto size = 8;
	const auto alignment = 8;
	auto* address = allocator.allocate(size, alignment);

	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - size, allocator.getFreeSize());
	ASSERT_EQ(size, allocator.getAllocatedSize());
}


TEST(StackAllocator, allocation_template)
{
	StackAllocator allocator(100_MB);
	auto* address = allocator.allocate<UInt8>();
	const auto size = sizeof(UInt8);

	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - size, allocator.getFreeSize());
	ASSERT_EQ(size, allocator.getAllocatedSize());
}

TEST(StackAllocator, allocation_verification)
{
	StackAllocator allocator(100_MB);

	auto* value_int = new (allocator.allocate<UInt8>()) UInt8(10);
	auto* value_boolean = new (allocator.allocate<Bool>()) Bool(true);
	auto* value_float = new (allocator.allocate<Float>()) Float(20.0f);

	ASSERT_EQ(*value_int, 10);
	ASSERT_EQ(*value_boolean, true);
	ASSERT_FLOAT_EQ(*value_float, 20.0f);

	const auto expected_allocated_size = 1 + 1 + (2) + 4;
	ASSERT_EQ(allocator.getAllocatedSize (), expected_allocated_size);
	ASSERT_EQ(allocator.getFreeSize(), 100_MB - expected_allocated_size);
}

TEST(StackAllocator, allocation_structure)
{
	struct TestStruct
	{
		UInt8 value_int {20};
		UInt8 value_bool {true};
		Float value_float {1.24f};
	};
	
	StackAllocator allocator(100_MB);

	const auto* value = new (allocator.allocate<TestStruct>()) TestStruct {10, true, 3.14f};

	ASSERT_EQ(value->value_int, 10);
	ASSERT_EQ(value->value_bool, true);
	ASSERT_FLOAT_EQ(value->value_float, 3.14f);

	const auto expected_allocated_size = 1 + 1 + (2) + 4;
	ASSERT_EQ(allocator.getAllocatedSize(), expected_allocated_size);
	ASSERT_EQ(allocator.getFreeSize(), 100_MB - expected_allocated_size);
}

TEST(StackAllocator, free)
{
	StackAllocator allocator(100_MB);
	auto* address = allocator.allocate<UInt8>();
	const auto size = sizeof(UInt8);

	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - size, allocator.getFreeSize());
	ASSERT_EQ(size, allocator.getAllocatedSize());

	allocator.free(address);
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - size, allocator.getFreeSize());
	ASSERT_EQ(size, allocator.getAllocatedSize());
}

TEST(StackAllocator, reset)
{
	StackAllocator allocator(100_MB);
	auto* address = allocator.allocate<UInt8>();
	const auto size = sizeof(UInt8);

	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - size, allocator.getFreeSize());
	ASSERT_EQ(size, allocator.getAllocatedSize());

	allocator.reset();
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB, allocator.getFreeSize());
	ASSERT_EQ(0, allocator.getAllocatedSize());
}

TEST(StackAllocator, marker_operations)
{
	StackAllocator allocator(100_MB);

	auto* address = allocator.allocate<UInt8>();
	const auto before_reset_size = sizeof(UInt8);
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - before_reset_size, allocator.getFreeSize());
	ASSERT_EQ(before_reset_size, allocator.getAllocatedSize());
	
	const auto marker = allocator.getMarker();

	auto* temporary_address = allocator.allocate<UInt8>();
	const auto temporary_size = before_reset_size + sizeof(UInt8);
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - temporary_size, allocator.getFreeSize());
	ASSERT_EQ(temporary_size, allocator.getAllocatedSize());

	allocator.resetToMarker(marker);
	ASSERT_EQ(100_MB, allocator.getTotalSize());
	ASSERT_EQ(100_MB - before_reset_size, allocator.getFreeSize());
	ASSERT_EQ(before_reset_size, allocator.getAllocatedSize());
}