#ifndef GK_LINEDRAWER
#define GK_LINEDRAWER

#include "../Vectors.hpp"
#include <cstdint>
#include <cmath>
#include <vector>

class LineDrawer
{
public:
    virtual ~LineDrawer() {}
    virtual std::vector<Point2D> DrawLine(int32_t x0,
                                              int32_t y0,
                                              int32_t x1,
                                              int32_t y1) = 0;
};

#endif