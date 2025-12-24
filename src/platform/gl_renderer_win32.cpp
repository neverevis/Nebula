#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/gl_renderer.h>
#include <platform/window.h>
#include <wglext.h>
#include <utils/log.h>

bool gl_load_context(NBL::Window& window)
{
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

    //setting legacy context
    {
        NBL::Window dummy(100,100,"",0);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;

        int pixelFormat = ChoosePixelFormat(dummy.data->handle_device_context, &pfd);

        if(!SetPixelFormat(dummy.data->handle_device_context, pixelFormat, &pfd))
        {
            MessageBoxA(nullptr, "Failed to set Pixel Format", "Error", MB_OK | MB_ICONERROR);
            log_error("Failed to set Pixel format");
            return false;
        }

        HGLRC legacy_context = wglCreateContext(dummy.data->handle_device_context);

        if(!legacy_context)
        {
            MessageBoxA(nullptr, "Failed to create legacy OpenGL context", "Error", MB_OK | MB_ICONERROR);
            log_error("Failed to create legacy OpenGL context");
            return false;
        }

        if(!wglMakeCurrent(dummy.data->handle_device_context, legacy_context))
        {
            MessageBoxA(nullptr, "Failed to make the OpenGL context current", "Error", MB_OK | MB_ICONERROR);
            log_error("Failed to make the OpenGL context current");
            return false;
        }

        //loading modern wgl functions
        wglCreateContextAttribsARB =    (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
        wglChoosePixelFormatARB =       (PFNWGLCHOOSEPIXELFORMATARBPROC)    wglGetProcAddress("wglChoosePixelFormatARB");

        if(!wglCreateContextAttribsARB || !wglChoosePixelFormatARB)
        {
            MessageBoxA(nullptr, "Failed to load wgl ARB functions","Error", MB_ICONERROR | MB_OK);
            log_error("Failed to load Failed to load wgl ARB functions from driver");
            return false;
        }

        //unbinding GL context, deleting GL context and deleting device context
        wglMakeCurrent(dummy.data->handle_device_context, nullptr);
        wglDeleteContext(legacy_context);
    }
    
    int pixelAttribs[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,

        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,

        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        
        WGL_SAMPLES_ARB, 4,
        0
    };

    UINT numPixelFormats;
    int pixelFormat;

    if(!wglChoosePixelFormatARB(window.data->handle_device_context, pixelAttribs, 0, 1, &pixelFormat, &numPixelFormats))
    {
        MessageBoxA(nullptr, "Failed to choose pixel format ARB","Error", MB_ICONERROR | MB_OK);
        log_error("Failed to choose pixel format ARB");
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd = {};
    DescribePixelFormat(window.data->handle_device_context, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if(!SetPixelFormat(window.data->handle_device_context, pixelFormat, &pfd))
    {
        MessageBoxA(nullptr, "Failed to set modern Pixel Format", "Error", MB_OK | MB_ICONERROR);
        log_error("Failed to set Pixel format");
        return false;
    }

    int attribs[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC modern_context = wglCreateContextAttribsARB(window.data->handle_device_context, nullptr, attribs);

    if(!modern_context)
    {
        MessageBoxA(nullptr, "Failed to load modern GL context", "Error", MB_ICONERROR | MB_OK);
        log_error("Failed to load modern OpenGL context");
        return false;
    }

    if(!wglMakeCurrent(window.data->handle_device_context, modern_context))
    {
        MessageBoxA(nullptr, "Failed make modern GL context current", "Error", MB_ICONERROR | MB_OK);
        log_error("Failed make modern GL context current");
        return false;
    }

    return true;
}

void* gl_load_proc(const char* fn)
{
    void* proc = (void*) wglGetProcAddress(fn);

    if(proc)
    {
        return proc;
    }

    HMODULE opengl32 = LoadLibraryA("opengl32.dll");

    if(!opengl32)
    {
        proc = nullptr;
    }

    proc = (void*) GetProcAddress(opengl32, fn);

    if(!proc)
    {
        log_error("failed to load function: %s", fn);
    }

    return proc;
}

#endif