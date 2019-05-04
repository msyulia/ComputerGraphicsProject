#include "Renderer.hpp"
#include "LinuxRenderer.hpp"
#include "OSXRenderer.hpp"

Renderer *Renderer::Create()
{
    //TODO: Till no DI, put the line drawers here

    auto line_drawer = EFLALineDrawer();
    auto h_line_drawer = HorizontalLineDrawer();
    auto v_line_drawer = VerticalLineDrawer();

    Renderer *ren;

#if GK_LINUX_BUILD
    ren = new LinuxRenderer();
    ren->SetLineDrawer(&line_drawer);
    ren->SetHorizontalLineDrawer(&h_line_drawer);
    ren->SetVerticalLineDrawer(&v_line_drawer);
    return ren;
#endif

#if GK_OSX_BUILD
    ren = (Renderer *)new OSXRenderer();
    ren->SetLineDrawer(&line_drawer);
    ren->SetHorizontalLineDrawer(&h_line_drawer);
    ren->SetVerticalLineDrawer(&v_line_drawer);
    return ren;
#endif
}

void Renderer::DrawLine(int32_t x0,
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
    std::vector<VectorInt2D> points;
    if (x0 == x1)
    {
        points = this->verticalLineDrawer->DrawLine(x0, y0, x1, y1);
    }
    else if (y0 == y1)
    {
        points = this->horizontalLineDrawer->DrawLine(x0, y0, x1, y1);
    }
    else
    {
        points = this->lineDrawer->DrawLine(x0, y0, x1, y1);
    }

    for (auto p : points)
    {
        this->SetPixel(p.x, p.y);
    }
}