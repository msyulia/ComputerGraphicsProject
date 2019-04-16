#include "Application.hpp"
#include "LinuxApplication.hpp"

Application *Application::Create()
{
#if GK_LINUX_BUILD
    return new LinuxApp();
#endif
    return nullptr;
}