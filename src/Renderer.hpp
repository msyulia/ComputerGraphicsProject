#ifndef GK_RENDERER
#define GK_RENDERER

#include "Window.hpp"
#include "Geometry.hpp"
#include "LineDrawer.hpp"
#include "EFLALineDrawer.hpp"
#include "IncrementalLineDrawer.hpp"
#include "VerticalLineDrawer.hpp"
#include "HorizontalLineDrawer.hpp"
#include "ObjectRegistry.hpp"
#include <iostream>
#include <cstdint>
#include <cstdlib>

#define BLACK 0, 0, 0, 255
#define WHITE 255, 255, 255, 255
#define RED 255, 0, 0, 255

struct LightSource
{
public:
    Point3D position;
    Color color;
    LightSource() = default;
    LightSource(Point3D position, Color color) : position(position), color(color) {}
    void Translate(const double offsetX, const double offsetY, const double offsetZ)
    {
        position.X += offsetX;
        position.Y += offsetY;
        position.Z += offsetZ;
    }
};

class GlobalLightSources
{
public:
    std::vector<LightSource> data;
    GlobalLightSources() {}
    ~GlobalLightSources() {}

    void Add(LightSource &newObject) { data.emplace_back(newObject); }
    void Remove(LightSource &object) {}
};

class FrameBuffer
{
private:
    std::unique_ptr<std::vector<std::vector<Color>>> data;

public:
    FrameBuffer() = default;
    // FrameBuffer(const FrameBuffer& other)
    // {

    // }
    FrameBuffer(uint32_t frameWidth, uint32_t frameHeight)
    {
        data = std::unique_ptr<std::vector<std::vector<Color>>>(new std::vector<std::vector<Color>>());
        data->resize(frameWidth);
        for (auto &colors : *data)
        {
            colors = std::vector<Color>();
            colors.resize(frameHeight);
        }
    }
    ~FrameBuffer() {}

    Color &operator()(uint32_t i, uint32_t j)
    {
        return data->at(i).at(j);
    }

    void Fill(const Color bufferColor)
    {
        for (auto &colors : *data)
        {
            for (auto &c : colors)
            {
                c = bufferColor;
            }
        }
    }
};

// template <typename T>
// using unique_ptr_with_lambda_deleter = std::unique_ptr<T, std::function<void(T *)>>;

class Renderer
{
private:
    void SortTriangleVerticesOnY(Point2D &A, Point2D &B, Point2D &C)
    {
        if (!(A.y <= B.y && B.y <= C.y))
        {
            if (A.y > B.y)
            {
                std::swap(A, B);
            }
            if (A.y > C.y)
            {
                std::swap(A, C);
            }
            if (B.y > C.y)
            {
                std::swap(B, C);
            }
        }
    }

protected:
    std::unique_ptr<LineDrawer> lineDrawer;
    std::unique_ptr<LineDrawer> horizontalLineDrawer;
    std::unique_ptr<LineDrawer> verticalLineDrawer;

public:
    virtual ~Renderer() {}

    Window *window;

    static Renderer *Create(Window *window);

    virtual void DrawTriangle(Polygon2D triangle)
    {
        auto A = triangle.A;
        auto B = triangle.B;
        auto C = triangle.C;
        auto fillBottomFlatTriangle = [this](Polygon2D triangle) {
            auto A = triangle.A;
            auto B = triangle.B;
            auto C = triangle.C;
            double invdx1 = (double)(B.x - A.x) / (B.y - A.y);
            double invdx2 = (double)(C.x - A.x) / (C.y - A.y);
            double currentX1 = A.x, currentX2 = A.x;

            for (int y = A.y; y <= B.y; y++)
            {
                DrawLine(std::round(currentX1),
                         y,
                         std::round(currentX2),
                         y);
                currentX1 += invdx1;
                currentX2 += invdx2;
            }
        };
        auto fillTopFlatTriangle = [this](Polygon2D triangle) {
            auto _A = triangle.A;
            auto _B = triangle.B;
            auto _C = triangle.C;
            double invdx1 = (double)(_C.x - _A.x) / (_C.y - _A.y);
            double invdx2 = (double)(_C.x - _B.x) / (_C.y - _B.y);
            double currentX1 = _C.x, currentX2 = _C.x;

            for (int y = _C.y; y > _A.y; y--)
            {
                DrawLine(std::round(currentX1),
                         y,
                         std::round(currentX2),
                         y);
                currentX1 -= invdx1;
                currentX2 -= invdx2;
            }
        };
        SortTriangleVerticesOnY(A, B, C);

        if (B.y == C.y)
        {
            fillBottomFlatTriangle(triangle);
        }
        else if (A.y == B.y)
        {
            fillTopFlatTriangle(triangle);
        }
        else
        {
            auto D = Point2D(
                std::round(A.x + ((double)(B.y - A.y) / (double)(C.y - A.y)) * (double)(C.x - A.x)),
                B.y);
            fillBottomFlatTriangle(Polygon2D(A, B, D));
            fillTopFlatTriangle(Polygon2D(B, D, C));
        }
        //(int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y)
    }

    virtual std::vector<Point2D> GetScreenPointsFromTriangleProjection(Polygon2D triangle)
    {
        std::vector<Point2D> result = std::vector<Point2D>();

        auto A = triangle.A;
        auto B = triangle.B;
        auto C = triangle.C;
        auto fillBottomFlatTriangle = [&result, this](Polygon2D triangle) {
            auto A = triangle.A;
            auto B = triangle.B;
            auto C = triangle.C;
            double invdx1 = (double)(B.x - A.x) / (B.y - A.y);
            double invdx2 = (double)(C.x - A.x) / (C.y - A.y);
            double currentX1 = A.x, currentX2 = A.x;

            for (int y = A.y; y <= B.y; y++)
            {

                auto points = GetScreenPointsFromLineBetween(std::round(currentX1),
                                                             y,
                                                             std::round(currentX2),
                                                             y);
                result.insert(result.end(), points.begin(), points.end());
                currentX1 += invdx1;
                currentX2 += invdx2;
            }
        };
        auto fillTopFlatTriangle = [&result, this](Polygon2D triangle) {
            auto _A = triangle.A;
            auto _B = triangle.B;
            auto _C = triangle.C;
            double invdx1 = (double)(_C.x - _A.x) / (_C.y - _A.y);
            double invdx2 = (double)(_C.x - _B.x) / (_C.y - _B.y);
            double currentX1 = _C.x, currentX2 = _C.x;

            for (int y = _C.y; y > _A.y; y--)
            {
                auto points = GetScreenPointsFromLineBetween(std::round(currentX1),
                                                             y,
                                                             std::round(currentX2),
                                                             y);
                result.insert(result.end(), points.begin(), points.end());
                currentX1 -= invdx1;
                currentX2 -= invdx2;
            }
        };
        SortTriangleVerticesOnY(A, B, C);

        if (B.y == C.y)
        {
            fillBottomFlatTriangle(triangle);
        }
        else if (A.y == B.y)
        {
            fillTopFlatTriangle(triangle);
        }
        else
        {
            auto D = Point2D(
                std::round(A.x + ((double)(B.y - A.y) / (double)(C.y - A.y)) * (double)(C.x - A.x)),
                B.y);
            fillBottomFlatTriangle(Polygon2D(A, B, D));
            fillTopFlatTriangle(Polygon2D(B, D, C));
        }
        return result;
    }

    virtual std::vector<Point2D> GetScreenPointsFromLineBetween(int32_t x0,
                                                                int32_t y0,
                                                                int32_t x1,
                                                                int32_t y1)
    {
        if (x0 > x1)
        {
            int32_t swap = x0;
            x0 = x1;
            x1 = swap;

            swap = y0;
            y0 = y1;
            y1 = swap;
        }
        std::vector<Point2D> points;
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

        return points;
    }

    virtual void DrawLine(int32_t x0,
                          int32_t y0,
                          int32_t x1,
                          int32_t y1)
    {
        auto points = GetScreenPointsFromLineBetween(x0, y0, x1, y1);

        for (auto p : points)
        {
            this->SetPixel(p.x, p.y);
        }
    }

    virtual void SetDrawColor(Color c) = 0;

    virtual void SetBackgroundColor(Color c) = 0;

    virtual Color GetBackgroundColor() = 0;

    virtual void SetPixel(int32_t x,
                          int32_t y) = 0;

    virtual void Clear() = 0;
    virtual void Render() = 0;
};

class OSXRenderer : public Renderer
{
private:
    SDL_Renderer *sdlRenderer;
    Color backgroundColor;

public:
    OSXRenderer(OSXWindow *window)
    {
        sdlRenderer = SDL_CreateRenderer(window->sdlWindow,
                                         -1,
                                         SDL_RENDERER_ACCELERATED);
        this->window = window;

        if (this->sdlRenderer == nullptr)
        {
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        }
        std::cout << "Created sdlRenderer!" << std::endl;

        lineDrawer = std::unique_ptr<LineDrawer>(new EFLALineDrawer());
        horizontalLineDrawer = std::unique_ptr<LineDrawer>(new HorizontalLineDrawer());
        verticalLineDrawer = std::unique_ptr<LineDrawer>(new VerticalLineDrawer());

        backgroundColor = Color{0, 0, 0};
    }

    ~OSXRenderer()
    {
        std::cout << "Renderer destroyed!" << std::endl;
        SDL_DestroyRenderer(sdlRenderer);
    }

    void SetDrawColor(Color c)
    {
        SDL_SetRenderDrawColor(this->sdlRenderer,
                               std::round(c.R * 255),
                               std::round(c.G * 255),
                               std::round(c.B * 255),
                               255);
    }

    void SetBackgroundColor(Color c)
    {
        backgroundColor = c;
        SetDrawColor(c);
        Clear();
    }

    Color GetBackgroundColor()
    {
        return backgroundColor;
    }

    void SetPixel(int32_t x, int32_t y)
    {
        y = window->GetSize().Height - y;
        if (SDL_RenderDrawPoint(this->sdlRenderer, x, y))
        {
            std::cout << "Pixel draw error: " << SDL_GetError() << std::endl;
        }
    }

    void Clear()
    {
        SDL_RenderClear(this->sdlRenderer);
    }

    void Render()
    {
        SDL_RenderPresent(this->sdlRenderer);
    }
};

Renderer *Renderer::Create(Window *window)
{
    //TODO: Till no DI, put the line drawers here

    auto line_drawer = EFLALineDrawer();
    auto h_line_drawer = HorizontalLineDrawer();
    auto v_line_drawer = VerticalLineDrawer();

    Renderer *ren;

#if GK_OSX_BUILD
    ren = new OSXRenderer((OSXWindow *)window);
    return ren;
#else
    return nullptr
#endif
}

#endif