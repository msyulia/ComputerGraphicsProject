#ifndef GK_OBJECTREGISTRY
#define GK_OBJECTREGISTRY

#include <vector>
#include "Geometry.hpp"
#include "GameObject.hpp"

template <typename TObject>
class ObjectRegistry
{
public:
    virtual ~ObjectRegistry() {}

    virtual void Add(TObject &newObject) = 0;
    virtual void Remove(TObject &object) = 0;
};

class GameObjectRegistry : public ObjectRegistry<GameObject>
{
private:
    std::vector<std::shared_ptr<GameObject>> registry;

public:
    using iterator = std::vector<std::shared_ptr<GameObject>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<GameObject>>::const_iterator;

    GameObjectRegistry(/* args */) {}
    ~GameObjectRegistry() {}

    void Add(GameObject &newGameObject)
    {
        //registry.emplace_back(std::make_shared<GameObject>(newGameObject));
    }

    void Add(std::shared_ptr<GameObject> newGameObject)
    {
        registry.emplace_back(newGameObject);
    }

    void Remove(GameObject &gameObject)
    {
    }

    iterator begin() { return registry.begin(); }
    const_iterator begin() const { return registry.begin(); }
    iterator end() { return registry.end(); }
    const_iterator end() const { return registry.end(); }
};

class MeshRegistry : public ObjectRegistry<Mesh>
{
private:
    std::vector<std::shared_ptr<Mesh>> registry;

public:
    using iterator = std::vector<std::shared_ptr<Mesh>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Mesh>>::const_iterator;

    MeshRegistry()
    {
        registry = std::vector<std::shared_ptr<Mesh>>();
    }
    ~MeshRegistry() {}

    void Add(Mesh &newMesh)
    {
        registry.emplace_back(std::make_shared<Mesh>(newMesh));
    }

    void Remove(Mesh &mesh)
    {
    }

    iterator begin() { return registry.begin(); }
    const_iterator begin() const { return registry.begin(); }
    iterator end() { return registry.end(); }
    const_iterator end() const { return registry.end(); }
};

#endif