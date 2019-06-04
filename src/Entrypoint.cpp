#include "Application.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char* args[])
{
    srand(time(NULL)); // Initialize random number generator
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
    delete app;
    return 0;
}
