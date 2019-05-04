#ifndef GK_HORIZONTALLINEDRAWER
#define GK_HORIZONTALLINEDRAWER

#include "LineDrawer.hpp"

class HorizontalLineDrawer : public LineDrawer
{
public:
    std::vector<VectorInt2D> DrawLine(int32_t x0,
                                      int32_t y0,
                                      int32_t x1,
                                      int32_t y1) override
    {
        auto result = std::vector<VectorInt2D>();
        for (size_t i = x0; i <= x1; i++)
        {
            //renderer->SetPixel(i, y0);
            result.push_back(VectorInt2D(i, y0));
        }
        return result;
    }
};

#endif