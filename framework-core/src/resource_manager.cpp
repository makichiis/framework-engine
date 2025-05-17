#include <fe/resource_manager.hpp>
#include <fe/objects/object.hpp>

void fe::internal::scene_graph_lut::erase(Object* obj) {
    all_objects.erase(obj);
    tentative.erase(obj);
    renderable.erase(obj);
}

void fe::internal::scene_graph_lut::add_to_index(Object* obj) {
    erase(obj);
    all_objects.insert(obj);
}

void fe::internal::scene_graph_lut::set_tentative(Object* obj) {
    assert(is_indexed(obj));

    tentative.insert(obj);
}

void fe::internal::scene_graph_lut::set_renderable(Object* obj) {
    assert(is_indexed(obj));

    renderable.insert(obj);
}

bool fe::internal::scene_graph_lut::is_indexed(Object* obj) const {
    return all_objects.find(obj) != all_objects.end();
}

bool fe::internal::scene_graph_lut::is_tentative(Object* obj) const {
    return tentative.find(obj) != tentative.end();
}

bool fe::internal::scene_graph_lut::is_renderable(Object* obj) const {
    return renderable.find(obj) != renderable.end();
}

fe::SceneGraphView::SceneGraphView(const internal::scene_graph_lut& scene_graph)
    : all_objects{ scene_graph.all_objects },
      tentative{ scene_graph.tentative },
      renderable{ scene_graph.renderable },
      shaders{ scene_graph.shaders },
      vertex_draw_shaders{ scene_graph.vertex_draw_shaders } {}

fe::ResourceManager::ResourceManager() = default;

fe::ResourceManager::ResourceManager(Allocator alloc) : alloc_{ alloc } {}

fe::ResourceManager::~ResourceManager() {
    while (!scene_graph_.all_objects.empty()) {
        auto* obj = *scene_graph_.all_objects.begin();

        scene_graph_.all_objects.erase(obj);
        alloc_.delete_object(obj);
    }
}

fe::SceneGraphView fe::ResourceManager::GetSceneGraph() const {
    return SceneGraphView{ scene_graph_ };
}

void fe::ResourceManager::PollUpdateEvents() {
    for (auto object : GetSceneGraph().all_objects) {
        object->OnUpdate();
    }
}
