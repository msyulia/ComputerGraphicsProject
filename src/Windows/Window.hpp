#ifndef GK_WINDOW
#define GK_WINDOW

#include <string>

struct WindowSize
{
    WindowSize(uint32_t width, 
               uint32_t height) : Width(width), 
                                  Height(height) {}
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

    virtual uint32_t GetID() = 0;

    virtual std::string GetTitle() = 0;
    virtual void SetTitle(std::string title) = 0;

    virtual WindowPosition GetPosition() = 0;
    virtual void SetWindowPosition(uint32_t x, uint32_t y) = 0;

    virtual WindowSize GetSize() = 0;
    virtual void SetSize(uint32_t width, uint32_t height) = 0;
};

#endif