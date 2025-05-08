#include <iostream>

#include <fe/runtime_handler.hpp>
#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>

int main() {
    auto& runtime_handler = fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler();

    auto main_scene = runtime_handler.scene_manager.CreateScene<fe::Scene>("Main Scene");
    runtime_handler.scene_manager.SetCurrentScene(main_scene);

    auto camera = main_scene->AddChild<fe::Camera>("Main Camera");
    auto cube = main_scene->AddChild<fe::sample::Cube>("Funny Cube");
    
    (void)camera;
    (void)cube;


}
