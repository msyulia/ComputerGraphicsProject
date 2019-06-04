#ifndef GK_WINDOW
#define GK_WINDOW

#include <string>
#include <SDL2/SDL.h>
#include <iostream>

struct WindowSize
{
    WindowSize() {}
    WindowSize(uint32_t width,
               uint32_t height)
    {
        Width = width;
        Height = height;
    }
    uint32_t Width, Height;
};

struct WindowPosition
{
    WindowPosition(uint32_t x,
                   uint32_t y) : X(x),
                                 Y(y) {}
    uint32_t X, Y;
};

class Window
{
public:
    virtual ~Window() {}

    static Window *Create(std::string title, unsigned int width, unsigned int height);

    virtual uint32_t GetID() = 0;

    virtual std::string GetTitle() = 0;
    virtual void SetTitle(std::string title) = 0;

    virtual WindowPosition GetPosition() = 0;
    virtual void SetPosition(uint32_t x, uint32_t y) = 0;

    virtual WindowSize GetSize() = 0;
    virtual void SetSize(uint32_t width, uint32_t height) = 0;
};

class OSXWindow : public Window
{
private:
    std::string windowTitle;

public:
    SDL_Window *sdlWindow;

    // uint32_t Width = 800;
    // uint32_t Height = 600;
    WindowSize size;

    OSXWindow(std::string title, unsigned int width, unsigned int height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Init error: " << SDL_GetError() << std::endl;
            return;
        }
        std::cout << "Initialized properly!" << std::endl;
        size = WindowSize(width, height);
        this->sdlWindow = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           size.Width, size.Height,
                                           SDL_WINDOW_SHOWN);
        if (this->sdlWindow == nullptr)
        {
            std::cout << "Couldn't create window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }
        std::cout << "Created window!" << std::endl;
    }
    ~OSXWindow()
    {
        std::cout << "Window destroyed!" << std::endl;
        SDL_DestroyWindow(sdlWindow);
    }

    uint32_t GetID()
    {
        return SDL_GetWindowID(this->sdlWindow);
    }

    std::string GetTitle()
    {
        if (windowTitle == "")
        {
            this->windowTitle = SDL_GetWindowTitle(this->sdlWindow);
        }
        return this->windowTitle;
    }
    void SetTitle(std::string title)
    {
        SDL_SetWindowTitle(this->sdlWindow, title.c_str());
        this->windowTitle = title;
    }

    WindowPosition GetPosition()
    {
        int *x = nullptr;
        int *y = nullptr;
        SDL_GetWindowPosition(this->sdlWindow, x, y);

        auto win_pos = WindowPosition(*x, *y);

        delete x, y; //Cleanup

        return win_pos;
    }
    void SetPosition(uint32_t x, uint32_t y)
    {
        SDL_SetWindowPosition(this->sdlWindow, x, y);
    }

    WindowSize GetSize()
    {
        return size;
    }

    void SetSize(uint32_t width, uint32_t height)
    {
        SDL_SetWindowSize(this->sdlWindow, width, height);
    }
};

Window *Window::Create(std::string title, unsigned int width, unsigned int height)
{
#if GK_OSX_BUILD
    auto win = new OSXWindow(title, width, height);
    return win;
#endif
}

#endif