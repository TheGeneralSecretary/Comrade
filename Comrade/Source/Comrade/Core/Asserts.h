#pragma once

#include "Comrade/Core/System.h"
#include "Comrade/Core/Logger.h"

#ifdef COMRADE_ENABLE_ASSERTS
	#define COMRADE_ASSERT(x, msg) { if(!(x)) { COMRADE_LOG_ERROR("Error: {}, File: {}, Line: {}", msg, __FILE__, __LINE__); COMRADE_DEBUGBREAK(); } }
#else
	#define COMRADE_ASSERT(...)
#endif
