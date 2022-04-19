#ifndef LINUX_OPENGL_H
#define LINUX_OPENGL_H

#include <GL/gl.h>
#include <GL/glx.h>
#include <xcb/xproto.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

class LinuxOpenGL
{
private:
    GLXDrawable drawable;
    GLXWindow glXWindow;
    GLXContext openGLContext;

    int visualID;
    GLXFBConfig *fbConfigs;
    
public:
    LinuxOpenGL();
    ~LinuxOpenGL();
    
    bool InitLinuxOpenGL(int defaultScreen, Display *display, int *visualAttribs, struct xcb_connection_t* connection, struct xcb_screen_t* screen);
    void Draw();
    void MakeGLXContextCurrent(Display *display, struct xcb_connection_t* connection, xcb_window_t& window);

    GLXWindow& GetGlXWindow();
    GLXContext& GetGlXContext();
    GLXDrawable& GetGlXDrawable();
    int& GetVisualID();
    GLXFBConfig* GetFBConfig();

};

inline GLXWindow& LinuxOpenGL::GetGlXWindow(){
    return glXWindow;
}

inline GLXContext& LinuxOpenGL::GetGlXContext(){
    return openGLContext;
}

inline GLXDrawable& LinuxOpenGL::GetGlXDrawable(){
    return drawable;
}

inline int& LinuxOpenGL::GetVisualID(){
    return visualID;
}

inline GLXFBConfig* LinuxOpenGL::GetFBConfig(){
    return fbConfigs;
}

#endif