#ifndef FE_SCENE_MANAGER_HPP
#define FE_SCENE_MANAGER_HPP

#include <unordered_set>
#include <cassert>

#include "objects/scene_objects/scene.hpp"
#include "resource_manager.hpp"

namespace fe {

template <class T>
concept SceneType = std::is_base_of_v<Scene, T>;

class SceneManager {
private:
    ResourceManager* resource_manager_;
    Scene* current_scene_;
    std::unordered_set<Scene*> scenes_;

public:
    SceneManager(ResourceManager* resource_manager);

    /**
     * @brief Adds an existing scene to this scene manager. 
     * @note When a scene is made the current scene, it is granted provisional ownership over tentative
     * objects managed by the internal resource manager. 
     */
    template <SceneType T>
    void AddScene(T* scene) {
        scenes_.insert(scene);
    }

    /**
     * @brief Create an empty scene.
     * @note When a scene is made the current scene, it is granted provisional ownership over tentative
     * objects managed by the internal resource manager. 
     */ 
    template <SceneType T, class... Args>
    T* CreateScene(Args&&... scene_ctor_args) {
        T* scene = resource_manager_->CreateObject<T>(std::forward<Args>(scene_ctor_args)...);
        scenes_.insert(scene);

        return scene;
    }

    /**
     * @brief Removes the `scene` managed by this scene manager and destroys the scene object. 
     * @note Tentative objects -- that is, object which are owned by the resource manager -- will
     * not be destroyed when this scene is destroyed.
     */
    void RemoveScene(Scene* scene);

    /**
     * @brief Retrieve a reference to the currently loaded scene.
     */
    Scene* GetCurrentScene();

    /**
     * @brief Unloads the previous focused scene (if any is set) and loads this `scene` 
     * owned by this scene manager. 
     * @note When a scene is made the focused scene, it is granted provisional ownership over tentative
     * objects managed by the internal resource manager. 
     */
    void SetCurrentScene(Scene* scene);

    void PollCameraEvents();
private:
    bool scene_is_in_scene_list_(Scene* scene);
};

}

#endif 