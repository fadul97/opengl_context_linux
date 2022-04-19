#include "linux_opengl.h"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include "window_linux.h"


LinuxOpenGL::LinuxOpenGL()
{
    GLXDrawable drawable = 0;
    GLXWindow glXWindow = 0;
    GLXContext openGLContext = nullptr;
    int visualID = 0;
    GLXFBConfig *fbConfigs = nullptr;
}

LinuxOpenGL::~LinuxOpenGL()
{
    //glXDestroyWindow(display, glXWindow);
    //glXDestroyContext(display, openGLContext);
}

bool LinuxOpenGL::InitLinuxOpenGL(int defaultScreen, Display *display, int *visualAttribs, struct xcb_connection_t* connection, struct xcb_screen_t* screen)
{
    std::cout << "Initializing Context Setup\n";
    visualID = 0;

    // Query framebuffer configurations that match visual_attribs
    fbConfigs = 0;
    int numFBConfigs = 0;
    std::cout << "Setting defaultScreen...\n";
    //defaultScreen = DefaultScreen(display);
    std::cout << "Testing fbConfig and numFBConfigs...\n";
    fbConfigs = glXChooseFBConfig(display, defaultScreen, visualAttribs, &numFBConfigs);

    if(!fbConfigs || numFBConfigs == 0){
        std::cerr << "glXGetFBConfigs failed\n";
        return false;
    }

    std::cout << "Found " << numFBConfigs << " matching FB configs\n";

    // Select first framebuffer config and query visualID
    GLXFBConfig fbConfig = fbConfigs[0];
    glXGetFBConfigAttrib(display, fbConfig, GLX_VISUAL_ID, &visualID);

    std::cout << "Creating OpenGL Context\n";
    // Create OpenGL Context
    if(display == nullptr)
        std::cout << "Display eh nulo\n";
    else
        std::cout << "Display nao eh nulo\n";
    if(fbConfig == nullptr)
        std::cout << "fbConfig eh nulo\n";
    else
        std::cout << "fbConfig nao eh nulo\n";

    std::cout << "Testando openGLContext...\n";
    if(openGLContext == nullptr)
        std::cout << "openGLContext eh nulo\n";
    else
        std::cout << "openGLContext nao eh nulo\n";
    std::cout << "Teste finalizado.\n";

    openGLContext = glXCreateNewContext(display, fbConfig, GLX_RGBA_TYPE, 0, True);
    std::cout << "Created new context\n";
    if(!openGLContext){
        std::cerr << "glXCreateNewContext failed\n";
        return false;
    }

    
    std::cout << "Creating XIDs\n";
    // Create XIDs for colormap and window
    xcb_colormap_t colormap = xcb_generate_id(connection);
    xcb_window_t window = xcb_generate_id(connection);

    std::cout << "Creating Colormap\n";
    // Create colormap
    xcb_create_colormap(
        connection,
        XCB_COLORMAP_ALLOC_NONE,
        colormap,
        screen->root,
        visualID
    );

    std::cout << "Creating window\n";
    // Create window 
    uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
    uint32_t valuelist[] = { eventmask, colormap, 0 };
    uint32_t valuemask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

    xcb_create_window(
        connection,
        XCB_COPY_FROM_PARENT,
        window,
        screen->root,
        0, 0,
        150, 150,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        visualID,
        valuemask,
        valuelist
    );

    // NOTE: window must be mapped before glXMakeContextCurrent
    xcb_map_window(connection, window);

    // Create GLX Window 

    std::cout << "Creating GKX window\n";
    glXWindow =
        glXCreateWindow(
            display,
            fbConfig,
            window,
            0
            );

    if(!window)
    {
        xcb_destroy_window(connection, window);
        glXDestroyContext(display, openGLContext);

        std::cerr << "glXDestroyContext failed\n";
        return false;
    }
    



    return true;
}

void LinuxOpenGL::MakeGLXContextCurrent(Display *display, struct xcb_connection_t* connection, xcb_window_t& window){
    drawable = glXWindow; // Talvez colocar de volta no metodo Init(?) ------------------------------------------------------

    if(!glXMakeContextCurrent(display, drawable, drawable, openGLContext)){
        xcb_destroy_window(connection, window);
        glXDestroyContext(display, openGLContext);

        std::cerr << "glXMakeContextCurrent failed\n";
    }
}

void LinuxOpenGL::Draw(){
    glClearColor(0.7, 0.5, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}