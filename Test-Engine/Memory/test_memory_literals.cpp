#include "gtest/gtest.h"

#include <Engine/Memory/memory_literals.hpp>

using namespace orion;

TEST(memory_literals, KB)
{
	const auto expected_value {1ull * 1024ull};

	ASSERT_EQ(1_KB, expected_value);
}

TEST(memory_literals, MB)
{
	const auto expected_value {1ull * 1024ull * 1024ull};

	ASSERT_EQ(1_MB, expected_value);
}

TEST(memory_literals, GB)
{
	const auto expected_value {1ull * 1024ull * 1024ull * 1024ull};

	ASSERT_EQ(1_GB, expected_value);
}