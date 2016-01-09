#pragma once

#ifdef _WIN32
#define PLATFORM_WINDOWS
	#ifdef _WIN64

	#endif
#elif __APPLE__

#elif __linux__

#elif __unix__

#elif defined(_POSIX_VERSION)

#else
#error "Unknown platform"
#endif

#if defined(_MSC_VER)
#define COMPILER_MSVC
#endif

// ALIGNED_ALLOC
// alignment must be a power of two
#if defined(COMPILER_MSVC)
#define ALIGNED_MALLOC(size, alignment) _aligned_malloc(size, alignment)
#define MALLOC(size) _aligned_malloc(size, 1)
#define FREE(ptr) _aligned_free(ptr)
#else
#define ALIGNED_MALLOC(size, alignment) aligned_alloc(alignment, size)
#define MALLOC(size) std::malloc(size)
#define FREE(ptr) std::free(ptr)
#endif