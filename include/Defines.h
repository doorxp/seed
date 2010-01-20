/*! \file Defines.h
	\author	Danny Angelo Carminati Grein
	\brief Defines
*/

#ifndef __SEED_DEFINES_H__
#define __SEED_DEFINES_H__

#include "Config.h"

/*
Compiler specific pragmas here
*/
#if defined(_MSC_VER)
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4201) // anonymous union
#pragma warning(disable:4530)
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#endif
#if defined(__MWERKS__)
#pragma warning off (10342)
#endif // __MWERKS__

#if defined(_WII_)
	#include "platform/wii/WiiDefines.h"
#else
	#if defined(_SDL_)
		#include "platform/sdl/SdlDefines.h"
	#else
		#if defined(_IPHONE_)
			#include "platform/iphone/IphDefines.h"
		#else
			#if defined(_QT_)
				#include "platform/qt/QtDefines.h"
			#endif // _QT_
		#endif // IPHONE
	#endif // SDL
#endif // WII

#define STRING_LENGTH					LIB_STRLEN
#define SIZE_T							LIB_SIZE_T

#define UNUSED(var)						(void)var;

#define RAND							LIB_RAND

#undef MEMSET4
// Memory and Strings
#define MEMSET							LIB_MEMSET
#define MEMSET4							LIB_MEMSET4
#define MEMCOPY							LIB_MEMCOPY
#define STRLEN							LIB_STRLEN
#define STRCMP							LIB_STRCMP
#define STRLCPY							LIB_STRLCPY
#define STRLCAT							LIB_STRLCAT
#define STRCASECMP						LIB_STRCASECMP
#define STRDUP							LIB_STRDUP

// Wide String funcs
#define WSTRLEN							LIB_WSTRLEN
#define WVSNPRINTF						LIB_WVSNPRINTF

// Math
#define FAST_DIV						LIB_FAST_DIV
#define FAST_MOD						LIB_FAST_MOD
#define FAST_SQRT						LIB_FAST_SQRT

// Display Object
#define PIXEL_A_MASK					LIB_PIXEL_A_MASK
#define PIXEL_A_SHIFT					LIB_PIXEL_A_SHIFT
#define PIXEL_R_MASK					LIB_PIXEL_R_MASK
#define PIXEL_R_SHIFT					LIB_PIXEL_R_SHIFT
#define PIXEL_G_MASK					LIB_PIXEL_G_MASK
#define PIXEL_G_SHIFT					LIB_PIXEL_G_SHIFT
#define PIXEL_B_MASK					LIB_PIXEL_B_MASK
#define PIXEL_B_SHIFT					LIB_PIXEL_B_SHIFT
#define PIXEL_DEFAULT_KEYCOLOR			LIB_PIXEL_DEFAULT_KEYCOLOR
#define	PIXEL_COMPONENT					LIB_PIXEL_COMPONENT
#define	PIXEL_COLOR						(PIXEL)LIB_PIXEL_COLOR
#define PIXEL_ALPHA_MAX_VALUE			LIB_PIXEL_ALPHA_MAX_VALUE

#define PIXEL_GET_A(px)			(static_cast<u8>(((px & PIXEL_A_MASK) >> PIXEL_A_SHIFT)))
#define PIXEL_GET_R(px)			(static_cast<u8>(((px & PIXEL_R_MASK) >> PIXEL_R_SHIFT)))
#define PIXEL_GET_G(px)			(static_cast<u8>(((px & PIXEL_G_MASK) >> PIXEL_G_SHIFT)))
#define PIXEL_GET_B(px)			(static_cast<u8>(((px & PIXEL_B_MASK) >> PIXEL_B_SHIFT)))
#define PIXEL_SET_A(px, a)		(((px) & (~LIB_PIXEL_A_MASK)) + (static_cast<u32>(a)<<PIXEL_A_SHIFT))
#define PIXEL_SET_R(px, r)		(((px) & (~LIB_PIXEL_R_MASK)) + (static_cast<u32>(r)<<PIXEL_R_SHIFT))
#define PIXEL_SET_G(px, g)		(((px) & (~LIB_PIXEL_G_MASK)) + (static_cast<u32>(g)<<PIXEL_G_SHIFT))
#define PIXEL_SET_B(px, b)		(((px) & (~LIB_PIXEL_B_MASK)) + (static_cast<u32>(b)<<PIXEL_B_SHIFT))


// Debugging
#ifdef DEBUG

	#ifndef ASSERT
	#define ASSERT							LIB_ASSERT
	#endif // ASSERT

	#ifndef ASSERT_MSG
	#define ASSERT_MSG						LIB_ASSERT_MSG
	#endif // ASSERT_MSG

	#ifndef ASSERT_NULL
	#define ASSERT_NULL						LIB_ASSERT_NULL
	#endif // ASSERT_NULL

	#ifndef SECURITY_CHECK
	#define SECURITY_CHECK					LIB_ASSERT_MSG
	#endif // SECURITY_CHECK

#else

	#if defined(__GNUC__) || defined(_WII_)
		#ifndef ASSERT
		#define ASSERT(...)
		#endif // ASSERT

		#ifndef ASSERT_MSG
		#define ASSERT_MSG(...)
		#endif // ASSERT_MSG

		#ifndef ASSERT_NULL
		#define ASSERT_NULL(...)
		#endif // ASSERT_NULL
	#else
		#ifndef ASSERT
		#define ASSERT
		#endif // ASSERT

		#ifndef ASSERT_MSG
		#define ASSERT_MSG
		#endif // ASSERT_MSG

		#ifndef ASSERT_NULL
		#define ASSERT_NULL
		#endif // ASSERT_NULL
	#endif // __GNUC__

	#ifndef SECURITY_CHECK
	#define SECURITY_CHECK(func, msg)		func
	#endif // SECURITY_CHECK

#endif // DEBUG

#define SEED_INVALID_ID					0xFFFFFFFF

#define CLAMP(val,min,max) 				((val) = (((val) < (min)) ? (min) : ((val) > (max)) ? (max) : (val)))
#define ROUND_UP(value, alignment)		(((u32)(value) + (alignment-1)) & ~(alignment-1))
#define ROUND_DOWN(value, alignment)	((u32)(value) & ~(alignment-1))
#define DISPLAY_MEM()					pMemoryManager->Info()

#define SEED_ABSTRACT_METHOD(m)			Log(SEED_TAG "WARNING: Calling an 'abstract' method " # m);

#define SEED_DISABLE_COPY(Class)		Class(const Class &); \
										Class &operator=(const Class &)

#define SEED_FORWARD_DECLARATION(Class) namespace Seed { class Class; }


#define SEED_COMPILE_TIME_ASSERT(name, x)	typedef int __seed_compile_assert_ ## name[(x) * 2 - 1]

SEED_COMPILE_TIME_ASSERT(u8,  sizeof(u8) == 1);
SEED_COMPILE_TIME_ASSERT(s8,  sizeof(s8) == 1);
SEED_COMPILE_TIME_ASSERT(u16, sizeof(u16) == 2);
SEED_COMPILE_TIME_ASSERT(s16, sizeof(s16) == 2);
SEED_COMPILE_TIME_ASSERT(u32, sizeof(u32) == 4);
SEED_COMPILE_TIME_ASSERT(s32, sizeof(s32) == 4);
SEED_COMPILE_TIME_ASSERT(u64, sizeof(u64) == 8);
SEED_COMPILE_TIME_ASSERT(s64, sizeof(s64) == 8);

typedef enum { SEED_ENUM_ASSERT_VALUE } SEED_ENUM_ASSERT;
SEED_COMPILE_TIME_ASSERT(enum, sizeof(SEED_ENUM_ASSERT) == sizeof(u32));

typedef u16* WideString;
typedef u16  WideChar;

#ifdef DEBUG
#define DEBUG_RECT(x, y, w, h, c) static_cast<Renderer2D *>(Seed::Private::pRenderer)->DrawRect(x, y, w, h, c);
#else
#define DEBUG_RECT(x, y, w, h, c)
#endif


#endif // __SEED_DEFINES_H__
