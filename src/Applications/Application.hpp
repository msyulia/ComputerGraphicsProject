#ifndef GK_APPLICATION
#define GK_APPLICATION

#include "Window.hpp"

class Application
{
protected:
    Window* mainWindow;
public:
    virtual ~Application() {}
    virtual void Run() = 0;
    static Application *Create();
};

#endif
