#pragma once

#ifdef SLN_BUILD_DLL
	#define SELENE_API __declspec(dllexport)
#else
	#define SELENE_API __declspec(dllimport)
#endif