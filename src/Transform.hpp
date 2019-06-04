#ifndef GK_TRANSFORM
#define GK_TRANSFORM

#include "Eigen/Geometry"
#include "Geometry.hpp"

class Transform
{
public:
    Eigen::Vector3<double> position;
    Eigen::Vector3<double> rotation;
    Eigen::Vector3<double> scale;
    Transform()
    {
        position = Eigen::Vector3<double>{0, 0, 0};
        rotation = Eigen::Vector3<double>{0, 0, 0};
        scale = Eigen::Vector3<double>{1, 1, 1};
    }
    virtual ~Transform() {}
    static Transform FromMesh(Mesh mesh)
    {
        double sumX, sumY, sumZ;
        size_t vertexCount = mesh.vertexBuffer.Count();
        for (size_t i = 0; i < vertexCount; i++)
        {
            sumX += mesh.vertexBuffer[i].X;
            sumY += mesh.vertexBuffer[i].Y;
            sumZ += mesh.vertexBuffer[i].Z;
        }
        Eigen::Vector3<double> position;
        position << sumX / vertexCount, sumY / vertexCount, sumZ / vertexCount;

        auto result = Transform();
        result.position = position;

        return result;
    }
};

#endif