#include <iostream>

#define DEBUG

#include <fe/runtime_handler.hpp>
#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>
#include <fe/objects/assets/materials/default_material.hpp>

#include <fe/objects/components/renderers/default_renderer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    auto main_scene = runtime_handler.GetSceneManager()->CreateScene<fe::Scene>("Main Scene");
    runtime_handler.GetSceneManager()->SetCurrentScene(main_scene);

    auto camera = main_scene->AddChild<fe::Camera>("Main Camera");
    
    camera->position = { 0.0f, 0.0f, -1.0f };
    camera->projection = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);
    camera->view = glm::translate(glm::identity<glm::mat4>(), camera->position);

    auto cube = main_scene->AddChild<fe::sample::Cube>("Funny Cube");
    std::cout << cube->name << " has " << cube->components_by_type.size() << " components.\n";

    // (temp) manual scene camera update 
    main_scene->SetPrimaryCamera(camera);
    main_scene->GetPrimaryCamera<fe::Camera>()->OnCameraUpdate();

    std::cout << "Scene loaded!\n"; 

    // (temp) manual object upload 
    std::cout << "Uploading GL buffers for " << cube->name << " at " << cube << '\n';
    runtime_handler.GetRenderHandler()->UploadObject(cube);

    glm::mat4 model = glm::identity<glm::mat4>();
    cube->GetComponent<fe::DefaultRenderer>()->material->shader->SetMatrix4s("model", 1, GL_FALSE, glm::value_ptr(model));

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto object : runtime_handler.GetResourceManager()->GetSceneGraph().all_objects) {
            object->OnUpdate();
        }

        runtime_handler.GetRenderHandler()->DrawObjects();

        if (glfwGetTime() > 5.0) glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    
    
    (void)camera;
    (void)cube;

    
}
