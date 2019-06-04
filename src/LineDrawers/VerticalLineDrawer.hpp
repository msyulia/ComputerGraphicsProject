#ifndef GK_VERTICALLINEDRAWER
#define GK_VERTICALLINEDRAWER

#include "LineDrawer.hpp"

class VerticalLineDrawer : public LineDrawer
{
public:
    std::vector<Point2D> DrawLine(int32_t x0,
                                      int32_t y0,
                                      int32_t x1,
                                      int32_t y1) override
    {
        auto result = std::vector<Point2D>();
        for (size_t i = y0; i <= y1; i++)
        {
            //renderer->SetPixel(x0, i);
            result.push_back(Point2D(x0, i));
        }
        return result;
    }
};

#endif