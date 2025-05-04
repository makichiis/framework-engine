#include <fe/resource_manager.hpp>
#include <fe/objects/object.hpp>

void fe::internal::SceneGraphLUT::erase(Object* obj) {
    all_objects.erase(obj);
    tentative.erase(obj);
    renderable.erase(obj);
}

void fe::internal::SceneGraphLUT::add_to_index(Object* obj) {
    erase(obj);
    all_objects.insert(obj);
}

void fe::internal::SceneGraphLUT::set_tentative(Object* obj) {
    assert(is_indexed(obj));

    tentative.insert(obj);
}

void fe::internal::SceneGraphLUT::set_renderable(Object* obj) {
    assert(is_indexed(obj));

    renderable.insert(obj);
}

bool fe::internal::SceneGraphLUT::is_indexed(Object* obj) {
    return all_objects.find(obj) != all_objects.end();
}

bool fe::internal::SceneGraphLUT::is_tentative(Object* obj) {
    return tentative.find(obj) != tentative.end();
}

bool fe::internal::SceneGraphLUT::is_renderable(Object* obj) {
    return renderable.find(obj) != renderable.end();
}

fe::ResourceManager::ResourceManager() = default;

fe::ResourceManager::ResourceManager(Allocator alloc) : alloc_{ alloc } {}

fe::ResourceManager::~ResourceManager() {
    while (!scene_graph_.all_objects.empty()) {
        auto* obj = *scene_graph_.all_objects.begin();

        DestroyObject(obj);
    }
}
