#include "OSXWindow.hpp"

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

void OSXWindow::SetWindowPosition(uint32_t x, uint32_t y)
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