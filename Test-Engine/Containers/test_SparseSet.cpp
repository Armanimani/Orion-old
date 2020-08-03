#include <gtest/gtest.h>
#include <Engine/Containers/SparseSet.hpp>

using namespace orion;

TEST(SparseSet, constructor_and_capacity)
{
	const auto set = SparseSet<int>(10);
	ASSERT_EQ(set.capacity(), 10);
}

TEST(SparseSet, size)
{
	auto set = SparseSet<int>(10);
	set.construct(0, 10);
	set.construct(2, 20);
	ASSERT_EQ(set.size(), 2);
}

TEST(SparseSet, sizeInByes)
{
	auto set = SparseSet<int>(10);
	set.construct(0, 10);
	set.construct(5, 20);
	ASSERT_EQ(set.sizeInBytes(), 2 * sizeof(int));
}

TEST(SparseSet, hasElement)
{
	auto set = SparseSet<int>(10);
	ASSERT_FALSE(set.hasElement(0));
	ASSERT_FALSE(set.hasElement(5));

	set.construct(5, 20);
	ASSERT_FALSE(set.hasElement(0));
	ASSERT_TRUE(set.hasElement(5));
}

TEST(SparseSet, getElementPointer_nonConst)
{
	auto set = SparseSet<int>(10);
	set.construct(5, 20);

	ASSERT_EQ(set.getElementPointer(0), nullptr);
	ASSERT_EQ(*set.getElementPointer(5), 20);

	*set.getElementPointer(5) = 100;
	ASSERT_EQ(set.getElementPointer(0), nullptr);
	ASSERT_EQ(*set.getElementPointer(5), 100);
}

TEST(SparseSet, getElementPointer_const)
{
	auto set = SparseSet<int>(10);
	set.construct(5, 20);
	const auto& ref = set;

	ASSERT_EQ(ref.getElementPointer(0), nullptr);
	ASSERT_EQ(*ref.getElementPointer(5), 20);
}

TEST(SparseSet, getElement_nonConst)
{
	auto set = SparseSet<int>(10);
	set.construct(5, 20);
	ASSERT_EQ(set.getElement(5), 20);

	set.getElement(5) = 100;
	ASSERT_EQ(set.getElement(5), 100);
}

TEST(SparseSet, getElement_const)
{
	auto set = SparseSet<int>(10);
	set.construct(5, 20);
	const auto& ref = set;
	ASSERT_EQ(ref.getElement(5), 20);
}

TEST(SparseSet, construct_fundamentalTypes)
{
	auto set = SparseSet<int>(10);
	set.construct(5, 20);
	ASSERT_EQ(set.getElement(5), 20);
}

TEST(SparseSet, construct_structure)
{
	struct Data
	{
		explicit Data(const int val) : value {val} {};
		int value {};
	};

	auto set = SparseSet<Data>(10);
	set.construct(5, 20);
	ASSERT_EQ(set.getElement(5).value, 20);
}

TEST(SparseSet, emplace_fundamentalTypes)
{
	auto set = SparseSet<int>(10);
	auto value = 9;

	set.emplace(5, std::move(value));
	ASSERT_EQ(set.getElement(5), 9);
}

TEST(SparseSet, emplace_structure)
{
	struct Data
	{
		int value {};
	};

	auto set = SparseSet<Data>(10);
	auto container = Data();
	container.value = 9;

	set.emplace(5, std::move(container));
	ASSERT_EQ(set.getElement(5).value, 9);
}

TEST(SparseSet, erase)
{
	auto set = SparseSet<int>(5);
	set.construct(0, 10);
	set.construct(1, 11);
	set.construct(3, 33);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(set.getElement(0), 10);
	ASSERT_EQ(set.getElement(1), 11);
	ASSERT_EQ(set.getElementPointer(2), nullptr);
	ASSERT_EQ(set.getElement(3), 33);
	ASSERT_EQ(set.getElementPointer(4), nullptr);

	set.erase(0);
	ASSERT_EQ(set.size(), 2);
	ASSERT_EQ(set.getElementPointer(0), nullptr);
	ASSERT_EQ(set.getElement(1), 11);
	ASSERT_EQ(set.getElementPointer(2), nullptr);
	ASSERT_EQ(set.getElement(3), 33);
	ASSERT_EQ(set.getElementPointer(4), nullptr);

	set.construct(0, 99);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(set.getElement(0), 99);
	ASSERT_EQ(set.getElement(1), 11);
	ASSERT_EQ(set.getElementPointer(2), nullptr);
	ASSERT_EQ(set.getElement(3), 33);
	ASSERT_EQ(set.getElementPointer(4), nullptr);
}