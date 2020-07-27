#pragma once

#include <cassert>

#ifdef ORION_BUILD_DLL
	#define ORION_API __declspec(dllexport)
#else
	#define ORION_API __declspec(dllimport)
#endif

#ifdef _DEBUG
	#define ORION_DEBUG
#endif

#ifdef ORION_DEBUG
	#define ORION_ASSERT(Expression) assert(Expression)
#else
	#define ORION_ASSERT(Expression) ;
#endif

#ifdef _WIN32
	#define ORION_PLATFORM_WINDOWS
#endif

// Disable warning for STL using in private data member
#pragma warning(disable:4251)
// Disable warning for exception handling
#pragma warning(disable:4530)

#include "Engine/Common/base_types.hpp"