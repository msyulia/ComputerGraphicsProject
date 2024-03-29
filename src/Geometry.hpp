#ifndef GK_GEOMETRY
#define GK_GEOMETRY

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_set>
struct Point2D
{
public:
    double x, y;

    Point2D(double newX = 0, double newY = 0)
    {
        x = newX,
        y = newY;
    }

    Point2D operator+(Point2D other)
    {
        return Point2D(x + other.x, y + other.y);
    }

    Point2D operator-(Point2D other)
    {
        return Point2D(x - other.x, y - other.y);
    }

    double Dot(Point2D other)
    {
        return x * other.x + y * other.y;
    }

    double Magnitude()
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    void Normalize()
    {
        auto norm = Magnitude();
        x /= norm;
        y /= norm;
    }

    static Point2D Zero()
    {
        return Point2D(0, 0);
    }
};

struct Point3D
{
    double X, Y, Z;
    Point3D(double newX = 0, double newY = 0, double newZ = 0) : X(newX), Y(newY), Z(newZ) {}

    bool operator==(Point3D other)
    {
        return X == other.X &&
               Y == other.Y &&
               Z == other.Z;
    }

    Point3D operator*(double scalar)
    {
        return Point3D(X * scalar, Y * scalar, Z * scalar);
    }

    Point3D operator+(Point3D other)
    {
        return Point3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Point3D operator-(Point3D other)
    {
        return Point3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Point3D operator-(Point2D other)
    {
        return Point3D(X - other.x, Y - other.y, Z);
    }

    double Dot(Point3D other)
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    double Magnitude()
    {
        return std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2));
    }

    void Normalize()
    {
        auto norm = Magnitude();
        X /= norm;
        Y /= norm;
        Z /= norm;
    }

    static Point3D Zero()
    {
        return Point3D{0, 0, 0};
    }
};

struct Color
{
private:
    double validate(double c)
    {
        return std::clamp(c, 0.0, 1.0);
    }

public:
    double R, G, B;
    Color() = default;
    Color(double R, double G, double B) : R(R), G(G), B(B) {}
    Color operator*(double scalar)
    {
        double _R = R;
        double _G = G;
        double _B = B;
        double __R = validate(_R * scalar);
        double __G = validate(_G * scalar);
        double __B = validate(_B * scalar);
        return Color(__R, __G, __B);
    }
    Color operator*(Color other)
    {
        Color result = Color(validate(R * other.R),
                             validate(G * other.G),
                             validate(B * other.B));
        return result;
    }
    Color operator+(Color other)
    {
        Color result = Color(validate(R + other.R),
                             validate(G + other.G),
                             validate(B + other.B));
        return result;
    }
    explicit operator Point3D() const
    {
        return Point3D(R, G, B);
    }
    static Color Random()
    {
        return Color((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);
    }
    static Color White()
    {
        return Color(1.0, 1.0, 1.0);
    }
    static Color Black()
    {
        return Color(0.0, 0.0, 0.0);
    }
};

struct Polygon
{
public:
    Point3D A, B, C, Normal;
    double coeffA, coeffB, coeffC, coeffD;
    Polygon() = default;
    Polygon(Point3D newA, Point3D newB, Point3D newC) : A(newA), B(newB), C(newC)
    {
        double x1 = newA.X;
        double y1 = newA.Y;
        double z1 = newA.Z;

        //Calculate plane coefficients
        auto coeff = NormalToPolygon();
        coeffA = coeff.X;
        coeffB = coeff.Y;
        coeffC = coeff.Z;
        coeffD = (-1) * (coeffA * x1 + coeffB * y1 + coeffC * z1);
        Normal = coeff;
        Normal.Normalize();
    }
    Point3D NormalToPolygon()
    {
        return { // (B - A) x (C - A)
            (B.Y - A.Y) * (C.Z - A.Z) - (B.Z - A.Z) * (C.Y - A.Y),
            (-1) * ((B.X - A.X) * (C.Z - A.Z) - (B.Z - A.Z) * (C.X - A.X)),
            (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X)};
    }
    void FlipNormal()
    {
        Normal = Normal * (-1);
        coeffA *= -1;
        coeffB *= -1;
        coeffC *= -1;
        coeffD *= -1;
    }
};

struct Polygon2D
{
    Point2D A, B, C;
    Polygon2D() = default;
    Polygon2D(Point2D A, Point2D B, Point2D C) : A(A), B(B), C(C) {}
};

class VertexBuffer
{
public:
    std::vector<Point3D> vertices;
    VertexBuffer()
    {
        vertices = std::vector<Point3D>();
    };
    VertexBuffer(std::vector<Point3D> vertices)
    {
        this->vertices = vertices;
    }

    bool Contains(Point3D p)
    {
        return std::find(vertices.begin(), vertices.end(), p) != vertices.end();
    }

    size_t IndexOf(Point3D p)
    {
        if (Contains(p))
        {
            return std::distance(vertices.begin(),
                                 std::find(vertices.begin(), vertices.end(), p));
        }
        return -1;
    }

    void Add(Point3D p)
    {
        vertices.emplace_back(p);
    }

    size_t Count()
    {
        return vertices.size();
    }

    Point3D operator[](size_t i)
    {
        return vertices[i];
    }
};

class IndexBuffer
{
public:
    std::vector<int> indices;
    IndexBuffer() = default;
    IndexBuffer(std::vector<int> indices)
    {
        this->indices = indices;
    }

    bool Contains(size_t i)
    {
        return std::find(indices.begin(), indices.end(), i) != indices.end();
    }

    size_t IndexOf(size_t i)
    {
        if (Contains(i))
        {
            return std::distance(indices.begin(),
                                 std::find(indices.begin(), indices.end(), i));
        }
        return -1;
    }

    void Add(size_t i)
    {
        indices.emplace_back(i);
    }
};

class Mesh
{
public:
    //std::vector<Polygon> vertices;
    IndexBuffer indexBuffer;
    VertexBuffer vertexBuffer;

    static Mesh *CreateCube()
    {
        auto vertices = VertexBuffer({
            {0, 0, 0},
            {1, 0, 0},
            {0, 1, 0},
            {1, 1, 0},
            {0, 0, 1},
            {1, 0, 1},
            {0, 1, 1},
            {1, 1, 1},
        });
        auto indices = IndexBuffer({0, 1, 3,
                                    2, 0, 3,
                                    1, 3, 5,
                                    3, 5, 7,
                                    5, 6, 7,
                                    4, 5, 6,
                                    0, 4, 6,
                                    0, 2, 6,
                                    0, 1, 5,
                                    0, 4, 5,
                                    2, 3, 6,
                                    3, 6, 7,
                                    });

        return new Mesh(vertices, indices);
    }
    Mesh(VertexBuffer vertices, IndexBuffer indices)
    {
        vertexBuffer = vertices;
        indexBuffer = indices;
    }

    Mesh() = default;
    ~Mesh()
    {
    }
};

#endif