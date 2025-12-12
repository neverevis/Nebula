#include <platform/definitions.h>
#ifdef PLATFORM_WINDOWS

#include <platform/gl_renderer.h>
#include <platform/window.h>
#include <wglext.h>
#include <utils/log.h>

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

    HGLRC legacy_context = wglCreateContext(hdc);

    if(!legacy_context)
    {
        MessageBoxA(nullptr, "Failed to create legacy OpenGL context", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to create legacy OpenGL context");
        return false;
    }

    if(!wglMakeCurrent(hdc, legacy_context))
    {
        MessageBoxA(nullptr, "Failed to make the OpenGL context current", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to make the OpenGL context current");
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

    if(!wglCreateContextAttribsARB)
    {
        MessageBoxA(nullptr, "Failed to load wglCreateContextAttribsARB function","Error", MB_ICONERROR | MB_OK);
        log_error("Failed to load wglCreateContextAttribsARB function from driver");
        return false;
    }

    int attribs[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC modern_context = wglCreateContextAttribsARB(hdc, nullptr, attribs);

    if(!modern_context)
    {
        MessageBoxA(nullptr, "Failed to load modern GL context", "Error", MB_ICONERROR | MB_OK);
        log_error("Failed to load modern OpenGL context");
        return false;
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(legacy_context);

    if(!wglMakeCurrent(hdc, modern_context))
    {
        MessageBoxA(nullptr, "Failed make modern GL context current", "Error", MB_ICONERROR | MB_OK);
        log_error("Failed make modern GL context current");
        return false;
    }

    return true;
}

PROC gl_load_proc(const char* fn)
{
    PROC proc = wglGetProcAddress(fn);

    return proc;
}

#endif