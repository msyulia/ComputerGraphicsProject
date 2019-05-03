#include "Window.hpp"
#include "OSXWindow.hpp"

Window *Window::Create(std::string title)
{
    #if GK_OSX_BUILD
        return new OSXWindow(title);
    #endif
}