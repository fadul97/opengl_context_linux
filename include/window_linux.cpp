#include "window_linux.h"
#include <GL/gl.h>
#include <GL/glx.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>

#include <cstring>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>

#include <xcb/xcb.h>
#include <xcb/xproto.h>

int LinuxWindow::visualAttribs[] =
{
    GLX_X_RENDERABLE, True,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    GLX_DOUBLEBUFFER, True,
    //GLX_SAMPLE_BUFFERS  , 1,
    //GLX_SAMPLES         , 4,
    None
};


LinuxWindow::LinuxWindow(){
    xcb_connection_t *connection = nullptr;
    xcb_window_t window = 0;
    xcb_screen_t *screen = nullptr;
    xcb_atom_t wmProtocols = 0;
    xcb_atom_t wmDeleteWin = 0;

    Display *display = nullptr;
    int defaultScreen = 0;

    u_int16_t windowWidth = 800;
    u_int16_t windowHeight = 600;
    const char *windowTitle = nullptr;
    bool running = false;

    xcb_colormap_t colormap = 0;
    //GLXDrawable drawable = 0;
    //GLXWindow glXWindow = 0;
    //GLXContext openGLContext = nullptr;
    //LinuxOpenGL *linuxOpenGL = nullptr;
    /*
    int screep = 0;
    connection = xcb_connect(NULL, &screep);

    if(xcb_connection_has_error(connection))
        printf("Failed to connect to X server using XCB");

    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(connection));

    for(int s = screep; s > 0; s--)
        xcb_screen_next(&iter);

    screen = iter.data;
    window = xcb_generate_id(connection);

    uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t valueList[] = {screen->black_pixel, 0};

    windowWidth = 800;
    windowHeight = 600;
    windowTitle = "Linx Window";

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window,
            screen->root, 0, 0, windowWidth, windowHeight, 0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
            eventMask, valueList);

    xcb_change_property(connection, XCB_PROP_MODE_REPLACE,
            window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
            std::strlen(windowTitle), windowTitle);

    xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
            connection, 0, strlen("WM_DELETE_WINDOW"),
            "WM_DELETE_WINDOW");

    xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(
            connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");

    xcb_intern_atom_reply_t *wmDeleteReply = xcb_intern_atom_reply(
            connection, wmDeleteCookie, NULL);
    xcb_intern_atom_reply_t *wmProtocolsReply = xcb_intern_atom_reply(
            connection, wmProtocolsCookie, NULL);

    wmDeleteWin = wmDeleteReply->atom;
    wmProtocols = wmProtocolsReply->atom;

    xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom);

    xcb_map_window(connection, window);
    xcb_flush(connection);
    */
    
    /* Open Xlib Display */
    //display = XOpenDisplay(0);
    //if(!display)
    //{
    //    std::cout << "Can't open display\n";
    //}
//
    //std::cout << "Got Display!\n";
    //defaultScreen = DefaultScreen(display);
//
    ///* Get the XCB connection from the display */
    //connection = XGetXCBConnection(display);
    //if(!connection)
    //{
    //    XCloseDisplay(display);
    //    std::cout << "Can't get xcb connection from display\n";
    //}
//
    ///* Acquire event queue ownership */
    //XSetEventQueueOwner(display, XCBOwnsEventQueue);
//
    ///* Find XCB screen */
    //screen = 0;
    //xcb_screen_iterator_t screenIter =
    //    xcb_setup_roots_iterator(xcb_get_setup(connection));
    //for(int screen_num = defaultScreen;
    //    screenIter.rem && screen_num > 0;
    //    --screen_num, xcb_screen_next(&screenIter));
    //screen = screenIter.data;
//
    ////std::cout << "Initializing LinuxOpenGL method...\n";
    ////linuxOpenGL->InitLinuxOpenGL(defaultScreen, display, visualAttribs, connection, screen);
    ////std::cout << "Setup finished\n";
    //std::cout << "Initializing opengl with no parameters...\n";
    ////InitLinuxOpenGL(defaultScreen, display, visualAttribs, connection, screen);
    //InitLinuxOpenGL();
    //std::cout << "Setup finished\n";
}

LinuxWindow::~LinuxWindow(){
    //glXDestroyWindow(display, linuxOpenGL->GetGlXWindow());
    //glXDestroyWindow(display, glXWindow);
    xcb_destroy_window(connection, window);
    //glXDestroyContext(display, linuxOpenGL->GetGlXContext());
    //glXDestroyContext(display, openGLContext);
}

bool LinuxWindow::InitWindow(){
    /* Open Xlib Display */
    display = XOpenDisplay(0);
    if(!display)
    {
        std::cout << "Can't open display\n";
        return false;
    }

    std::cout << "Got Display!\n";
    defaultScreen = DefaultScreen(display);

    /* Get the XCB connection from the display */
    connection = XGetXCBConnection(display);
    if(!connection)
    {
        XCloseDisplay(display);
        std::cout << "Can't get xcb connection from display\n";
        return false;
    }

    /* Acquire event queue ownership */
    XSetEventQueueOwner(display, XCBOwnsEventQueue);

    /* Find XCB screen */
    screen = 0;
    xcb_screen_iterator_t screenIter =
        xcb_setup_roots_iterator(xcb_get_setup(connection));
    for(int screen_num = defaultScreen;
        screenIter.rem && screen_num > 0;
        --screen_num, xcb_screen_next(&screenIter));
    screen = screenIter.data;

    //std::cout << "Initializing LinuxOpenGL method...\n";
    //linuxOpenGL->InitLinuxOpenGL(defaultScreen, display, visualAttribs, connection, screen);
    //std::cout << "Setup finished\n";
    //std::cout << "Initializing opengl with no parameters...\n";
    //InitLinuxOpenGL(defaultScreen, display, visualAttribs, connection, screen);
    //InitLinuxOpenGL();
    //std::cout << "Setup finished\n";
    
    return true;
}

bool LinuxWindow::CreateWindow(int& visualID, GLXWindow& glXWindow, GLXFBConfig *fbConfig, GLXContext& openGLContext){
    std::cout << "Creating XIDs\n";
    // Create XIDs for colormap and window
    colormap = xcb_generate_id(connection);
    window = xcb_generate_id(connection);

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
    /* Create window */
    uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
    uint32_t valuelist[] = { eventmask, colormap, 0 };
    uint32_t valuemask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

    xcb_create_window(
        connection,
        XCB_COPY_FROM_PARENT,
        window,
        screen->root,
        0, 0,
        windowWidth, windowHeight,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        visualID,
        valuemask,
        valuelist
    );

    // NOTE: window must be mapped before glXMakeContextCurrent
    xcb_map_window(connection, window);

    /* Create GLX Window */

    std::cout << "Creating GLX window\n";
    glXWindow =
        glXCreateWindow(
            display,
            GLXFBConfig(*fbConfig),
            window,
            0
            );

    std::cout << "Aqui\n";
    if(!window)
    {
        xcb_destroy_window(connection, window);
        glXDestroyContext(display, openGLContext);

        std::cerr << "glXDestroyContext failed\n";
        return false;
    }

    std::cout << "Window created!\n";
    return true;
}

void LinuxWindow::Loop(){

    //std::cout << "Initializing LinuxOpenGL method...\n";
    //linuxOpenGL->InitLinuxOpenGL(defaultScreen, display, visualAttribs, connection, screen);
    //std::cout << "Setup finished\n";

    running = true;

    xcb_generic_event_t *event;
    xcb_client_message_event_t *cm;

    std::cout << "Starting loop method!\n";
    while(running){
        event = xcb_wait_for_event(connection);
        switch (event->response_type & ~0x80) {
            case XCB_KEY_PRESS:{
                xcb_key_press_event_t *keyEvent = (xcb_key_press_event_t *) event;
                switch (keyEvent->detail) {
                    case 0x19:
                        std::cout << "Pressing W" << std::endl;
                        break;
                   }
           }
            case XCB_CLIENT_MESSAGE:{
                cm = (xcb_client_message_event_t *) event;
                if(cm->data.data32[0] == wmDeleteWin)
                    running = false;

                break;
                                    }
            case XCB_EXPOSE:
                std::cout << "Starting to draw!\n";
                //linuxOpenGL->Draw();
                //Draw();
                std::cout << "Finished drawing! Swapping buffers...\n";
                //glXSwapBuffers(display, drawable); // drawable from OpenGL
                std::cout << "Finished swapping buffers!\n";
                break;
            default:
                break;
        }
        free(event);
    }
}






/*
// -------------------------------------------------------------
bool LinuxWindow::InitLinuxOpenGL(int defaultScreen, Display *display, int *visualAttribs, struct xcb_connection_t* connection, struct xcb_screen_t* screen)
{
    std::cout << "Initializing Context Setup\n";
    int visualID = 0;

    // Query framebuffer configurations that match visual_attribs
    GLXFBConfig *fbConfigs = 0;
    int numFBConfigs = 0;
    std::cout << "Setting defaultScreen...\n";
    defaultScreen = DefaultScreen(display);
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
    /* Create window */
    /*
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

    /* Create GLX Window */
    /*
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

    drawable = glXWindow;

    // Make OpenGL context current
    if(!glXMakeContextCurrent(display, drawable, drawable, openGLContext)){
        xcb_destroy_window(connection, window);
        glXDestroyContext(display, openGLContext);

        std::cerr << "glXMakeContextCurrent failed\n";
        return false;
    }

    return true;
}

/*
void LinuxWindow::Draw(){
    glClearColor(0.8, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool LinuxWindow::InitLinuxOpenGL()
{
    std::cout << "Initializing Context Setup\n";
    int visualID = 0;

    // Query framebuffer configurations that match visual_attribs
    GLXFBConfig *fbConfigs = 0;
    int numFBConfigs = 0;
    std::cout << "Setting defaultScreen...\n";

    if(display == nullptr)
        std::cout << "Display eh nulo\n";
    else
        std::cout << "Display nao eh nulo\n";
    
    defaultScreen = DefaultScreen(display);
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
    /* Create window */
    /*
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

    /* Create GLX Window */
    /*
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

    drawable = glXWindow;

    // Make OpenGL context current
    if(!glXMakeContextCurrent(display, drawable, drawable, openGLContext)){
        xcb_destroy_window(connection, window);
        glXDestroyContext(display, openGLContext);

        std::cerr << "glXMakeContextCurrent failed\n";
        return false;
    }

    return true;
}
*/