#include "Application.hpp"
#include "LinuxApplication.hpp"
#include "OSXApplication.hpp"

Application *Application::Create()
{
#if GK_LINUX_BUILD
    return new LinuxApp();
#endif

#if GK_OSX_BUILD
    return new OSXApp();
#endif
    return nullptr;
}