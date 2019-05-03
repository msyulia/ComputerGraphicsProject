#ifndef GK_OSXWINDOW
#define GK_OSXWINDOW

#include <SDL2/SDL.h>
#include "Window.hpp"

class OSXWindow : public Window
{
private:
    SDL_Window *sdlWindow;
    std::string windowTitle;

public:
    OSXWindow(std::string title);
    ~OSXWindow();

    uint32_t GetID();

    std::string GetTitle();
    void SetTitle(std::string title);

    WindowPosition GetPosition();
    void SetPosition(uint32_t x, uint32_t y);

    WindowSize GetSize();
    void SetSize(uint32_t width, uint32_t height);
};

#endif