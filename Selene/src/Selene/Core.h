#pragma once

#ifdef SLN_PLATFORM_WINDOWS
	#ifdef SLN_BUILD_DLL
		#define SELENE_API __declspec(dllexport)
	#else
		#define SELENE_API __declspec(dllimport)
	#endif
#else
	#error Selene only supports Windows!
#endif