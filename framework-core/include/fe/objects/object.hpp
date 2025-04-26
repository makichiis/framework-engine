#ifndef FE_OBJECT_HPP
#define FE_OBJECT_HPP

#include <unordered_map>
#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>

#include <cstddef>

#include "../resource_manager.hpp"

namespace fe {

class Object {
public:
    ResourceManager* resource_manager;
    std::vector<Object*> children; // TODO: Refactor as unordered set for O(1) removal
    std::string name;

    Object();
    Object(std::string p_name);
    virtual ~Object();

    // TODO: Allow transfer of ownership between objects/between RM and object 

    /**
     * @brief Makes this object a tentative object, meaning that it will not
     * be destroyed when its parent is destroyed. Useful for objects which exist
     * between scenes. 
     */
    void UnbindFromParent();

    /**
     * @brief Creates a new object with this object's Resource Manager and makes it a child
     * of this object. 
     */
    template <class T, class... Args>
    T* AddChild(Args&&... ctor_args) requires (std::is_base_of_v<Object, T>) {
        T* child = resource_manager->CreateObject<T>(std::forward<Args>(ctor_args)...);
        children.push_back(dynamic_cast<Object*>(child));

        return child;
    }

    /**
     * @brief Relinquishes ownership of this object, and destroys it via the Resource Manager.
     */
    template <class T>
    void RemoveChild(T* obj) requires (std::is_base_of_v<Object, T>) {
        if (!remove_child_and_shift_(obj)) {
            std::cerr << "Object not in this tree.\n";
            std::exit(1);
        }

        resource_manager->DestroyObject(obj);
    }

private:
    /**
     * @brief Removes an object from `children` and shifts every consecutive element leftwards. 
     * @returns Success flag: `false` if `obj` is not found, `true` otherwise. 
     */
    bool remove_child_and_shift_(Object* obj);
};

}

#endif 