#include "LinuxWindow.hpp"

uint32_t LinuxWindow::GetID()
{
    return SDL_GetWindowID(this->sdlWindow);
}

std::string LinuxWindow::GetTitle()
{
    if (windowTitle == "")
    {
        this->windowTitle = SDL_GetWindowTitle(this->sdlWindow);
    }
    return this->windowTitle;
}

void LinuxWindow::SetTitle(std::string title)
{
    SDL_SetWindowTitle(this->sdlWindow, title.c_str());
    this->windowTitle = title;
}