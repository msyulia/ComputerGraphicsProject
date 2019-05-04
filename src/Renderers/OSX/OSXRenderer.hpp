#ifndef GK_OSXRENDERER
#define GK_OSXRENDERER

#include <SDL2/SDL.h>
#include "Renderer.hpp"

class OSXRenderer : public Renderer
{
private:
    SDL_Renderer *renderer;

public:
    OSXRenderer();
    ~OSXRenderer();

    void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void SetPixel(int32_t x, int32_t y);

    void Clear();
    void Render();
};

#endif