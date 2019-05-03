#include "OSXWindow.hpp"

OSXWindow::OSXWindow(std::string title)
{
    auto flags = SDL_WINDOW_INPUT_GRABBED;

    this->sdlWindow = SDL_CreateWindow(title.c_str(),
                      SDL_WINDOWPOS_CENTERED, 
                      SDL_WINDOWPOS_CENTERED,
                      800, 600,
                      flags);

}

OSXWindow::~OSXWindow() {}

uint32_t OSXWindow::GetID()
{
    return SDL_GetWindowID(this->sdlWindow);
}

std::string OSXWindow::GetTitle()
{
    if (windowTitle == "")
    {
        this->windowTitle = SDL_GetWindowTitle(this->sdlWindow);
    }
    return this->windowTitle;
}

void OSXWindow::SetTitle(std::string title)
{
    SDL_SetWindowTitle(this->sdlWindow, title.c_str());
    this->windowTitle = title;
}

WindowPosition OSXWindow::GetPosition()
{
    int *x = nullptr;
    int *y = nullptr;
    SDL_GetWindowPosition(this->sdlWindow, x, y);

    auto win_pos = WindowPosition(*x, *y);

    delete x, y; //Cleanup

    return win_pos;
}

void OSXWindow::SetPosition(uint32_t x, uint32_t y)
{
    SDL_SetWindowPosition(this->sdlWindow, x, y);
}

WindowSize OSXWindow::GetSize()
{
    int *width = nullptr;
    int *height = nullptr;
    SDL_GetWindowSize(this->sdlWindow, width, height);

    auto win_size = WindowSize(*width, *height);

    delete width, height;

    return win_size;
}

void OSXWindow::SetSize(uint32_t width, uint32_t height) 
{
    SDL_SetWindowSize(this->sdlWindow, width, height);
}