#ifndef FE_RESOURCE_MANAGER_HPP
#define FE_RESOURCE_MANAGER_HPP

#include <memory_resource>
#include <unordered_set>
#include <type_traits>
#include <cassert>

namespace fe {

class Object;

template <class T>
concept ObjectType = std::is_base_of_v<Object, T>;

class ResourceManager {
public:
    using Allocator = std::pmr::polymorphic_allocator<Object>;
#ifndef DEBUG
private:
#endif 
    // TODO: Make template. Refactored as non-template in order to
    // temporarily resolve circular dependency issues.
    Allocator alloc_;

    std::unordered_set<Object*> allocated_objects_;
    std::unordered_set<Object*> tentative_objects_;

public:
    ResourceManager();
    ResourceManager(Allocator alloc);

    ~ResourceManager();

    /**
     * @brief Creates an unowned object managed by this resource. Must be freed
     * via call to `this->DestroyObject(T)`. 
     * @note If calling this function from within a script or runtime drivers,
     * `fe::Object::AddChild<T>` handles object allocation AND transfer of
     * ownership from RMS to parent object. 
     */
    template <ObjectType T, class... Args>
    T* CreateObject(Args&&... ctor_args) {
        T* obj = alloc_.template new_object<T>(std::forward<Args>(ctor_args)...);
        obj->resource_manager = this;

        allocated_objects_.insert(obj);

        return obj;
    }

    /**
     * @brief Destroy `obj` allocated by this resource manager. Destroys all owned children. 
     */
    template <ObjectType T>
    void DestroyObject(T* obj) {
        assert(object_is_in_alloc_heap_(dynamic_cast<Object*>(obj)));

        if (obj->parent) {
            obj->parent->children.erase(obj); // Prevent hanging child reference (issue #1)
            obj->parent = nullptr;
        }

        // Destroy all children, forfeit tentative objects.
        while (!obj->children.empty()) {
            auto child_it = obj->children.begin();
            
            if (object_is_tentative_(*child_it)) {
                obj->children.erase(child_it);
                continue;
            }

            DestroyObject(*child_it);
        }
        
        // TODO: (when event system) fire unload event (destructors work too though)

        allocated_objects_.erase(obj);
        tentative_objects_.erase(obj);

        alloc_.template delete_object<T>(obj);
    }

    /**
     * @brief Grants this resource manager ownership of `obj` allocated by it. Non-tentative children 
     * of `obj` are recursively treated as tentative objects unless accessed directly. 
     */
    template <ObjectType T>
    void TakeOwnership(T* obj) {
        assert(object_is_in_alloc_heap_(dynamic_cast<Object*>(obj)));

        tentative_objects_.insert(obj);
    }

    /**
     * @brief Determines whether `object` is tentative, i.e., owned directly by this
     * resource manager rather than a parent object (regardless of whether any such object exists). 
     * @return `true` if this object is tentative. `false` if it is owned by another object. 
     */
    template <ObjectType T>
    inline bool ObjectIsTentative(T* object) {
        return object_is_tentative_(dynamic_cast<Object*>(object));
    }

private:
    bool object_is_in_alloc_heap_(Object* obj);
    bool object_is_tentative_(Object* obj);
};

}

#endif 