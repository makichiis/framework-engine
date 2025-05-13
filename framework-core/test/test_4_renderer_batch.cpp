#include <iostream>
#include <cassert>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// #define DEBUG

#include <fe/scene_manager.hpp>
#include <fe/resource_manager.hpp>

#include <fe/runtime_handler.hpp>
#include <fe/objects/components/renderer.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>

#include <typeinfo>

using namespace fe;
using namespace fe::sample;

int main() {
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "[ERROR] Initialization of GLFW window unsuccessful.\n";
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "[ERROR]: Could not load GLAD.\n";
        return 1;
    }

    runtime::FrameworkRuntimeHandler& runtime_handler = runtime::FrameworkRuntimeHandler::GetRuntimeHandler();
    auto scene_manager = runtime_handler.GetSceneManager();
    auto resource_manager = runtime_handler.GetResourceManager();

    std::cout << "test\n";

    auto main_scene = scene_manager->CreateScene<Scene>("Main Scene");
    scene_manager->SetCurrentScene(main_scene);

    auto first_cube = main_scene->AddChild<Cube>("First Cube");
    (void)first_cube;

    auto second_cube = main_scene->AddChild<Cube>("Second Cube");
    (void)second_cube;

    auto renderless_object = main_scene->AddChild<Object>("Renderless Object");
    auto doomed_renderer = renderless_object->CreateComponent<Renderer>();
    renderless_object->RemoveComponentById(typeid(*doomed_renderer));

    assert(resource_manager->GetSceneGraph().renderable.size() == 2);

    glfwTerminate();
}
