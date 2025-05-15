#ifndef FE_CAMERA_HPP
#define FE_CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "scene_object.hpp"

namespace fe {

class Camera : public SceneObject {
public:
    using SceneObject::SceneObject;

    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 position; // TODO: replace with transform component

    /**
     * @brief Called by the Scene Manager when 
     */
    virtual void OnCameraStateChange();
};

}

#endif 
