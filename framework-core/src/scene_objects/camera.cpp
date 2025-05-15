#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/assets/shaders/shader.hpp>
#include <fe/runtime_handler.hpp>

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void fe::Camera::OnCameraUpdate() {
    auto resource_manager = GetFramework().GetResourceManager();

    projection = glm::perspective(glm::radians(60.0f), (float)GetFramework().GetWindow()->GetState().size.aspect(), 0.1f, 100.0f);
    view = glm::translate(glm::identity<glm::mat4>(), position);

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
