#ifndef GK_EFLALINEDRAWER
#define GK_EFLALINEDRAWER

#include "LineDrawer.hpp"

class EFLALineDrawer : public LineDrawer
{
public:
    void DrawLine(Renderer *renderer,
                  int32_t x0,
                  int32_t y0,
                  int32_t x1,
                  int32_t y1) override
    {
        bool yLonger = false;
        int shortLen = y1 - y0;
        int longLen = x1 - x0;
        if (abs(shortLen) > abs(longLen))
        {
            int swap = shortLen;
            shortLen = longLen;
            longLen = swap;
            yLonger = true;
        }
        int decInc;
        if (longLen == 0)
            decInc = 0;
        else
            decInc = (shortLen << 16) / longLen;

        if (yLonger)
        {
            if (longLen > 0)
            {
                longLen += y0;
                for (int j = 0x8000 + (x0 << 16); y0 <= longLen; ++y0)
                {
                    renderer->SetPixel(j >> 16, y0);
                    j += decInc;
                }
                return;
            }
            longLen += y0;
            for (int j = 0x8000 + (x0 << 16); y0 >= longLen; --y0)
            {
                renderer->SetPixel(j >> 16, y0);
                j -= decInc;
            }
            return;
        }

        if (longLen > 0)
        {
            longLen += x0;
            for (int j = 0x8000 + (y0 << 16); x0 <= longLen; ++x0)
            {
                renderer->SetPixel(x0, j >> 16);
                j += decInc;
            }
            return;
        }
        longLen += x0;
        for (int j = 0x8000 + (y0 << 16); x0 >= longLen; --x0)
        {
            renderer->SetPixel(x0, j >> 16);
            j -= decInc;
        }
    }
};

#endif