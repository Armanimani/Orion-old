#include <gtest/gtest.h>
#include <Engine/Containers/StaticArray.hpp>

using namespace orion;

TEST(StaticArray, construction)
{
	StaticArray<int, 2> array(10);

	ASSERT_EQ(array[0], 10);
	ASSERT_EQ(array[1], 10);
}

TEST(StaticArray, construction_default)
{
	StaticArray<int, 2> array;

	ASSERT_EQ(array[0], 0);
	ASSERT_EQ(array[1], 0);
}

TEST(StaticArray, size)
{
	StaticArray<int, 2> array;

	ASSERT_EQ(array.size, 2);
}

TEST(StaticArray, operator_bracket)
{
	StaticArray<int, 2> array;
	array[0] = 20;
	array[1] = 30;

	ASSERT_EQ(array[0], 20);
	ASSERT_EQ(array[1], 30);
}

TEST(StaticArray, operator_equality)
{
	StaticArray<int, 2> lhs;
	lhs[0] = 20;
	lhs[1] = 30;

	StaticArray<int, 2> rhs;
	rhs[0] = 20;
	rhs[1] = 30;

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);
}

TEST(StaticArray, operator_inequality)
{
	StaticArray<int, 2> lhs;
	lhs[0] = 20;
	lhs[1] = 30;

	StaticArray<int, 2> rhs;
	rhs[0] = 21;
	rhs[1] = 30;

	ASSERT_FALSE(lhs == rhs);
	ASSERT_TRUE(lhs != rhs);
}