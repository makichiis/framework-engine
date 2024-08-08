#ifndef FE_GLFW_CALLBACKS_H
#define FE_GLFW_CALLBACKS_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void fe_base_glfw_error_callback(int blame, const char* reason);

void fe_base_glfw_key_callback(GLFWwindow* window, int key, int scancode,
                               int action, int mods);

#endif 

