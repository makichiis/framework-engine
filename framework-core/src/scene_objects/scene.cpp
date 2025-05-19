#include <fe/objects/scene_objects/scene.hpp>

fe::Camera* fe::Scene::GetPrimaryCamera() {
    return primary_camera_;
}
