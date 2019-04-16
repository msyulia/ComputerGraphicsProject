#include "LinuxRenderer.hpp"

LinuxRenderer::LinuxRenderer()
{
}

LinuxRenderer::~LinuxRenderer()
{
}

void LinuxRenderer::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void LinuxRenderer::SetPixel(int32_t x, int32_t y)
{
    SDL_RenderDrawPoint(this->renderer, x, y);
}

void LinuxRenderer::Clear()
{
    SDL_RenderClear(this->renderer);
}

void LinuxRenderer::Render()
{
    SDL_RenderPresent(this->renderer);
}