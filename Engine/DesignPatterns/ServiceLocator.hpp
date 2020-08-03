#pragma once

#include "Engine/engine.hpp"

#include <memory>

namespace orion
{
	template<typename IService>
	class ServiceLocator
	{
	public:
		static void provide(std::unique_ptr<IService>&& service) noexcept;
		static IService* get() noexcept;
	private:
		inline static std::unique_ptr<IService> s_service {nullptr};
	};


	template <typename IService>
	void ServiceLocator<IService>::provide(std::unique_ptr<IService>&& service) noexcept
	{
		if (s_service)
			s_service.reset();

		s_service = std::move(service);
	}

	template <typename IService>
	IService* ServiceLocator<IService>::get() noexcept
	{
		ORION_ASSERT(s_service);

		return s_service.get();
	}
}