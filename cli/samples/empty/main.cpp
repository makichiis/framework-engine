#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <fe/runtime_handler.hpp>
#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>
#include <fe/objects/assets/materials/default_material.hpp>
#include <fe/objects/components/transform.hpp>

#include <fe/objects/components/renderers/default_renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdlib>

int main() {
    auto& framework = fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler();
    (void)framework;

    framework.SetWindow(fe::Window::CreateNewWindow({ 640, 480 }, "Window Test"));

    auto scene = framework.GetSceneManager()->CreateScene<fe::Scene>("Main Scene");
    framework.GetSceneManager()->SetCurrentScene(scene);

    auto camera = scene->AddChild<fe::Camera>("Main Camera");
    camera->position = { 0.0f, 0.0f, -5.0f };
    scene->SetPrimaryCamera(camera);

    // User init code here

    while (!framework.GetWindow()->WindowShouldClose()) {
        framework.GetWindow()->PollEvents();

        framework.UpdateTime(glfwGetTime);

        framework.GetSceneManager()->PollCameraEvents();
        framework.GetResourceManager()->PollUpdateEvents();
        framework.GetRenderHandler()->DrawObjects();

        framework.GetWindow()->SwapBuffers();
    }
}
