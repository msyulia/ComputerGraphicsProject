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

struct Frame
{
    std::shared_ptr<DepthBuffer> depthBuffer;
    std::shared_ptr<FrameBuffer> frameBuffer;

    Frame(std::shared_ptr<DepthBuffer> depthBuffer,
          std::shared_ptr<FrameBuffer> frameBuffer) : depthBuffer(depthBuffer),
                                                      frameBuffer(frameBuffer) {}
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

    Frame GetNewFrame(Renderer &ren, GameObjectRegistry &registry, GlobalLightSources &lights)
    {
        auto size = ren.window->GetSize();
        //Initialize depth buffer
        auto depthBuffer = std::shared_ptr<DepthBuffer>(new DepthBuffer(size.Width, size.Height));
        depthBuffer->Fill(std::numeric_limits<double>::max());
        auto frameBuffer = std::shared_ptr<FrameBuffer>(new FrameBuffer(size.Width, size.Height));
        frameBuffer->Fill(Color::White());

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
                    Polygon2D(v1Proj, v2Proj, v3Proj));

                if (i == 24 || i == 6 || i == 15 || i == 18 || i == 33)
                {
                    currentPolygon.FlipNormal();
                }
            
                for (auto &point : currentPolygon2D)
                {
                    if (point.x >= size.Width || point.y >= size.Height)
                        continue;
                    int x = point.x;
                    int y = point.y;
                    depth = (-1) * ((x * currentPolygon.coeffA) + (y * currentPolygon.coeffB) + currentPolygon.coeffD) / currentPolygon.coeffC;
                    
                    if (depth < (*depthBuffer)(x, y))
                    {
                        (*depthBuffer)(x, y) = depth;
                        double ambientStrength = 0.1;
                        double specularStrenth = 0.5;
                        double shininess = 256;
                        Color ambientColor = Color((99.0/255.0), (159.0/255.0), 1.0) * ambientStrength; //(Blueish tint)
                        Color diffuse = Color::Black(), specular = Color::Black();
                        for (auto &l : lights.data)
                        {   
                            auto fragPosition = Point3D(point.x, point.y, depth);
                            //fragPosition.Normalize();

                            // Diffuse lightning
                            auto lightDirection = (fragPosition - l.position);
                            lightDirection.Normalize();
                            double diff = std::max((currentPolygon.Normal).Dot(lightDirection), 0.0);
                            diffuse = diffuse + (l.color * diff);

                            //Specular lightning
                            auto reflect = [](Point3D incidentVector, Point3D normal) {
                                return incidentVector - ((normal * incidentVector.Dot(normal)) * 2.0);
                            };
                            auto viewDir = Point3D(256, 256, 0) - fragPosition; //* (-1);
                            viewDir.Normalize();
                            auto reflectDir = reflect((lightDirection), currentPolygon.Normal);
                            reflectDir.Normalize();
                            double spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.0), 256);
                            specular = specular + (l.color * spec * specularStrenth);
                        }
                        
                        Color newColor = (diffuse + ambientColor + specular) * (gameObject->ObjectColor);
                        (*frameBuffer)(x, y) = newColor;
                    }
                }
            }
        }
        return Frame(depthBuffer, frameBuffer);
    }

    void DrawFrame(Renderer &ren, Frame newFrame)
    {
        auto depthBuffer = newFrame.depthBuffer;
        auto frameBuffer = newFrame.frameBuffer;
        for (int x = 0; x < depthBuffer->size.Width; x++)
        {
            for (int y = 0; y < depthBuffer->size.Height; y++)
            {
                auto bufferValue = (*depthBuffer)(x, y);
                if (bufferValue < std::numeric_limits<double>::max())
                {
                    Color c = frameBuffer->operator()(x,y);
                    ren.SetDrawColor(c);
                    //ren.SetDrawColor(Color(bufferValue,bufferValue,bufferValue));
                    ren.SetPixel(x, y);
                }
            }
        }
    }

    void DrawModelWithRandomPolygonColors(Renderer &ren, Mesh &mesh)
    {
        auto vertices = mesh.vertexBuffer;
        auto indices = mesh.indexBuffer.indices;
        for (size_t i = 0; i < indices.size(); i += 3)
        {
            Point3D v1 = vertices[indices[i]];
            Point3D v2 = vertices[indices[i + 1]];
            Point3D v3 = vertices[indices[i + 2]];

            //ren.SetDrawColor(Color::Random());
            Polygon p = Polygon(v1,v2,v3);
            Draw(ren, p);
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

    void DrawWireframe(Renderer &ren, Mesh &mesh)
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

            ren.SetDrawColor(Color::Black());
            ren.DrawLine(v1Proj.x, v1Proj.y, v2Proj.x, v2Proj.y);
            ren.DrawLine(v1Proj.x, v1Proj.y, v3Proj.x, v3Proj.y);
            ren.DrawLine(v2Proj.x, v2Proj.y, v3Proj.x, v3Proj.y);
        }
    }
    void DrawWireframe(Renderer &ren, GameObject &object)
    {
        DrawWireframe(ren, *object.mesh);
    }

private:
    Eigen::Matrix4d projection_matrix;
};

#endif