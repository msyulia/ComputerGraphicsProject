#ifndef GK_EFLALINEDRAWER
#define GK_EFLALINEDRAWER

#include "LineDrawer.hpp"

class EFLALineDrawer : public LineDrawer
{
public:
    std::vector<Point2D> DrawLine(int32_t x,
                                      int32_t y,
                                      int32_t x2,
                                      int32_t y2) override
    {
        auto result = std::vector<Point2D>();
        bool yLonger = false;
        int shortLen = y2 - y;
        int longLen = x2 - x;
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
                longLen += y;
                for (int j = 0x8000 + (x << 16); y <= longLen; ++y)
                {
                    
                    //myPixel(surface, j >> 16, y);
                    auto p = Point2D(j >> 16, y);
                    result.emplace_back(p);
                    j += decInc;
                }
                return result;
            }
            longLen += y;
            for (int j = 0x8000 + (x << 16); y >= longLen; --y)
            {
                //myPixel(surface, j >> 16, y);
                auto p = Point2D(j >> 16, y);
                result.emplace_back(p);
                j -= decInc;
            }
            return result;
        }

        if (longLen > 0)
        {
            longLen += x;
            for (int j = 0x8000 + (y << 16); x <= longLen; ++x)
            {
                //myPixel(surface, x, j >> 16);
                auto p = Point2D(x, j >> 16);
                result.emplace_back(p);
                j += decInc;
            }
            return result;
        }
        longLen += x;
        for (int j = 0x8000 + (y << 16); x >= longLen; --x)
        {
            //myPixel(surface, x, j >> 16);
            auto p = Point2D(x, j >> 16);
            result.emplace_back(p);
            j -= decInc;
        }
        return result;
    }
};

#endif