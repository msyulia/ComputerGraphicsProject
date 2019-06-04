// #ifndef GK_VECTORS
// #define GK_VECTORS

// #include "Eigen/Dense"

// template <typename T>
// class Vector2DAdapter
// {
// public:
//     T x, y;
//     Vector2DAdapter<T>(T newX, T newY) : x(newX), y(newY) {}
//     virtual ~Vector2DAdapter<T>() {}
//     virtual Vector2DAdapter<T> operator+(Vector2DAdapter<T> other) = 0;
//     virtual Vector2DAdapter<T> operator+=(Vector2DAdapter<T> other) = 0;
//     virtual Vector2DAdapter<T> operator-(Vector2DAdapter<T> other) = 0;
//     virtual Vector2DAdapter<T> operator-=(Vector2DAdapter<T> other) = 0;
//     virtual Vector2DAdapter<T> operator*(T scalar) = 0;
//     virtual Vector2DAdapter<T> operator*=(T scalar) = 0;
//     virtual Vector2DAdapter<T> operator/(T scalar) = 0;
//     virtual Vector2DAdapter<T> operator/=(T scalar) = 0;
//     virtual T Dot(Vector2DAdapter<T> other) = 0;
//     virtual Vector2DAdapter<T> Cross(Vector2DAdapter<T> other) = 0;
// };

// template <typename T>
// class Vector3DAdapter
// {
// public:
//     T x, y, z;
//     Vector3DAdapter<T>(T newX, T newY, T newZ) : x(newX), y(newY), z(newZ) {}
//     virtual ~Vector3DAdapter<T>() {}
//     virtual Vector3DAdapter<T> operator+(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator+=(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator-(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator-=(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator*(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator*=(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator/(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator/=(T scalar) = 0;
//     virtual T Dot(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> Cross(Vector3DAdapter<T> other) = 0;
// };

// template <typename T>
// class Vector3D : public Vector3DAdapter<T>
// {
// private:
//     Eigen::Vector3<T> data;

// public:
//     Vector3D<T>(T newX, T newY, T newZ) 
//     {
//         data = Eigen::Vector3<T>();
//     }
//     virtual ~Vector3D<T>() {}
//     virtual Vector3DAdapter<T> operator+(Vector3DAdapter<T> other) 
//     {
        
//     }
//     virtual Vector3DAdapter<T> operator+=(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator-(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator-=(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> operator*(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator*=(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator/(T scalar) = 0;
//     virtual Vector3DAdapter<T> operator/=(T scalar) = 0;
//     virtual T Dot(Vector3DAdapter<T> other) = 0;
//     virtual Vector3DAdapter<T> Cross(Vector3DAdapter<T> other) = 0;
// };


// struct VectorInt2D
// {
// public:
//     int x, y;
//     VectorInt2D(int newX, int newY) : x(newX), y(newY) {}
// };

// struct VectorDouble3D
// {
// public:
//     double x, y, z;
//     VectorDouble3D(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ) {}
// };

// #endif
