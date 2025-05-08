#ifndef FE_OBJECT_HPP
#define FE_OBJECT_HPP

#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>

#include <cstddef>

#include "fe/resource_manager.hpp"

namespace fe {

class Component;
class Renderer;

class Object {
public:
    ResourceManager* resource_manager;
    std::unordered_set<Object*> children;
    std::unordered_map<std::type_index, Component*> components_by_type;
    Object* parent = nullptr;
    std::string name;

    Object();
    Object(std::string p_name);
    virtual ~Object();

    /**
     * @brief Called on every object before the next frame is drawn. 
     */
    virtual void OnUpdate();

    // TODO: Allow transfer of ownership between objects/between RM and object 

    /**
     * @brief Makes this object a tentative object, meaning that it will not
     * be destroyed when its parent is destroyed. Useful for objects which exist
     * between scenes, and assets which are not owned by any scene. 
     */
    void UnbindFromParent();

    /**
     * @brief Creates a new object with this object's Resource Manager and makes it a child
     * of this object.
     * @tparam T Type of the new object. Must be derived from Object.
     * @tparam Args Types of the arguments to be passed to the constructor of the new object.
     * @param ctor_args Arguments to be passed to the constructor of the new object.
     * @returns Pointer to the new object.
     */
    template <class T, class... Args>
    T* AddChild(Args&&... ctor_args) requires (std::is_base_of_v<Object, T>) {
        T* child = resource_manager->CreateObject<T>(std::forward<Args>(ctor_args)...);
        insert_child_(child);

        child->parent = dynamic_cast<Object*>(this);

        return child;
    }

    /**
     * @brief Relinquishes ownership of this object, and destroys it via the Resource Manager if it is not tentative.
     * @tparam T Type of the object to be removed. Must be derived from Object.
     * @param obj Pointer to the object to be removed.
     * @note For data security, function will not destroy the object if it is not a child of this object.
     */
    template <class T>
    void RemoveChild(T* obj) requires (std::is_base_of_v<Object, T>) {
        if (!remove_child_(obj)) return;

        if (!resource_manager->ObjectIsTentative(obj)) 
            resource_manager->DestroyObject(obj);
    }

    /**
     * @brief Creates a new component object of type `T` and makes it an owned component of this object.
     * @tparam T Type of the component to be added. Must be derived from `fe::Component`. 
     * @tparam Args Types of the arguments to be passed to the constructor of the new component.
     */
    template <class T, class... Args>
    T* CreateComponent(Args&&... ctor_args) requires (std::is_base_of_v<Component, T>) {
        assert(!component_assigned_<T>());

        T* component = resource_manager->CreateObject<T>(std::forward<Args>(ctor_args)...);
        insert_component_(component);
        component->parent = dynamic_cast<Object*>(this);

        return component;
    }

    /**
     * @brief Retrieves a component of type `T` from this object.
     * @tparam T Type of the component to be retrieved. Must be derived from `fe::Component`.
     * @returns Pointer to the component, or `nullptr` if no such component exists.
     */
    template <class T>
    T* GetComponent() requires (std::is_base_of_v<Component, T>) {
        if (!component_assigned_<T>()) return nullptr;

        return dynamic_cast<T*>(components_by_type.at(typeid(T)));
    }

    /**
     * @brief Removes a component from this object, and destroys it if it is not tentative. 
     * @tparam T Type of the component to be removed. Must be derived from `fe::Component`.
     */
    template <class T>
    void RemoveComponent() requires (std::is_base_of_v<Component, T>) {
        if (!component_assigned_<T>()) return;

        auto component = dynamic_cast<T*>(components_by_type.extract(typeid(T)).mapped());
        if constexpr (std::is_base_of_v<Renderer, T>) {
            resource_manager->MarkObjectRenderable(this, false);
        }

        if (!resource_manager->ObjectIsTentative(component))
            resource_manager->DestroyObject(component);
    }

    template <class T=Component>
    void RemoveComponentById(const std::type_info& component_typeid) {
        if (components_by_type.find(component_typeid) == components_by_type.end())
            return;
        
        auto component = dynamic_cast<T*>(components_by_type.extract(std::type_index(component_typeid)).mapped());
        if (dynamic_cast<Renderer*>(component))
            resource_manager->MarkObjectRenderable(this, false);

        if (!resource_manager->ObjectIsRenderable(component))
            resource_manager->DestroyObject(component);
    }

    template <class T>
    bool HasComponent() {
        return components_by_type.find(typeid(T)) != components_by_type.end();
    }

private:
    /**
     * @brief Removes an object from `children`. 
     * @returns Success flag: `false` if `obj` is not found, `true` otherwise. 
     */
    bool remove_child_(Object* obj);

    template <class T>
    void insert_child_(T* obj) {
        children.insert(dynamic_cast<Object*>(obj));
    }

    template <class T>
    bool component_assigned_() {
        return !(components_by_type.find(typeid(T)) == components_by_type.end());
    }

    template <class T>
    void insert_component_(T* component) {
        components_by_type.insert({ typeid(T), dynamic_cast<Component*>(component) });
    
        // if it becomes a problem, refactor this as a runtime check 
        if constexpr (std::is_base_of_v<Renderer, T>) {
            resource_manager->MarkObjectRenderable(this);
        }
    }
};

}

#endif 