#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#error "x64 platforms are not supported"
	#else
		#define COMRADE_PLATFORM_WINDOWS
	#endif
#else
		#error "unsupported platform"
#endif

#ifdef COMRADE_DEBUG
	#ifdef COMRADE_PLATFORM_WINDOWS
		#define COMRADE_DEBUGBREAK() __debugbreak()	
	#else
		#error "platform doesnt support debugbreak"
	#endif

	#define COMRADE_ENABLE_ASSERTS
#else
	#define COMRADE_DEBUGBREAK()
#endif
