#include "OSXApplication.hpp"
#include "Window.hpp"
#include <iostream>

OSXApp::OSXApp()
{
}

OSXApp::~OSXApp()
{
}

void OSXApp::Run()
{
    this->mainWindow = Window::Create("Projekt 2");
    bool quit = false;

    while (!quit)
    {
        if (getchar() == 'x')
        {
            quit = true;
        }
    }
}
