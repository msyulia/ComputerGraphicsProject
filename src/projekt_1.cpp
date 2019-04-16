// #include <SDL2/SDL.h>
// #include <iostream>
// #include <cmath>

// #define COLOR_WHITE 255, 255, 255, 255
// #define COLOR_BLACK 0, 0, 0, 255
// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGHT 600

// class Renderer;

// class LineDrawer
// {
// public:
//     LineDrawer() {}
//     virtual ~LineDrawer() {}
//     virtual void DrawLine(Renderer *renderer,
//                           int32_t x0,
//                           int32_t y0,
//                           int32_t x1,
//                           int32_t y1) = 0;
// };

// class Renderer
// {
// private:
//     SDL_Renderer *renderer;

// protected:
//     LineDrawer *lineDrawer;
//     LineDrawer *horizontalLineDrawer;
//     LineDrawer *verticalLineDrawer;

// public:
//     Renderer(SDL_Renderer *renderer);
//     ~Renderer();

//     LineDrawer *GetLineDrawer();
//     void SetLineDrawer(LineDrawer *lineDrawer);

//     LineDrawer *GetHorizontalLineDrawer();
//     void SetHorizontalLineDrawer(LineDrawer *lineDrawer);

//     LineDrawer *GetVerticalLineDrawer();
//     void SetVerticalLineDrawer(LineDrawer *lineDrawer);

//     void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
//     void SetPixel(int32_t x, int32_t y);
//     void Clear();
//     void Render();
//     void DrawLine(int32_t x0,
//                   int32_t y0,
//                   int32_t x1,
//                   int32_t y1);
// };

// class IncrementalDrawer : public LineDrawer
// {
// public:
//     void DrawLine(Renderer *renderer,
//                   int32_t x0,
//                   int32_t y0,
//                   int32_t x1,
//                   int32_t y1) override
//     {
//         int32_t deltaX = x1 - x0;
//         int32_t deltaY = y1 - y0;
//         float_t slope = (float_t)deltaY / deltaX;

//         if (std::abs(slope) > 1)
//         {
//             slope = 1.f / slope;

//             if (y0 > y1)
//             {
//                 int32_t swap = y0;
//                 y0 = y1;
//                 y1 = swap;
//             }

//             float_t currentX = std::min(x0, x1);
//             for (int32_t currentY = y0; currentY <= y1; currentY++)
//             {
//                 renderer->SetPixel((int32_t)std::round(currentX), currentY);
//                 currentX += slope;
//             }
//         }
//         else
//         {
//             float_t currentY = y0;
//             for (int32_t currentX = x0; currentX <= x1; currentX++)
//             {
//                 renderer->SetPixel(currentX, (int32_t)std::round(currentY));
//                 currentY += slope;
//             }
//         }
//     }
// };

// class EFLALineDrawer : public LineDrawer
// {
// public:
//     void DrawLine(Renderer *renderer,
//                   int32_t x0,
//                   int32_t y0,
//                   int32_t x1,
//                   int32_t y1) override
//     {
//         bool yLonger = false;
//         int shortLen = y1 - y0;
//         int longLen = x1 - x0;
//         if (abs(shortLen) > abs(longLen))
//         {
//             int swap = shortLen;
//             shortLen = longLen;
//             longLen = swap;
//             yLonger = true;
//         }
//         int decInc;
//         if (longLen == 0)
//             decInc = 0;
//         else
//             decInc = (shortLen << 16) / longLen;

//         if (yLonger)
//         {
//             if (longLen > 0)
//             {
//                 longLen += y0;
//                 for (int j = 0x8000 + (x0 << 16); y0 <= longLen; ++y0)
//                 {
//                     renderer->SetPixel(j >> 16, y0);
//                     j += decInc;
//                 }
//                 return;
//             }
//             longLen += y0;
//             for (int j = 0x8000 + (x0 << 16); y0 >= longLen; --y0)
//             {
//                 renderer->SetPixel(j >> 16, y0);
//                 j -= decInc;
//             }
//             return;
//         }

//         if (longLen > 0)
//         {
//             longLen += x0;
//             for (int j = 0x8000 + (y0 << 16); x0 <= longLen; ++x0)
//             {
//                 renderer->SetPixel(x0, j >> 16);
//                 j += decInc;
//             }
//             return;
//         }
//         longLen += x0;
//         for (int j = 0x8000 + (y0 << 16); x0 >= longLen; --x0)
//         {
//             renderer->SetPixel(x0, j >> 16);
//             j -= decInc;
//         }
//     }
// };

// class HorizontalLineDrawer : public LineDrawer
// {
// public:
//     void DrawLine(Renderer *renderer,
//                   int32_t x0,
//                   int32_t y0,
//                   int32_t x1,
//                   int32_t y1) override
//     {
//         for (size_t i = x0; i <= x1; i++)
//         {
//             renderer->SetPixel(i, y0);
//         }
//     }
// };

// class VerticalLineDrawer : public LineDrawer
// {
// public:
//     void DrawLine(Renderer *renderer,
//                   int32_t x0,
//                   int32_t y0,
//                   int32_t x1,
//                   int32_t y1) override
//     {
//         for (size_t i = y0; i <= y1; i++)
//         {
//             renderer->SetPixel(x0, i);
//         }
//     }
// };

// Renderer::Renderer(SDL_Renderer *renderer)
// {
//     this->renderer = renderer;
// }

// Renderer::~Renderer()
// {
//     delete lineDrawer;
//     delete horizontalLineDrawer;
//     delete verticalLineDrawer;

//     SDL_DestroyRenderer(renderer);
// }

// LineDrawer *Renderer::GetLineDrawer()
// {
//     return lineDrawer;
// }

// void Renderer::SetLineDrawer(LineDrawer *lineDrawer)
// {
//     this->lineDrawer = lineDrawer;
// }

// LineDrawer *Renderer::GetHorizontalLineDrawer()
// {
//     return this->horizontalLineDrawer;
// }

// void Renderer::SetHorizontalLineDrawer(LineDrawer *lineDrawer)
// {
//     this->horizontalLineDrawer = lineDrawer;
// }

// LineDrawer *Renderer::GetVerticalLineDrawer()
// {
//     return this->verticalLineDrawer;
// }

// void Renderer::SetVerticalLineDrawer(LineDrawer *lineDrawer)
// {
//     this->verticalLineDrawer = lineDrawer;
// }

// void Renderer::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
// {
//     SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
// }

// void Renderer::SetPixel(int32_t x, int32_t y)
// {
//     SDL_RenderDrawPoint(this->renderer, x, y);
// }

// void Renderer::Clear()
// {
//     SDL_RenderClear(this->renderer);
// }

// void Renderer::Render()
// {
//     SDL_RenderPresent(this->renderer);
// }

// void Renderer::DrawLine(int32_t x0,
//                         int32_t y0,
//                         int32_t x1,
//                         int32_t y1)
// {
//     // Swap x coordinates if x0 is larger than x1
//     if (x0 > x1)
//     {
//         int32_t swap = x0;
//         x0 = x1;
//         x1 = swap;
//     }

//     if (x0 == x1)
//     {
//         this->verticalLineDrawer->DrawLine(this, x0, y0, x1, y1);
//     }
//     else if (y0 == y1)
//     {
//         this->horizontalLineDrawer->DrawLine(this, x0, y0, x1, y1);
//     }
//     else
//     {
//         this->lineDrawer->DrawLine(this, x0, y0, x1, y1);
//     }
// }

// int main(int argc, char **argv)
// {
//     int x0, y0, x1, y1;
//     x0 = atoi(argv[1]);
//     y0 = atoi(argv[2]);
//     x1 = atoi(argv[3]);
//     y1 = atoi(argv[4]);

//     SDL_Init(SDL_INIT_VIDEO);

//     auto window = SDL_CreateWindow("Projekt 1",
//                                    SDL_WINDOWPOS_CENTERED,
//                                    SDL_WINDOWPOS_CENTERED,
//                                    WINDOW_WIDTH,
//                                    WINDOW_HEIGHT,
//                                    SDL_WINDOW_SHOWN);

//     Uint32 rendererFlags = SDL_RENDERER_ACCELERATED |
//                            SDL_RENDERER_PRESENTVSYNC;

//     Renderer *renderer = new Renderer(SDL_CreateRenderer(window,
//                                                          -1,
//                                                          rendererFlags));
//     // Proper dependency injection xD
//     renderer->SetLineDrawer(new IncrementalDrawer());
//     renderer->SetHorizontalLineDrawer(new HorizontalLineDrawer());
//     renderer->SetVerticalLineDrawer(new VerticalLineDrawer());

//     renderer->SetDrawColor(COLOR_BLACK);
//     renderer->Clear();
//     renderer->Render();

//     renderer->SetDrawColor(COLOR_WHITE);
//     renderer->DrawLine(x0, y0, x1, y1);

//     renderer->Render();

//     bool running = true;
//     SDL_Event event;
//     while (running)
//     {
//         if (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_QUIT)
//             {
//                 break;
//             }
//         }
//     }

//     delete renderer;
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }
