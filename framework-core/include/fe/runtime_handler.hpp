#ifndef FE_RUNTIME_HANDLER_HPP
#define FE_RUNTIME_HANDLER_HPP

#include <fe/resource_manager.hpp>
#include <fe/render_handler.hpp>
#include <fe/scene_manager.hpp>
#include <fe/window.hpp>

namespace fe {
/**
 * @brief The scope of all Framework Engine components which drive the program, and
 * should not be accessed or interfaced unless implementing the driver (e.g., game runtime base,
 * level editor). 
 */
namespace runtime {

namespace internal {

}

/**
 * @brief Singleton runtime handler. 
 */
class FrameworkRuntimeHandler {
private:
#ifdef DEBUG
public:
#endif 
    ResourceManager* resource_manager_;
    RenderHandler* render_handler_;
    SceneManager* scene_manager_;
    Window* window_;

    double time_since_start_ = 0.0;
public:
    double delta_time = 0.0;

    ~FrameworkRuntimeHandler();

    /**
     * @brief Retrieves the global runtime handler. 
     */
    static FrameworkRuntimeHandler& GetRuntimeHandler();

    ResourceManager *const GetResourceManager();
    RenderHandler *const GetRenderHandler();
    SceneManager *const GetSceneManager();

    /**
     * @brief Retrieve the current window.
     */
    Window *const GetWindow();
    
    void SetWindow(Window* window);

    /**
     * @brief Retrieve the input handler for reading key and mouse input.
     * @returns The input handler. 
     * @note Auxiliary access function for `GetWindow()->GetInput()`
     */
    InputHandler *const GetInput();

    /**
     * @brief Updates this runtime handler's delta time and other possibly time-related calculations. Called by driver.
     */
    void UpdateTime(double (*time_fn)());

    /**
     * @brief Retrieve the time (in seconds) since the start of this simulation.s
     */
    double GetTime();

private:
    FrameworkRuntimeHandler();
public:
    FrameworkRuntimeHandler(const FrameworkRuntimeHandler&) = delete;
    void operator=(const FrameworkRuntimeHandler&) = delete;
};

}
}

#endif 