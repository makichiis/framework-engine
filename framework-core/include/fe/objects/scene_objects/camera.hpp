#ifndef FE_CAMERA_HPP
#define FE_CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "scene_object.hpp"

namespace fe {

/**
 * @brief Base Camera type. Responsible for the rendering of objects in a scene. 
 */
class Camera : public SceneObject {
public:
    using SceneObject::SceneObject;

    // TODO: Replace with transform 
    glm::mat4 projection;
    glm::mat4 view; 
    glm::vec3 position; // TODO: replace with transform component

    float near = 0.1f;
    float far = 1000.0f;

    /**
     * @brief Called by the driver before `OnUpdate()` is called on any object. 
     * May safely be called directly to bolster pre-processing events like 
     * custom frustum culling. 
     */
    virtual void OnCameraUpdate();
};

}

#endif 
