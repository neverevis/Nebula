#pragma once

#ifdef _WIN32
#define PLATFORM_WINDOWS

#elif __linux__
#define PLATFORM_LINUX

#elif __APPLE__
#define PLATFORM_APPLE

#endif

// =-=-=-= PLATFORM SPECIFIC DEFINITIONS =-=-=-=-

#ifdef PLATFORM_WINDOWS

    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif

    #include <windows.h>

    struct Platform_Data
    {
        HWND    handle_window;
        HDC     handle_device_context;
        HGLRC   handle_gl_render_context;
    };
    
#endif

#ifdef PLATFORM_LINUX
#endif

#ifdef PLATFORM_APPLE
#endif