#include <fe/scene_manager.hpp>

fe::SceneManager::SceneManager(ResourceManager* resource_manager) : resource_manager_{ resource_manager } {}

void fe::SceneManager::RemoveScene(Scene* scene) {
    assert(scene_is_in_scene_list_(scene));
    scenes_.erase(scene);

    if (scene == current_scene_) 
        current_scene_ = scenes_.empty() ? nullptr : *scenes_.begin();

    resource_manager_->DestroyObject(scene);
}

void fe::SceneManager::SetCurrentScene(Scene* scene) {
    assert(scene_is_in_scene_list_(scene));

    // TODO: Unloading/caching

    current_scene_ = scene;
}

fe::Scene* fe::SceneManager::GetCurrentScene() {
    return current_scene_;
}

void fe::SceneManager::PollCameraEvents() {
    // TODO: Abstract, should work with all camera subtypes.
    current_scene_->GetPrimaryCamera()->OnCameraUpdate();
}

bool fe::SceneManager::scene_is_in_scene_list_(Scene* scene) { return scenes_.find(scene) != scenes_.end(); }

