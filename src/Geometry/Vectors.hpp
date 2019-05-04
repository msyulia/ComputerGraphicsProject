#ifndef GK_VECTORS
#define GK_VECTORS

template <typename T>
struct Vector2D
{
    T x, y;
    Vector2D<T>(T newX, T newY) : x(newX), y(newY) {}
};

template <typename T>
struct Vector3D
{
    T x, y, z;
    Vector3D<T>(T newX, T newY, T newZ) : x(newX), y(newY), z(newZ) {}
};

struct VectorInt2D
{
public:
    int x, y;
    VectorInt2D(int newX, int newY) : x(newX), y(newY) {}
};

struct VectorDouble3D
{
public:
    double x, y, z;
    VectorDouble3D(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ) {}
};

#endif