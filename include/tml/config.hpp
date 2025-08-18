#pragma once


#if defined(_WIN32) && defined(TML_DLL_EXPORT)
#  define TML_API __declspec(dllexport)
#elif defined(_WIN32)
#  define TML_API __declspec(dllimport)
#else
#  define TML_API
#endif
