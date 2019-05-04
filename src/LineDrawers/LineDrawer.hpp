#ifndef GK_LINEDRAWER
#define GK_LINEDRAWER

#include <cstdint>
#include <cmath>
#include <vector>

#include "Vectors.hpp"

class LineDrawer
{
public:
    virtual ~LineDrawer() {}
    virtual std::vector<VectorInt2D> DrawLine(int32_t x0,
                                              int32_t y0,
                                              int32_t x1,
                                              int32_t y1) = 0;
};

#endif