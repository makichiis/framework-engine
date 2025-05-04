#include <iostream>

// #define DEBUG

#include <fe/scene_manager.hpp>
#include <fe/resource_manager.hpp>
#include <fe/objects/components/renderer.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>

#include <typeinfo>

using namespace fe;
using namespace fe::sample;

int main() {
    ResourceManager resource_manager;
    SceneManager scene_manager(&resource_manager);

    auto main_scene = scene_manager.CreateScene<Scene>("Main Scene");
    scene_manager.SetCurrentScene(main_scene);

    auto first_cube = main_scene->AddChild<Cube>("First Cube");
    first_cube->CreateComponent<Renderer>("First Cube Renderer");

    auto second_cube = main_scene->AddChild<Cube>("Second Cube");
    second_cube->CreateComponent<Renderer>("Second Cube Renderer");

    auto renderless_object = main_scene->AddChild<Object>("Renderless Object");
    auto doomed_renderer = renderless_object->CreateComponent<Renderer>();
    renderless_object->RemoveComponentById(typeid(*doomed_renderer));

    assert(resource_manager.GetSceneGraph().renderable.size() == 2);
}
