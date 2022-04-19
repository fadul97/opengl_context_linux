#ifndef LINUX_WINDOW_H
#define LINUX_WINDOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <X11/Xlib-xcb.h>
#include <X11/Xlib.h>

#include <GL/glx.h>
#include <GL/gl.h>

#include "linux_opengl.h"

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);


class LinuxWindow{
    public:
        LinuxWindow();
        ~LinuxWindow();

        Display* GetDisplay();
        int GetDefaultScreen();
        int* GetVisualAttribs();
        xcb_connection_t* GetConnection();
        xcb_screen_t* GetScreen();
        xcb_window_t& GetXCBWindow();

        void Loop();
        bool InitWindow();
        bool CreateWindow(int& visualID, GLXWindow& glXWindow, GLXFBConfig *fbConfig, GLXContext& openGLContext);

        //bool InitLinuxOpenGL(int defaultScreen, Display *display, int *visualAttribs, struct xcb_connection_t *connection, struct xcb_screen_t *screen);
        //void Draw();
        //bool InitLinuxOpenGL();

        static int visualAttribs[];
    protected:
    private:
        xcb_connection_t *connection;
        xcb_window_t window;
        xcb_screen_t *screen;
        xcb_atom_t wmProtocols;
        xcb_atom_t wmDeleteWin;

        Display *display;
        int defaultScreen = 0;

        u_int16_t windowWidth;
        u_int16_t windowHeight;
        const char * windowTitle;
        bool running;

        xcb_colormap_t colormap;

        //LinuxOpenGL *linuxOpenGL;
};

inline Display* LinuxWindow::GetDisplay(){
    return display;
}

inline int LinuxWindow::GetDefaultScreen(){
    return defaultScreen;
}

inline int* LinuxWindow::GetVisualAttribs(){
    return visualAttribs;
}

inline xcb_connection_t* LinuxWindow::GetConnection(){
    return connection;
}

inline xcb_screen_t* LinuxWindow::GetScreen(){
    return screen;
}

inline xcb_window_t& LinuxWindow::GetXCBWindow(){
    return window;
}

#endif
