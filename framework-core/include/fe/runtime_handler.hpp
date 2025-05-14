#ifndef FE_RUNTIME_HANDLER_HPP
#define FE_RUNTIME_HANDLER_HPP

#include <fe/resource_manager.hpp>
#include <fe/render_handler.hpp>
#include <fe/scene_manager.hpp>

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
    ResourceManager resource_manager;
    RenderHandler render_handler;
    SceneManager scene_manager;

public:
    double delta_time = 0.0;

    /**
     * @brief Retrieves the global runtime handler. 
     */
    static FrameworkRuntimeHandler& GetRuntimeHandler();

    ResourceManager *const GetResourceManager();
    RenderHandler *const GetRenderHandler();
    SceneManager *const GetSceneManager();

    /**
     * @brief Updates this runtime handler's delta time and other possibly time-related calculations. Called by driver.
     */
    void UpdateTime(double (*time_fn)());

private:
    FrameworkRuntimeHandler();
public:
    FrameworkRuntimeHandler(const FrameworkRuntimeHandler&) = delete;
    void operator=(const FrameworkRuntimeHandler&) = delete;
};

}
}

#endif 