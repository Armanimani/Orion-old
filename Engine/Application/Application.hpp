#pragma once

#include "Engine/engine.hpp"
#include "Engine/Application/EngineContext.hpp"

#include <memory>

namespace orion
{
	class ORION_API Application
	{
	public:
		Application();
		~Application() = default;

		Application(const Application& other) = delete;
		Application(Application&& other) noexcept = delete;
		Application& operator=(const Application& other) = delete;
		Application& operator=(Application&& other) noexcept = delete;
		
		void execute() noexcept;
	private:
		std::unique_ptr<EngineContext> context {nullptr};
		
		void configure() noexcept;
		void initialize() noexcept;
		void update() noexcept;
		void finalize() noexcept;

		void updateContext() const noexcept;
	};
}
