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
#include <cassert>

int main() {
    auto& runtime = fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler();

    assert(!runtime.window_);

    auto window = fe::Window::CreateNewWindow({ 640, 480 }, "Memory Integrity");
    assert(window->window_handle_);
}
