#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#ifdef TIN_EXPORTS
		#define TIN_API __declspec(dllexport)
	#else
		#define TIN_API __declspec(dllimport)
	#endif
#else
	#define TIN_API
#endif