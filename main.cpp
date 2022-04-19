#include "include/window_linux.h"
#include "include/linux_opengl.h"

int main(){
    LinuxWindow *window = new LinuxWindow();
    LinuxOpenGL *opengl = new LinuxOpenGL();
    window->InitWindow();
    //window->InitLinuxOpenGL();
    //window->InitLinuxOpenGL(window->GetDefaultScreen(), window->GetDisplay(), window->GetVisualAttribs(), window->GetConnection(), window->GetScreen());
    opengl->InitLinuxOpenGL(window->GetDefaultScreen(), 
        window->GetDisplay(), window->GetVisualAttribs(), 
        window->GetConnection(), window->GetScreen());

    //window->CreateWindow(opengl->GetVisualID(), opengl->GetGlXWindow(), opengl->GetFBConfig(), opengl->GetGlXContext());
    opengl->MakeGLXContextCurrent(window->GetDisplay(), window->GetConnection(), window->GetXCBWindow());
    //LinuxOpenGL *linuxOpenGL = new LinuxOpenGL();
    //linuxOpenGL->InitLinuxOpenGL(window->GetDefaultScreen(), window->GetDisplay(), window->GetVisualAttribs(), window->GetConnection(), window->GetScreen());
    //window->Loop();

    bool running = true;
    xcb_atom_t wmDeleteWin;

    xcb_generic_event_t *event;
    xcb_client_message_event_t *cm;

    std::cout << "Starting loop method!\n";
    while(running){
        event = xcb_wait_for_event(window->GetConnection());
        std::cout << "Got event from window connection!\n";
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
                opengl->Draw();
                //Draw();
                std::cout << "Finished drawing! Swapping buffers...\n";
                glXSwapBuffers(window->GetDisplay(), opengl->GetGlXDrawable());
                std::cout << "Finished swapping buffers!\n";
                break;
            default:
                break;
        }
        free(event);
    }

    return 0;
}
