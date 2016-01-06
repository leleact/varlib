
#ifndef _VARLIB_H
#define _VARLIB_H

#ifdef _WIN32
	#ifdef VARLIB_API_EXPORT
		#define VARLIB_API __declspec(dllexport)
	#elif defined(VARLIB_API_IMPORT)
		#define VARLIB_API __declspec(dllimport)
	#else
		#define VARLIB_API
	#endif

	#ifdef FUNCTION_MODE_STDCALL
		#define FUNCTION_MODE __stdcall
	#elif defined(FUNCTION_MODE_CDECL)
		#define FUNCTION_MODE __cdecl
	#else
		#define FUNCTION_MODE
	#endif
#else
	#define VARLIB_API
	#define FUNCTION_MODE
#endif

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

#if defined(DEBUG)
  #ifdef _WIN32
	#define VARLIBASSERT(x) if ( !((void)0,(x))) { __debugbreak(); }
  #elif
	#define VARLIBASSERT(x)  assert(x)
  #endif
#else
    #define VARLIBASSERT(x) {}
#endif

#endif
