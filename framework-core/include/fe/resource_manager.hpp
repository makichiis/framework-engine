#ifndef FE_RESOURCE_MANAGER_HPP
#define FE_RESOURCE_MANAGER_HPP

#include <memory_resource>
#include <unordered_set>
#include <type_traits>
#include <cassert>

#include <iostream>

namespace fe {

class Object;
class Shader;

template <class T>
concept ObjectType = std::is_base_of_v<Object, T>;

namespace internal {

/**
 * @brief Lookup table list for allocated polymorphic objects. 
 */
struct scene_graph_lut {
    /**
     * @brief All objects referenced by this LUT. Any objects referenced in
     * `tenative` and `renderable` must also be in `all_objects`. 
     */
    std::unordered_set<Object*> all_objects; 
    /**
     * @brief Objects marked as `tentative`, i.e., they are owned by their
     * allocator, rather than their immediate parent in the scene graph. 
     */
    std::unordered_set<Object*> tentative;
    /**
     * @brief Objects which contain components derived from `fe::Renderer`. 
     */
    std::unordered_set<Object*> renderable;

    std::unordered_set<Shader*> shaders;

    std::unordered_set<Shader*> vertex_draw_shaders;

    /**
     * @brief Erases `obj` -- if found -- from all tables. 
     */
    void erase(Object* obj);

    /**
     * @brief Adds `obj` to the global scene graph index. 
     */
    void add_to_index(Object* obj);

    /**
     * @brief Adds `obj` to the tentative index. 
     */
    void set_tentative(Object* obj);

    /**
     * @brief Adds `obj` to the renderable index.
     */
    void set_renderable(Object* obj);

    /**
     * @brief Returns `true` if `obj` is indexed by this LUT. 
     */
    bool is_indexed(Object* obj) const;

    /**
     * @brief Returns `true` if `obj` is tentative. 
     */
    bool is_tentative(Object* obj) const;

    /**
     * @brief Returns `true` if `obj` contains a component derived from `fe::Renderer`. 
     */
    bool is_renderable(Object* obj) const;
};

}

class SceneGraphView {
public:
    /**
     * @brief All objects referenced by this LUT. Any objects referenced in
     * `tenative` and `renderable` must also be in `all_objects`. 
     */
    const std::unordered_set<Object*>& all_objects; 
    /**
     * @brief Objects marked as `tentative`, i.e., they are owned by their
     * allocator, rather than their immediate parent in the scene graph. 
     */
    const std::unordered_set<Object*>& tentative;
    /**
     * @brief Objects which contain components derived from `fe::Renderer`. 
     */
    const std::unordered_set<Object*>& renderable;

    const std::unordered_set<Shader*>& shaders;
    
    const std::unordered_set<Shader*>& vertex_draw_shaders;

    SceneGraphView(const internal::scene_graph_lut& scene_graph);
};

class ResourceManager {
public:
    using Allocator = std::pmr::polymorphic_allocator<Object>;
#ifndef DEBUG
private:
#endif 
    // TODO: Make template. Refactored as non-template in order to
    // temporarily resolve circular dependency issues.
    Allocator alloc_;

    // Unordered sets are used to index object attributes for fast lookup
    internal::scene_graph_lut scene_graph_;

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
        // std::cout << "Building new " << typeid(T).name() << '\n';
        // std::flush(std::cout);

        T* obj = alloc_.template new_object<T>(std::forward<Args>(ctor_args)...);
        
        // std::cout << typeid(T).name() << " built at " << obj << ". Configuring...\n";
        // std::flush(std::cout);

        obj->resource_manager = this;

        // std::cout << "Adding " << typeid(T).name() << " to scene graph.\n";
        // std::flush(std::cout);
        
        scene_graph_.add_to_index(dynamic_cast<Object*>(obj));

        if constexpr (std::is_base_of_v<Shader, T>) {
            scene_graph_.shaders.insert(obj);
        }

        obj->OnInit();

        return obj;
    }

    /**
     * @brief Destroy `obj` allocated by this resource manager. Destroys all owned children. 
     */
    template <ObjectType T>
    void DestroyObject(T* obj) {
        assert(scene_graph_.is_indexed(dynamic_cast<Object*>(obj)));

        if (obj->parent) {
            obj->parent->children.erase(obj); // Prevent hanging child reference (issue #1)
            obj->parent = nullptr;
        }

        // Destroy all children, forfeit tentative objects.
        while (!obj->children.empty()) {
            auto child_it = obj->children.begin();
            
            if (scene_graph_.is_tentative(*child_it)) {
                obj->children.erase(child_it);
                continue;
            }

            DestroyObject(*child_it);
        }
        
        // TODO: (when event system) fire unload event (destructors work too though)

        scene_graph_.erase(obj);
        alloc_.template delete_object<T>(obj);
    }

    /**
     * @brief Grants this resource manager ownership of `obj` allocated by it. Non-tentative children 
     * of `obj` are recursively treated as tentative objects unless accessed directly. 
     */
    template <ObjectType T>
    void MarkObjectTentative(T* obj, bool tentative=true) {
        if (!tentative && scene_graph_.is_tentative(obj)) {
            scene_graph_.tentative.erase(obj);
            if (obj->parent == nullptr) DestroyObject(obj);
        } else if (tentative) {
            scene_graph_.set_tentative(obj);
        }
    }

    template <ObjectType T>
    void MarkObjectRenderable(T* obj, bool renderable=true) {
        if (renderable) scene_graph_.set_renderable(obj);
        else scene_graph_.renderable.erase(obj);
    }

    /**
     * @brief Determines whether `object` is tentative, i.e., owned directly by this
     * resource manager rather than a parent object (regardless of whether any such object exists). 
     * @return `true` if this object is tentative. `false` if it is owned by another object. 
     */
    template <ObjectType T>
    inline bool ObjectIsTentative(T* obj) const {
        return scene_graph_.is_tentative(dynamic_cast<Object*>(obj));
    }

    template <ObjectType T>
    inline bool ObjectIsRenderable(T* obj) const {
        return scene_graph_.is_renderable(dynamic_cast<Object*>(obj));
    }

    SceneGraphView GetSceneGraph() const;

private:
};

}

#endif 