#include <iostream>

#define DEBUG

#include <fe/scene_manager.hpp>
#include <fe/resource_manager.hpp>
#include <fe/objects/components/renderer.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>

using namespace fe;
using namespace fe::sample;

int main() {
    ResourceManager resource_manager;
    SceneManager scene_manager(&resource_manager);

    auto main_scene = scene_manager.AddScene<Scene>("Main Scene");
    scene_manager.SetCurrentScene(main_scene);

    auto first_cube = main_scene->AddChild<Cube>("First Cube");
    (void)first_cube;
    first_cube->CreateComponent<Renderer>("First Cube Renderer");

    auto second_cube = main_scene->AddChild<Cube>("Second Cube");
    second_cube->CreateComponent<Renderer>("Second Cube Renderer");

    auto shared_renderer = resource_manager.CreateObject<Renderer>("Shared Renderer");
    shared_renderer->UnbindFromParent();

    Cube* cubes[10];
    for (size_t i = 0; i < (sizeof cubes / sizeof (Cube*)); ++i) {
        cubes[i] = main_scene->AddChild<Cube>("Cube (" + std::to_string(1 + i) + ")");
        cubes[i]->SetComponent<Renderer>(shared_renderer);
    }

    auto renderless_object = main_scene->AddChild<Object>("Renderless Object");
    (void)renderless_object;


    assert(!"Not fully implemented. Failing for clarity."); // not finished
}
