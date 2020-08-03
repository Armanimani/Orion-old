#include "Engine/Application/Application.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"
#include "Engine/Time/StopWatch.hpp"
#include "Engine/Time/Clock.hpp"

#include <string>

namespace orion
{
	template<typename Function>
	void executeAndLogTime(const std::string& function_name, Function&& function)
	{
		ConsoleLogger::logInformation(k_engine_channel, function_name + "...");
		auto stop_watch = StopWatch();
		stop_watch.start();

		function();

		const auto elapsed_time = stop_watch.getElapsedTime().count();
		ConsoleLogger::logInformation(k_engine_channel, function_name + " Done! took " + std::to_string(elapsed_time) + " ms");
	}
	
	Application::Application()
	{
		context = std::make_unique<EngineContext>();
	}

	void Application::execute() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Starting...");

		configure();
		initialize();
		update();
		finalize();
	}
	
	void Application::configure() noexcept
	{
		executeAndLogTime("Configuring", [=]()
			{
				//TODO: configure all pipelines
			}
		);
	}
	
	void Application::initialize() noexcept
	{
		executeAndLogTime("Initializing", [=]()
			{
				//TODO: initialize all pipelines
			}
		);
	}
	
	void Application::update() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Updating...");
		auto frame_clock = Clock();

		context->is_running = true;
		frame_clock.start();
		while (context->is_running)
		{
			frame_clock.tick();

			updateContext();
			//TODO: update all pipelines
		}

		ConsoleLogger::logInformation(k_engine_channel, "Updating done! took " + std::to_string(frame_clock.getElapsedTime().count()) + " ms");
	}
	
	void Application::finalize() noexcept
	{
		executeAndLogTime("finalizing", [=]()
			{
				//TODO: finalize all pipelines
			}
		);
	}
	
	void Application::updateContext() const noexcept
	{
		//TODO: update event manager system
	}
}
