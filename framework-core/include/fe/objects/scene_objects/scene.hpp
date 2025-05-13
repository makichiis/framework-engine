#ifndef FE_SCENE_HPP
#define FE_SCENE_HPP

#include "scene_object.hpp"
#include "camera.hpp"

namespace fe {

class Scene : public SceneObject {
    Camera* primary_camera;
public:
    using SceneObject::SceneObject;

    /**
     * @brief Specify from which camera renders this scene. 
     */
    template <class T>
    void SetPrimaryCamera(T* camera) requires std::is_base_of_v<Camera, T> {
        primary_camera = camera;
    }

    template <class T>
    T* GetPrimaryCamera() requires std::is_base_of_v<Camera, T> {
        return dynamic_cast<T*>(primary_camera);
    }
};

}

#endif 