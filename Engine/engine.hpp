#pragma once

#ifdef ORION_BUILD_DLL
	#define ORION_API __declspec(dllexport)
#else
	#define ORION_API __declspec(dllimport)
#endif

#ifdef _DEBUG
	#define ORION_DEBUG
#endif

#include "Engine/Common/base_types.hpp"