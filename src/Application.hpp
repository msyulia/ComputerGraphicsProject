#ifndef GK_APPLICATION
#define GK_APPLICATION

#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include "Eigen/Core"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "ObjectRegistry.hpp"

class Application
{
public:
    virtual ~Application() {}
    virtual void Run() = 0;
    static Application *Create();
};

class OSXApp : public Application
{
private:
    std::unique_ptr<GameObjectRegistry> gameObjectRegistry;
    SDL_Event lastEvent;
    bool isTerminated;

public:
    OSXApp()
    {
        gameObjectRegistry = std::unique_ptr<GameObjectRegistry>(new GameObjectRegistry());
        isTerminated = false;
    }
    ~OSXApp()
    {
        std::cout << "Quitting application" << std::endl;
        SDL_Quit();
    }
    void HandleEvents()
    {
        while (SDL_PollEvent(&lastEvent))
        {
            if (lastEvent.type == SDL_QUIT)
            {
                isTerminated = true;
            }
        }
    }
    void Run()
    {
        auto mainWindow = Window::Create("Projekt 2", 512, 512);
        auto mainRenderer = Renderer::Create(mainWindow);
        auto windowSize = mainWindow->GetSize();

        clock_t timer;
        double deltaTime = 0.0;

        auto obj = std::shared_ptr<GameObject>(new GameObject());
        gameObjectRegistry->Add(obj);
        obj->Scale(100, 100, 100);
        obj->Translate(256, 256, 1000);
        obj->Rotate(30, 30, 10);

        // auto obj1 = std::shared_ptr<GameObject>(new GameObject());
        // gameObjectRegistry->Add(obj1);
        // obj1->Translate(150, 175, 10);
        // obj1->Scale(100, 50, 100);
        // obj1->Rotate(30, 45, 60);

        auto cam = Camera();

        while (!isTerminated)
        {
            timer = std::clock();

            HandleEvents();
            mainRenderer->Clear();
            mainRenderer->SetBackgroundColor(WHITE);

            cam.DrawDepthBuffer(*mainRenderer, cam.GetDepthBuffer(*mainRenderer, *gameObjectRegistry));
            mainRenderer->SetDrawColor(BLACK);
            cam.Draw(*mainRenderer, *(obj->mesh));

            obj->Rotate(15*deltaTime,15*deltaTime,15*deltaTime);

            mainRenderer->Render();

            SDL_Delay(10);
            deltaTime = double(clock() - timer) / CLOCKS_PER_SEC;
        }

        delete mainRenderer;
        delete mainWindow;
    }
};

Application *Application::Create()
{
#if GK_OSX_BUILD
    return new OSXApp();
#endif
    return nullptr;
}

#endif
