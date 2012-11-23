#pragma once
#include "KofResource.h"

#if defined _AFXDLL && !defined _KOFPACK_STATIC_
	#ifdef _KOFPACK_
		#define KOFPACKDLLEXPORT  _declspec(dllexport)
	#else
		#define KOFPACKDLLEXPORT  _declspec(dllimport)
	#endif
	#else
		#define KOFPACKDLLEXPORT
#endif