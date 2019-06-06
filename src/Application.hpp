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
    std::shared_ptr<GlobalLightSources> lights;
    SDL_Event lastEvent;
    bool isTerminated;

public:
    OSXApp()
    {
        gameObjectRegistry = std::unique_ptr<GameObjectRegistry>(new GameObjectRegistry());
        lights = std::shared_ptr<GlobalLightSources>(new GlobalLightSources());
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

        clock_t timer;
        double deltaTime = 0.0;

        // Add 2 lights
        auto light1 = LightSource({256, 0, 100}, Color(0.5, 0.1, 0.9));
        auto light2 = LightSource({0, 256, 100}, {0.0, 1.0, 0.0});
        lights->Add(light2);
        lights->Add(light1);

        auto obj = std::shared_ptr<GameObject>(new GameObject());
        gameObjectRegistry->Add(obj);
        obj->Scale(100, 100, 100);
        obj->Translate(256, 256, 300);

        auto obj1 = std::shared_ptr<GameObject>(new GameObject());
        gameObjectRegistry->Add(obj1);
        obj1->Scale(100, 50, 100);
        obj1->Translate(100, 100, 10);

        auto cam = Camera();

        while (!isTerminated)
        {
            timer = std::clock();

            HandleEvents();
            //mainRenderer->Clear();
            mainRenderer->SetBackgroundColor(Color::White());

            auto frame = cam.GetNewFrame(*mainRenderer, *gameObjectRegistry, *lights);
            cam.DrawFrame(*mainRenderer, frame);

            //cam.DrawModelWithRandomPolygonColors(*mainRenderer, *(obj->mesh));
            //cam.DrawWireframe(*mainRenderer, *(obj->mesh));

            obj->Rotate(15 * deltaTime, 15 * deltaTime,0 );
            obj1->Rotate(30 * deltaTime, 30 * deltaTime, 30 * deltaTime );
            light1.Translate(0, 200 * std::sin(timer), 0);
            light2.Translate(200 * std::sin(timer), 0, 0);
            mainRenderer->Render();

            //SDL_Delay(10);
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
