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

class ShittyMovementCamera : public fe::Camera {
public:
    using fe::Camera::Camera;

    void OnCameraUpdate() override {
        fe::Camera::OnCameraUpdate();
    }

    constexpr static float movement_mult = 15.0f;

    void OnUpdate() override {
        float velocity = movement_mult * GetFramework().delta_time;

        if (GetFramework().GetInput()->GetKeyPressed(fe::Key::S)) {
            position.z -= velocity;
        }

        if (GetFramework().GetInput()->GetKeyPressed(fe::Key::W)) {
            position.z += velocity;
        }

        if (GetFramework().GetInput()->GetKeyPressed(fe::Key::A)) {
            position.x += velocity;
        }

        if (GetFramework().GetInput()->GetKeyPressed(fe::Key::D)) {
            position.x -= velocity;
        }
    }
};

class IDKWhatToCallThisScript : public fe::Object {
public:
    using Object::Object;

    void OnUpdate() override {
        static int call_count = 0;

        int speed_mult = 1;
        call_count += speed_mult;

        auto camera = GetFramework().GetSceneManager()->GetCurrentScene()->GetPrimaryCamera();
        double radius = fabs(camera->position.z);

        for (int i = 0; i < speed_mult; ++i) { auto cube = resource_manager->CreateObject<fe::sample::RotatingCube>();
            GetFramework().GetRenderHandler()->UploadObject(cube);

            cube->GetComponent<fe::Transform>()->position = { 
                -radius + (rand() % (2 * (int)radius)), 
                -radius + (rand() % (2 * (int)radius)),
                -radius + (rand() % (2 * (int)radius)) 
            };

            auto pos = cube->GetComponent<fe::Transform>()->position;
            pos.x /= 255.0f;
            pos.y /= 255.0f;
            pos.z /= 255.0f;
            pos = glm::normalize(pos);

            fe::Color color = { pos.x, pos.y, pos.z, 1.0f };
            
            cube->GetComponent<fe::DefaultRenderer>()->material->color = color;
        }


        camera->far = 2 * radius;

        GetFramework().GetSceneManager()->GetCurrentScene()->GetPrimaryCamera()->position.z -= 2.5 * GetFramework().delta_time;

        if (call_count % 512 == 0) {
            std::cout << call_count << " total cubes added (" << GetFramework().GetTime() << "s elapsed).\n";
        }
    }
};

int main() {
    auto& framework = fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler();
    (void)framework;

    framework.SetWindow(fe::Window::CreateNewWindow({ 640, 480 }, "Window Test"));

    auto scene = framework.GetSceneManager()->CreateScene<fe::Scene>("Main Scene");
    framework.GetSceneManager()->SetCurrentScene(scene);

    scene->AddChild<IDKWhatToCallThisScript>();

    auto camera = scene->AddChild<ShittyMovementCamera>("Main Camera");
    camera->position = { 0.0f, 0.0f, -40.0f }; // set this to whatever (DO NOT MAKE A MOVEMENT SCRIPT YET)
    scene->SetPrimaryCamera(camera);

    for (size_t i = 0; i < 20; ++i) {
        auto cube = scene->AddChild<fe::sample::RotatingCube>("CUBE " + std::to_string(i));
        cube->GetComponent<fe::Transform>()->position = { -25.0f + (rand() % 50), -25.0f + (rand() % 50), -25.0f + (rand() % 50) };

        framework.GetRenderHandler()->UploadObject(cube);
    }
    
    while (!framework.GetWindow()->WindowShouldClose()) {
        framework.GetWindow()->PollEvents();

        framework.UpdateTime(glfwGetTime);

        framework.GetSceneManager()->PollCameraEvents(); 
        framework.GetResourceManager()->PollUpdateEvents(); 
        framework.GetRenderHandler()->DrawObjects(); 

        framework.GetWindow()->SwapBuffers();
    }

    glfwTerminate();

    std::cout << "Exiting...\n";
}
