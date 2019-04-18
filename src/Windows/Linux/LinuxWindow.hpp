#ifndef GK_LINUXWINDOW
#define GK_LINUXWINDOW

#include <SDL2/SDL.h>
#include "Window.hpp"

class LinuxWindow : public Window
{
private:
    SDL_Window *sdlWindow;
    std::string windowTitle;

public:
    LinuxWindow();
    ~LinuxWindow();

    uint32_t GetID();

    std::string GetTitle();
    void SetTitle(std::string title);

    WindowPosition GetPosition();
    void SetWindowPosition(uint32_t x, uint32_t y);

    WindowSize GetSize();
    void SetSize(uint32_t width, uint32_t height);
};

#endif