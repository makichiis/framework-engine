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
    /**
     * @brief Retrieves the global runtime handler. 
     */
    static FrameworkRuntimeHandler& GetRuntimeHandler();

    ResourceManager *const GetResourceManager();
    RenderHandler *const GetRenderHandler();
    SceneManager *const GetSceneManager();

private:
    FrameworkRuntimeHandler();
public:
    FrameworkRuntimeHandler(const FrameworkRuntimeHandler&) = delete;
    void operator=(const FrameworkRuntimeHandler&) = delete;
};

}
}

#endif 