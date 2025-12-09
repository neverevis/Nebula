#include <platform/definitions.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>
#include <utils/log.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

bool gl_load_context(Window& window)
{
    HDC hdc = GetDC((HWND) window.handle);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);

    if(!SetPixelFormat(hdc, pixelFormat, &pfd))
    {
        MessageBoxA(nullptr, "Failed to set Pixel Format", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to set Pixel format");
        return false;
    }

    HGLRC hglrc = wglCreateContext(hdc);

    if(!hglrc)
    {
        MessageBoxA(nullptr, "Failed to create legacy OpenGL context", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to create legacy OpenGL context");
        return false;
    }

    if(!wglMakeCurrent(hdc, hglrc))
    {
        MessageBoxA(nullptr, "Failed to make the OpenGL context current", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to make the OpenGL context current");
        return false;
    }


    return true;
}

#endif