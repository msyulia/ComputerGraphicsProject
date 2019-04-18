#include "Application.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    auto app = Application::Create();
    if (app != nullptr)
    {
        app->Run();
    }
    else
    {
        std::cout << "Couldn't create appliaction, not supported platform" 
                  << std::endl;
    }

    return 0;
}