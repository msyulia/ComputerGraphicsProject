#ifndef GK_CAMERA
#define GK_CAMERA

#include <limits>
#include "Eigen/Core"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "ObjectRegistry.hpp"

struct BufferSize
{
    uint32_t Width, Height;
    BufferSize(uint32_t Width, uint32_t Height) : Width(Width), Height(Height){};
    BufferSize() = default;
};

class DepthBuffer
{
public:
    std::unique_ptr<std::vector<std::vector<double>>> data;
    BufferSize size;

    DepthBuffer() = default;
    DepthBuffer(uint32_t frameWidth, uint32_t frameHeight)
    {
        data = std::unique_ptr<std::vector<std::vector<double>>>(new std::vector<std::vector<double>>());
        data->resize(frameWidth);
        for (auto &val : *data)
        {
            val = std::vector<double>();
            val.resize(frameHeight);
        }
        size = BufferSize(frameWidth, frameHeight);
    }
    ~DepthBuffer() {}

    double &operator()(uint32_t i, uint32_t j)
    {
        return data->at(i).at(j);
    }

    void Fill(const double bufferValue)
    {
        for (auto &values : *data)
        {
            for (auto &v : values)
            {
                v = bufferValue;
            }
        }
    }
};

class Camera
{
public:
    std::unique_ptr<Transform> transform;
    Camera()
    {
        projection_matrix << 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 1;
        transform = std::unique_ptr<Transform>(new Transform());
    }
    ~Camera() {}

    std::shared_ptr<DepthBuffer> GetDepthBuffer(Renderer &ren, GameObjectRegistry &registry)
    {
        auto size = ren.window->GetSize();
        //Initialize depth buffer
        auto depthBuffer = std::shared_ptr<DepthBuffer>(new DepthBuffer(size.Width, size.Height));
        depthBuffer->Fill(std::numeric_limits<double>::max());
        auto frameBuffer = std::shared_ptr<FrameBuffer>(new FrameBuffer(size.Width, size.Height));

        for (auto &gameObject : registry)
        {
            auto indexBuffer = gameObject->mesh->indexBuffer.indices;
            auto vertexBuffer = gameObject->mesh->vertexBuffer.vertices;

            double depth;
            //Foreach polygon in game object
            for (auto i = 0; i < indexBuffer.size(); i += 3)
            {
                Point3D v1 = vertexBuffer[indexBuffer[i]];
                Point3D v2 = vertexBuffer[indexBuffer[i + 1]];
                Point3D v3 = vertexBuffer[indexBuffer[i + 2]];

                Polygon currentPolygon = Polygon{v1, v2, v3};

                Point2D v1Proj = GetPointProjection(v1);
                Point2D v2Proj = GetPointProjection(v2);
                Point2D v3Proj = GetPointProjection(v3);

                auto currentPolygon2D = ren.GetScreenPointsFromTriangleProjection(
                    Polygon2D(v1Proj, v2Proj, v3Proj)
                );

                for (auto &point : currentPolygon2D)
                {
                    if (point.x >= size.Width || point.y >= size.Height)
                        continue;
                    int x = point.x;
                    int y = point.y;
                    depth = (-1) * (x * currentPolygon.coeffA + y * currentPolygon.coeffB + currentPolygon.coeffD) / currentPolygon.coeffC;

                    if (depth < (*depthBuffer)(x, y))
                    {
                        (*depthBuffer)(x, y) = depth;
                        //Calculate color of pixel in frame buffer
                        //Color newColor = 
                        //(*frameBuffer)(x,y)                        
                    }
                }
            }
        }
        return depthBuffer;
    }

    void DrawDepthBuffer(Renderer &ren, std::shared_ptr<DepthBuffer> buffer)
    {
        for (int x = 0; x < buffer->size.Width; x++)
        {
            for (int y = 0; y < buffer->size.Height; y++)
            {
                auto bufferValue = (*buffer)(x, y);
                if (bufferValue < std::numeric_limits<double>::max())
                {
                    ren.SetPixel(x, y);
                }
            }
        }
    }

    std::vector<Point2D> GetTriangleProjectionPoints(Renderer &ren, Point3D v1, Point3D v2, Point3D v3)
    {
        auto A = GetPointProjection(v1);
        auto B = GetPointProjection(v2);
        auto C = GetPointProjection(v3);

        auto triangleVertices = Polygon2D{A, B, C};

        return ren.GetScreenPointsFromTriangleProjection(triangleVertices);
    }

    Point2D GetPointProjection(Point3D p)
    {
        Eigen::Vector3d eigenPoint;
        eigenPoint << p.X,
            p.Y,
            p.Z;
        auto projection = projection_matrix * eigenPoint.homogeneous();
        return Point2D(std::round(projection.x()), std::round(projection.y()));
    }

    void Draw(Renderer &ren, Polygon &triangle)
    {
        for (auto &p : GetTriangleProjectionPoints(ren, triangle.A, triangle.B, triangle.C))
        {
            ren.SetPixel(p.x, p.y);
        }
    }

    void Draw(Renderer &ren, Mesh &mesh)
    {
        auto vertices = mesh.vertexBuffer;
        auto indices = mesh.indexBuffer.indices;
        for (size_t i = 0; i < indices.size(); i += 3)
        {
            Point3D v1 = vertices[indices[i]];
            Point3D v2 = vertices[indices[i + 1]];
            Point3D v3 = vertices[indices[i + 2]];

            Point2D v1Proj = GetPointProjection(v1);
            Point2D v2Proj = GetPointProjection(v2);
            Point2D v3Proj = GetPointProjection(v3);

            ren.SetDrawColor(0, 0, 0, 255);
            ren.DrawLine(v1Proj.x, v1Proj.y, v2Proj.x, v2Proj.y);
            ren.DrawLine(v1Proj.x, v1Proj.y, v3Proj.x, v3Proj.y);
            ren.DrawLine(v2Proj.x, v2Proj.y, v3Proj.x, v3Proj.y);
        }
    }
    void Draw(Renderer &ren, GameObject &object)
    {
        Draw(ren, *object.mesh);
    }

private:
    Eigen::Matrix4d projection_matrix;
};

#endif