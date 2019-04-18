#ifndef GK_OSXAPPLICATION
#define GK_OSXAPPLICATION

#include "Application.hpp"

class OSXApp : public Application
{
public:
    OSXApp();
    ~OSXApp();
    void Run();
};

#endif