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

#define _VARLIB_BEGIN_NAMESPACE BEGIN_NAMESPACE(varlib)
#define _VARLIB_END_NAMESPACE END_NAMESPACE

#define VARLIB_NAMESPACE_BEGIN BEGIN_NAMESPACE(varlib)
#define VARLIB_NAMESPACE_END END_NAMESPACE

#if defined(DEBUG)
#ifdef _WIN32
#define VARLIBASSERT(x) if ( !((void)0,(x))) { __debugbreak(); }
#elif
#define VARLIBASSERT(x)  assert(x)
#endif
#else
#define VARLIBASSERT(x) {}
#endif

#ifdef __cplusplus
#define __VARLIB_FUNC__ __PRETTY_FUNCTION__
#else
#define __VARLIB_FUNC__ __func__
#endif

#if defined __GNUC__  && __cplusplus < 201402L
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined __GNUC__  && __cplusplus >= 201402L
#define DEPRECATED(func) [[deprecated]] func
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

#endif
