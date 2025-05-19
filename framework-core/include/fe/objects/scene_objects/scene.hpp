#ifndef FE_SCENE_HPP
#define FE_SCENE_HPP

#include "../object.hpp"
#include "camera.hpp"

namespace fe {

class Scene : public Object {
    Camera* primary_camera_;
public:
    using Object::Object;

    /**
     * @brief Specify from which camera renders this scene. 
     */
    template <class T>
    void SetPrimaryCamera(T* camera) requires std::is_base_of_v<Camera, T> {
        primary_camera_ = camera;
    }

    /**
     * @brief Retrieve the camera currently rendering this scene. 
     */
    fe::Camera* GetPrimaryCamera();
};

}

#endif 