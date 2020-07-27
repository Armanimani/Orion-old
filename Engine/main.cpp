#include "Engine/DesignPatterns/ServiceLocator.hpp"
#include "Engine/engine.hpp"

#ifdef ORION_PLATFORM_WINDOWS
	#include <Windows.h>
	#include "Engine/Logging/Platform/Windows/Win32ConsoleLoggerAdapter.hpp"

	BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID lpReserved)
	{
	    switch (fdwReason)
	    {
	    case DLL_PROCESS_ATTACH:
			orion::ServiceLocator<orion::IConsoleLoggerAdapter>::provide(std::make_unique<orion::Win32ConsoleLoggerAdapter>());
	        break;
	    case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
	    case DLL_PROCESS_DETACH:
	        break;
		default:
	    	return FALSE;
	    }
	    return TRUE;
	}
#endif