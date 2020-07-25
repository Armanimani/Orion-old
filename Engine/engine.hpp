#pragma once

#ifdef ORION_BUILD_DLL
	#define ORION_API __declspec(dllexport)
#else
	#define ORION_API __deespec(dllimport)
#endif

#include "Engine/Common/base_types.hpp"