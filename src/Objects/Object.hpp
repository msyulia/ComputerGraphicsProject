#ifndef GK_OBJECT
#define GK_OBJECT

#include <map>
#include <string>
#include <typeinfo>
#include <vector>
#include <memory>

class Component; // Implement this shit

class Object
{
private:
    std::map<std::string, std::vector<std::shared_ptr<Component>>> componentLookup;

    template <typename T>
    std::string typeToString()
    {
        return std::string(typeid(T).name());
    }

public:
    Object()
    {
        componentLookup = std::map<std::string, std::vector<std::shared_ptr<Component>>>();
    }
    virtual ~Object()
    {
        componentLookup.clear();
    }

    template <typename T>
    std::shared_ptr<T> GetComponentOfType()
    {
        auto typeName = typeToString<T>();
        std::shared_ptr<Component> result = NULL;

        if ((componentLookup[typeName] != NULL) && (componentLookup[typeName].size() > 0))
        {
            result = componentLookup[typeName].front();
        }
        return result;
    }

    template <typename T>
    std::vector<std::shared_ptr<T>> GetComponentsOfType()
    {
        auto typeName = typeToString<T>();
        return componentLookup[typeName];
    }

    template <typename T>
    void AddComponentOfType()
    {
        auto typeName = typeToString<T>();
        if (componentLookup[typeName] == NULL)
        {
            componentLookup[typeName] = std::vector<std::shared_ptr<Component>>();
        }
        componentLookup[typeName].push_back(std::shared_ptr<Component>(new T()));
    }

    template <typename T>
    std::shared_ptr<Component> RemoveComponentOfType()
    {
        auto typeName = typeToString<T>();
        std::shared_ptr<Component> deleted = NULL;
        if ((componentLookup[typeName] != NULL) && (componentLookup[typeName].size() > 0))
        {
            deleted = componentLookup[typeName].back();
            componentLookup[typeName].pop_back();
        }
        return deleted;
    }

    template <typename T>
    std::vector<std::shared_ptr<Component>> RemoveComponentsOfType()
    {
        auto typeName = typeToString<T>();   
        std::vector<std::shared_ptr<Component>> deleted;

        if (componentLookup[typeName] != NULL)
        {
            deleted = componentLookup[typeName];
            componentLookup.erase(typeName);
        }
        return deleted;
    }
};

#endif
