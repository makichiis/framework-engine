#include <iostream>

#define DEBUG

#include <fe/runtime_handler.hpp>
#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>

#include <fe/objects/components/renderers/default_renderer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "[ERROR] Initialization of GLFW unsuccessful.\n";
        return 1;
    }

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

    std::cout << "GLFW and GL bindings loaded. Initializing Framework runtime...\n";

    auto& runtime_handler = fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler();

    auto main_scene = runtime_handler.scene_manager.CreateScene<fe::Scene>("Main Scene");
    runtime_handler.scene_manager.SetCurrentScene(main_scene);

    auto camera = main_scene->AddChild<fe::Camera>("Main Camera");
    

    auto cube = main_scene->AddChild<fe::sample::Cube>("Funny Cube");

    main_scene->SetPrimaryCamera(camera);

    std::cout << "Scene loaded!\n"; 

    // (temp) manual scene camera update 
    main_scene->GetPrimaryCamera<fe::Camera>();

    runtime_handler.render_handler.UploadObject(cube);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto object : runtime_handler.resource_manager.GetSceneGraph().all_objects) {
            object->OnUpdate();
        }

        runtime_handler.render_handler.DrawObjects();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    
    
    (void)camera;
    (void)cube;

    
}
