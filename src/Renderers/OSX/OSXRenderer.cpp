#include "OSXRenderer.hpp"

OSXRenderer::OSXRenderer()
{
}

OSXRenderer::~OSXRenderer()
{
}

void OSXRenderer::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void OSXRenderer::SetPixel(int32_t x, int32_t y)
{
    SDL_RenderDrawPoint(this->renderer, x, y);
}

void OSXRenderer::Clear()
{
    SDL_RenderClear(this->renderer);
}

void OSXRenderer::Render()
{
    SDL_RenderPresent(this->renderer);
}