#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/assets/shaders/shader.hpp>
#include <fe/runtime_handler.hpp>

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

void fe::Camera::OnCameraStateChange() {
    auto resource_manager = GetFramework().GetResourceManager();

    for (auto&& shader : resource_manager->GetSceneGraph().shaders) {
        assert(shader->GetShaderID() != 0); // TODO: Refactgor this when empty shaders are valid.
        glUseProgram(shader->GetShaderID());

        if (shader->HasUniform("projection")) {
            shader->SetMatrix4s("projection", 1, GL_FALSE, glm::value_ptr(projection));
        }

        if (shader->HasUniform("view")) {
            shader->SetMatrix4s("view", 1, GL_FALSE, glm::value_ptr(view));
        }
    }
}
