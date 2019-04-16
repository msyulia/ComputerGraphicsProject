#ifndef GK_HORIZONTALLINEDRAWER
#define GK_HORIZONTALLINEDRAWER

#include "LineDrawer.hpp"

class HorizontalLineDrawer : public LineDrawer
{
public:
    void DrawLine(Renderer *renderer,
                  int32_t x0,
                  int32_t y0,
                  int32_t x1,
                  int32_t y1) override
    {
        for (size_t i = x0; i <= x1; i++)
        {
            renderer->SetPixel(i, y0);
        }
    }
};

#endif