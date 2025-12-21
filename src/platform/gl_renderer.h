#pragma once

#include <platform/window.h>
#include <glcorearb.h>

//OpenGL functions pointers
inline PFNGLDRAWARRAYSPROC                  glDrawArrays_ptr;
inline PFNGLCLEARCOLORPROC                  glClearColor_ptr;
inline PFNGLCLEARPROC                       glClear_ptr;
inline PFNGLCREATEBUFFERSPROC               glCreateBuffers_ptr;
inline PFNGLNAMEDBUFFERDATAPROC             glNamedBufferData_ptr;
inline PFNGLCREATEVERTEXARRAYSPROC          glCreateVertexArrays_ptr;
inline PFNGLVERTEXARRAYVERTEXBUFFERPROC     glVertexArrayVertexBuffer_ptr;
inline PFNGLENABLEVERTEXARRAYATTRIBPROC     glEnableVertexArrayAttrib_ptr;
inline PFNGLVERTEXARRAYATTRIBFORMATPROC     glVertexArrayAttribFormat_ptr;
inline PFNGLVERTEXARRAYATTRIBBINDINGPROC    glVertexArrayAttribBinding_ptr;
inline PFNGLCREATESHADERPROC                glCreateShader_ptr;
inline PFNGLSHADERSOURCEPROC                glShaderSource_ptr;
inline PFNGLCOMPILESHADERPROC               glCompileShader_ptr;
inline PFNGLGETSHADERIVPROC                 glGetShaderiv_ptr;
inline PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog_ptr;
inline PFNGLCREATEPROGRAMPROC               glCreateProgram_ptr;
inline PFNGLATTACHSHADERPROC                glAttachShader_ptr;
inline PFNGLLINKPROGRAMPROC                 glLinkProgram_ptr;
inline PFNGLGETPROGRAMIVPROC                glGetProgramiv_ptr;
inline PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog_ptr;
inline PFNGLDELETESHADERPROC                glDeleteShader_ptr;
inline PFNGLGETUNIFORMLOCATIONPROC          glGetUniformLocation_ptr;
inline PFNGLPROGRAMUNIFORM4FPROC            glProgramUniform4f_ptr;
inline PFNGLPROGRAMUNIFORMMATRIX4FVPROC     glProgramUniformMatrix4fv_ptr;
inline PFNGLUSEPROGRAMPROC                  glUseProgram_ptr;
inline PFNGLBINDVERTEXARRAYPROC             glBindVertexArray_ptr;

#define glDrawArrays                glDrawArrays_ptr
#define glClearColor                glClearColor_ptr
#define glClear                     glClear_ptr
#define glCreateBuffers             glCreateBuffers_ptr
#define glNamedBufferData           glNamedBufferData_ptr
#define glCreateVertexArrays        glCreateVertexArrays_ptr
#define glVertexArrayVertexBuffer   glVertexArrayVertexBuffer_ptr
#define glEnableVertexArrayAttrib   glEnableVertexArrayAttrib_ptr
#define glVertexArrayAttribFormat   glVertexArrayAttribFormat_ptr
#define glVertexArrayAttribBinding  glVertexArrayAttribBinding_ptr
#define glCreateShader              glCreateShader_ptr
#define glShaderSource              glShaderSource_ptr
#define glCompileShader             glCompileShader_ptr
#define glGetShaderiv               glGetShaderiv_ptr
#define glGetShaderInfoLog          glGetShaderInfoLog_ptr;
#define glCreateProgram             glCreateProgram_ptr
#define glAttachShader              glAttachShader_ptr
#define glLinkProgram               glLinkProgram_ptr
#define glGetProgramiv              glGetProgramiv_ptr
#define glGetProgramInfoLog         glGetProgramInfoLog_ptr
#define glDeleteShader              glDeleteShader_ptr
#define glGetUniformLocation        glGetUniformLocation_ptr
#define glProgramUniform4f          glProgramUniform4f_ptr
#define glProgramUniformMatrix4fv   glProgramUniformMatrix4fv_ptr
#define glUseProgram                glUseProgram_ptr
#define glBindVertexArray           glBindVertexArray_ptr

bool gl_load_context(NBL::Window& window);
void* gl_load_proc(const char* fn);

inline bool gl_load_functions()
{
    glDrawArrays_ptr =                  (PFNGLDRAWARRAYSPROC)                   gl_load_proc("glDrawArrays");
    glClearColor_ptr =                  (PFNGLCLEARCOLORPROC)                   gl_load_proc("glClearColor");
    glClear_ptr =                       (PFNGLCLEARPROC)                        gl_load_proc("glClear");
    glCreateBuffers_ptr =               (PFNGLCREATEBUFFERSPROC)                gl_load_proc("glCreateBuffers");
    glNamedBufferData_ptr =             (PFNGLNAMEDBUFFERDATAPROC)              gl_load_proc("glNamedBufferData");
    glCreateVertexArrays_ptr =          (PFNGLCREATEVERTEXARRAYSPROC)           gl_load_proc("glCreateVertexArrays");
    glVertexArrayVertexBuffer_ptr =     (PFNGLVERTEXARRAYVERTEXBUFFERPROC)      gl_load_proc("glVertexArrayVertexBuffer");
    glEnableVertexArrayAttrib_ptr =     (PFNGLENABLEVERTEXARRAYATTRIBPROC)      gl_load_proc("glEnableVertexArrayAttrib");
    glVertexArrayAttribFormat_ptr =     (PFNGLVERTEXARRAYATTRIBFORMATPROC)      gl_load_proc("glVertexArrayAttribFormat");
    glVertexArrayAttribBinding_ptr =    (PFNGLVERTEXARRAYATTRIBBINDINGPROC)     gl_load_proc("glVertexArrayAttribBinding");
    glCreateShader_ptr =                (PFNGLCREATESHADERPROC)                 gl_load_proc("glCreateShader");
    glShaderSource_ptr =                (PFNGLSHADERSOURCEPROC)                 gl_load_proc("glShaderSource");
    glCompileShader_ptr =               (PFNGLCOMPILESHADERPROC)                gl_load_proc("glCompileShader");
    glGetShaderiv_ptr =                 (PFNGLGETSHADERIVPROC)                  gl_load_proc("glGetShaderiv");
    glGetShaderInfoLog_ptr =            (PFNGLGETSHADERINFOLOGPROC)             gl_load_proc("glGetShaderInfoLog");
    glCreateProgram_ptr =               (PFNGLCREATEPROGRAMPROC)                gl_load_proc("glCreateProgram");
    glAttachShader_ptr =                (PFNGLATTACHSHADERPROC)                 gl_load_proc("glAttachShader");
    glLinkProgram_ptr =                 (PFNGLLINKPROGRAMPROC)                  gl_load_proc("glLinkProgram");
    glGetProgramiv_ptr =                (PFNGLGETPROGRAMIVPROC)                 gl_load_proc("glGetProgramiv");
    glGetProgramInfoLog_ptr =           (PFNGLGETPROGRAMINFOLOGPROC)            gl_load_proc("glGetProgramInfoLog");
    glDeleteShader_ptr =                (PFNGLDELETESHADERPROC)                 gl_load_proc("glDeleteShader");
    glGetUniformLocation_ptr =          (PFNGLGETUNIFORMLOCATIONPROC)           gl_load_proc("glGetUniformLocation");
    glProgramUniform4f_ptr =            (PFNGLPROGRAMUNIFORM4FPROC)             gl_load_proc("glProgramUniform4f");
    glProgramUniformMatrix4fv_ptr =     (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)      gl_load_proc("glProgramUniformMatrix4fv");
    glUseProgram_ptr =                  (PFNGLUSEPROGRAMPROC)                   gl_load_proc("glUseProgram");
    glBindVertexArray_ptr =             (PFNGLBINDVERTEXARRAYPROC)              gl_load_proc("glBindVertexArray");

    return true;
}





