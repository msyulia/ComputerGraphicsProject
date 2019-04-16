#include "Application.hpp"

int main(int argc, char **argv)
{
    auto app = Application::Create();
    app->Run();

    return 0;
}