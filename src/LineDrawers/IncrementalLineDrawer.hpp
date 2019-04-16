#ifndef GK_INCREMENTALLINEDRAWER
#define GK_INCREMENTALLINEDRAWER

#include "LineDrawer.hpp"

class IncrementalDrawer : public LineDrawer
{
public:
    void DrawLine(Renderer *renderer,
                  int32_t x0,
                  int32_t y0,
                  int32_t x1,
                  int32_t y1) override
    {
        int32_t deltaX = x1 - x0;
        int32_t deltaY = y1 - y0;
        float slope = (float)deltaY / deltaX;

        if (std::abs(slope) > 1)
        {
            slope = 1.f / slope;

            if (y0 > y1)
            {
                int32_t swap = y0;
                y0 = y1;
                y1 = swap;
            }

            float currentX = std::min(x0, x1);
            for (int32_t currentY = y0; currentY <= y1; currentY++)
            {
                renderer->SetPixel((int32_t)std::round(currentX), currentY);
                currentX += slope;
            }
        }
        else
        {
            float currentY = y0;
            for (int32_t currentX = x0; currentX <= x1; currentX++)
            {
                renderer->SetPixel(currentX, (int32_t)std::round(currentY));
                currentY += slope;
            }
        }
    }
};

#endif