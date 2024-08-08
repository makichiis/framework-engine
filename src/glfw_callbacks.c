#include <fe/glfw_callbacks.h>
#include <fe/logger.h>

void fe_base_glfw_error_callback(int blame, const char *reason) {
    FE_ERROR("GLFW error (%d) occured: %s\n", blame, reason);
}

void fe_base_glfw_key_callback(GLFWwindow *window, int key, 
                               int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

