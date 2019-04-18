#ifndef GK_LINUXAPP
#define GK_LINUXAPP

#include "Application.hpp"

class LinuxApp : public Application
{
public:
    LinuxApp();
    ~LinuxApp();
    void Run();
};

#endif