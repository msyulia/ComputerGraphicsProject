#ifndef GK_VERTICALLINEDRAWER
#define GK_VERTICALLINEDRAWER

#include "LineDrawer.hpp"

class VerticalLineDrawer : public LineDrawer
{
public:
    void DrawLine(Renderer *renderer,
                  int32_t x0,
                  int32_t y0,
                  int32_t x1,
                  int32_t y1) override
    {
        for (size_t i = y0; i <= y1; i++)
        {
            renderer->SetPixel(x0, i);
        }
    }
};

#endif