#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/assets/shaders/shader.hpp>
#include <fe/runtime_handler.hpp>

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

void fe::Camera::OnCameraUpdate() {
    auto& runtime = runtime::FrameworkRuntimeHandler::GetRuntimeHandler();
    auto resource_manager = runtime.resource_manager;

    for (auto&& shader : resource_manager.GetSceneGraph().shaders) {
        assert(shader->GetShaderID() != 0);
        glUseProgram(shader->GetShaderID());

        if (shader->HasUniform("projection")) {
            std::cout << "Shader " << shader->GetShaderID() << " has projection uniform.\n";
            shader->SetMatrix4s("projection", 1, GL_FALSE, glm::value_ptr(projection));
        }

        if (shader->HasUniform("view")) {
            std::cout << "Shader " << shader->GetShaderID() << " has view uniform.\n";
            shader->SetMatrix4s("view", 1, GL_FALSE, glm::value_ptr(view));
        }

        
    }
}