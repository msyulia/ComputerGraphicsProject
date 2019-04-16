#ifndef GK_RENDERER
#define GK_RENDERER

#ifndef GK_LINEDRAWER
#include "LineDrawer.hpp"
#endif

#include <cstdint>

class Renderer
{
protected:
    LineDrawer *lineDrawer;
    LineDrawer *horizontalLineDrawer;
    LineDrawer *verticalLineDrawer;

public:
    virtual ~Renderer() {}

    virtual LineDrawer *GetLineDrawer()
    {
        return lineDrawer;
    }
    virtual void SetLineDrawer(LineDrawer *lineDrawer)
    {
        this->lineDrawer = lineDrawer;
    }

    virtual LineDrawer *GetHorizontalLineDrawer()
    {
        return horizontalLineDrawer;
    }
    virtual void SetHorizontalLineDrawer(LineDrawer *lineDrawer)
    {
        this->horizontalLineDrawer = lineDrawer;
    }

    virtual LineDrawer *GetVerticalLineDrawer()
    {
        return verticalLineDrawer;
    }
    virtual void SetVerticalLineDrawer(LineDrawer *lineDrawer)
    {
        this->verticalLineDrawer = lineDrawer;
    }

    virtual void DrawLine(int32_t x0,
                          int32_t y0,
                          int32_t x1,
                          int32_t y1)
    {
        if (x0 > x1)
        {
            int32_t swap = x0;
            x0 = x1;
            x1 = swap;
        }

        if (x0 == x1)
        {
            this->verticalLineDrawer->DrawLine(this, x0, y0, x1, y1);
        }
        else if (y0 == y1)
        {
            this->horizontalLineDrawer->DrawLine(this, x0, y0, x1, y1);
        }
        else
        {
            this->lineDrawer->DrawLine(this, x0, y0, x1, y1);
        }
    }

    virtual void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void SetPixel(int32_t x, int32_t y) = 0;

    virtual void Clear() = 0;
    virtual void Render() = 0;
};

#endif