#ifndef FE_RUNTIME_HANDLER_HPP
#define FE_RUNTIME_HANDLER_HPP

#include <fe/resource_manager.hpp>
#include <fe/scene_manager.hpp>

namespace fe {
/**
 * @brief The scope of all Framework Engine components which drive the program, and
 * should not be accessed or interfaced unless implementing the driver (e.g., game runtime base,
 * level editor). 
 */
namespace runtime {

/**
 * @brief Singleton runtime handler. 
 */
class FrameworkRuntimeHandler {
public:
    ResourceManager resource_manager;
    SceneManager scene_manager;

    /**
     * @brief Retrieves the global runtime handler. 
     */
    static FrameworkRuntimeHandler& GetRuntimeHandler();

private:
    FrameworkRuntimeHandler();
public:
    FrameworkRuntimeHandler(const FrameworkRuntimeHandler&) = delete;
    void operator=(const FrameworkRuntimeHandler&) = delete;
};

}
}

#endif 