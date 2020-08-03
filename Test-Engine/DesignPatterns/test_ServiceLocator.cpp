#include <gtest/gtest.h>
#include <Engine/DesignPatterns/ServiceLocator.hpp>

using namespace orion;

TEST(Locator, provide_and_get)
{
	struct DummyService
	{
		int value {};
	};

	auto service = std::make_unique<DummyService>();
	service->value = 10;
	ServiceLocator<DummyService>::provide(std::move(service));


	ASSERT_TRUE(ServiceLocator<DummyService>::get());
	auto* const registered_service = ServiceLocator<DummyService>::get();

	ASSERT_EQ(registered_service->value, 10);
}