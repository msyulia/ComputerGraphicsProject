#include "Window.hpp"
#include "OSXWindow.hpp"

Window *Window::Create(std::string title)
{
    #if GK_OSX_BUILD
        auto win = new OSXWindow(title); 
        win->renderer = Renderer::Create();
        return win;
    #endif
}