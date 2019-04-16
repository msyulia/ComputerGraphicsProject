#ifndef GK_LINEDRAWER
#define GK_LINEDRAWER

#include <cstdint>
#include <cmath>

class Renderer;
class LineDrawer
{
public:
    virtual ~LineDrawer();
    virtual void DrawLine(Renderer *renderer,
                          int32_t x0,
                          int32_t y0,
                          int32_t x1,
                          int32_t y1) = 0;
};

#endif