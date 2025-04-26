#include <rootdef.hpp>

#include <iostream>
#include <cassert>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
    assert(foo() == FE_FOO_SUCCESS);
    std::cout << "Library integrity confirmed!\n";

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

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetTime() >= 1.0)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
