#include <glad/gl.h>
#include <GLFW/glfw3.h> 

#include <fe/glfw_callbacks.h>
#include <fe/glinfo.h>
#include <fe/logger.h>
#include <fe/err.h>

#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

#define DEFAULT_WINDOW_LENGTH 600 
#define DEFAULT_WINDOW_HEIGHT 400 
#define DEFAULT_WINDOW_TITLE "Framework Engine"

#define CURRENT_MONITOR NULL 
#define NO_CONTEXT_SHARE NULL 

#define LOG_BAR "----------------------------------"

#ifndef FE_VERSION
#pragma GCC warning "This file is likely not being built by CMake,"\
    " or this is a bug. Expect this to break some things."
#define FE_VERSION 
#define FE_VERSION_MAJOR 0
#define FE_VERSION_MINOR 0 
#define FE_VERSION_PATCH 1
#define FE_VERSION_TIME "<error>"
#endif 

/**
 * @brief Verifies the integrity of the current working directory 
 * by scanning for necessary metadata/assets files. Basically just
 * checks if resources/ exists.
 * @return CWD_VALID on success, non-zero value on failure. Exit with this code.
 */ 
int verify_working_directory();
#define CWD_VALID 0 

// TODO: Re-research event subscriber pattern for glfw et al. event handling 
// TODO: Rewrite build script that bootstraps cmake configurations 
// TODO: Logger colors ! https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// TODO: Figure out basic module/mesh/render pipeline
// TODO: Decide on voxel structure(s)

int main() {
    char cwd[PATH_MAX];

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-result"
    getcwd(cwd, sizeof cwd);
#pragma GCC diagnostic pop

    FE_INFO("cwd: %s", cwd);

    int status = verify_working_directory();
    if (status != CWD_VALID) {
        FE_FATAL("Could not verify integrity of current working directory.");
        return status;
    }

    FE_DEBUG("folder '%s/resources' exists.", cwd);

    if (glfwInit() == GLFW_FALSE) {
        FE_FATAL("Could not initialize GLFW.");
        return FE_ERR_GLFW_INIT;
    }
    glfwSetErrorCallback(fe_base_glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  FE_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  FE_OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE,         FE_OPENGL_PROFILE);

    FE_INFO("GLFW initialized successfully.");

    // replace with program options 
    GLFWwindow* window = glfwCreateWindow(
        DEFAULT_WINDOW_LENGTH,
        DEFAULT_WINDOW_HEIGHT,
        DEFAULT_WINDOW_TITLE,
        CURRENT_MONITOR,
        NO_CONTEXT_SHARE 
    ); 

    if (!window) {
        FE_FATAL("GLFW window context failed to initialize.");
        return FE_ERR_GLFW_WINDOW_INIT;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, fe_base_glfw_key_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        FE_FATAL("GLAD failed to initialize.");
        return FE_ERR_GLAD_INIT;
    }

    FE_INFO("Engine initialized successfully.");
    FE_INFO(LOG_BAR);
    FE_INFO("Welcome to Framework Engine.");
    FE_INFO("v%d.%d.%d (%s)", FE_VERSION_MAJOR,
            FE_VERSION_MINOR,
            FE_VERSION_PATCH,
            FE_VERSION_TIME);
    FE_INFO("makichiis. All rights reserved.");
    FE_INFO(LOG_BAR);

    FE_WARNING("Finish this project by September 18th.");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3f, 0.3f, 0.35f, 1.0f);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

int verify_working_directory() {
    if (access("./resources/", F_OK) == 0) {
        return CWD_VALID;
    } else {
        return FE_ERR_INVALID_CWD;
    }
}

