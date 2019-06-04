#ifndef GK_GAMEOBJECT
#define GK_GAMEOBJECT

#include <cmath>
#include "Eigen/Geometry"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"

class GameObject
{
public:
    Mesh *mesh;
    Transform transform;
    Color Ambient, Diffuse, Specular;
    GameObject()
    {
        mesh = Mesh::CreateCube();
        transform = Transform::FromMesh(*mesh);
        Ambient = Color(0.1*255, 0.3 * 255, 0.1* 255);
    }
    ~GameObject() { delete mesh; }

    void Translate(double offsetX, double offsetY, double offsetZ)
    {
        auto translationMatrix = getHomogeneousTranslationMatrix(offsetX, offsetY, offsetZ);

        for (size_t i = 0; i < mesh->vertexBuffer.Count(); i++)
        {
            auto oldPosition = Eigen::Vector3d();
            oldPosition << mesh->vertexBuffer[i].X,
                mesh->vertexBuffer[i].Y,
                mesh->vertexBuffer[i].Z;
            auto newPosition = translationMatrix * oldPosition.homogeneous();
            auto newPoint = Point3D(newPosition.x(), newPosition.y(), newPosition.z());
            mesh->vertexBuffer.vertices.at(i) = newPoint;
        }
    }

    void Scale(double scaleX, double scaleY, double scaleZ)
    {
        auto scaleMatrix = getHomogeneousScaleMatrix(scaleX, scaleY, scaleZ);

        auto firstVertexOldPosition = mesh->vertexBuffer[0];
        for (size_t i = 0; i < mesh->vertexBuffer.Count(); i++)
        {
            auto oldPosition = Eigen::Vector3d();
            oldPosition << mesh->vertexBuffer[i].X,
                mesh->vertexBuffer[i].Y,
                mesh->vertexBuffer[i].Z;
            auto newPosition = scaleMatrix * oldPosition.homogeneous();
            auto newPoint = Point3D(newPosition.x(), newPosition.y(), newPosition.z());
            mesh->vertexBuffer.vertices.at(i) = newPoint;
        }
        auto firstVertexCurrentPosition = mesh->vertexBuffer[0];
        Translate((-1) * firstVertexCurrentPosition.X + firstVertexOldPosition.X,
                  (-1) * firstVertexCurrentPosition.Y + firstVertexOldPosition.Y,
                  (-1) * firstVertexCurrentPosition.Z + firstVertexOldPosition.Z);
    }

    void Rotate(double rotationX, double rotationY, double rotationZ)
    {
        rotationX = (rotationX / 180.0) * M_PI;
        rotationY = (rotationY / 180.0) * M_PI;
        rotationZ = (rotationZ / 180.0) * M_PI;
        auto rotationMatrix = getHomogeneousRotationMatrix(rotationX, rotationY, rotationZ);
        auto firstVertexOldPosition = mesh->vertexBuffer[0];
        for (size_t i = 0; i < mesh->vertexBuffer.Count(); i++)
        {
            auto oldPosition = Eigen::Vector3d();
            oldPosition << mesh->vertexBuffer[i].X,
                mesh->vertexBuffer[i].Y,
                mesh->vertexBuffer[i].Z;
            auto newPosition = rotationMatrix * (oldPosition.homogeneous());
            auto newPoint = Point3D(newPosition.x(), newPosition.y(), newPosition.z());
            mesh->vertexBuffer.vertices.at(i) = newPoint;
        }
        auto firstVertexCurrentPosition = mesh->vertexBuffer[0];
        Translate((-1) * firstVertexCurrentPosition.X + firstVertexOldPosition.X,
                  (-1) * firstVertexCurrentPosition.Y + firstVertexOldPosition.Y,
                  (-1) * firstVertexCurrentPosition.Z + firstVertexOldPosition.Z);
    }

private:
    Eigen::Matrix4d getHomogeneousTranslationMatrix(double offsetX, double offsetY, double offsetZ)
    {
        Eigen::Matrix4d translationMatrix;
        translationMatrix << 1, 0, 0, offsetX,
            0, 1, 0, offsetY,
            0, 0, 1, offsetZ,
            0, 0, 0, 1;
        return translationMatrix;
    }
    Eigen::Matrix4d getHomogeneousScaleMatrix(double scaleX, double scaleY, double scaleZ)
    {
        Eigen::Matrix4d scaleMatrix;
        scaleMatrix << scaleX, 0, 0, 0,
            0, scaleY, 0, 0,
            0, 0, scaleZ, 0,
            0, 0, 0, 1;
        return scaleMatrix;
    }

    Eigen::Matrix4d getHomogeneousRotationMatrix(double rotationX, double rotationY, double rotationZ)
    {
        Eigen::Matrix4d rotationMatrix;
        auto a11 = std::cos(rotationY) * std::cos(rotationZ);
        auto a12 = (-1) * std::cos(rotationY) * std::sin(rotationZ);
        auto a13 = std::sin(rotationY);
        auto a21 = std::cos(rotationX) * std::sin(rotationZ) + std::sin(rotationX) * std::sin(rotationY) * std::cos(rotationZ);
        auto a22 = std::cos(rotationX) * std::cos(rotationZ) + std::sin(rotationX) * std::sin(rotationY) * std::sin(rotationZ);
        auto a23 = (-1) * std::sin(rotationX) * std::cos(rotationY);
        auto a31 = std::sin(rotationX) * std::sin(rotationZ) - std::cos(rotationX) * std::sin(rotationY) * std::cos(rotationZ);
        auto a32 = std::sin(rotationX) * std::cos(rotationZ) + std::cos(rotationX) * std::sin(rotationY) * std::sin(rotationZ);
        auto a33 = std::cos(rotationX) * std::cos(rotationY);
        rotationMatrix << a11, a12, a13, 0,
            a21, a22, a23, 0,
            a31, a32, a33, 0,
            0, 0, 0, 1;
        return rotationMatrix;   
    }
};

#endif