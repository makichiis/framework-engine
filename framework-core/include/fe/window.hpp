#ifndef FE_WINDOW_HPP
#define FE_WINDOW_HPP

#include "input_handler.hpp"

namespace fe {

namespace runtime { class FrameworkRuntimeHandler; }

struct Size2D {
    int x;
    int y;

    /**
     * @brief Compute `x:y` ratio of this size object.
     */
    double aspect() const;
};

/**
 * @brief Configurations and state information about this window.
 */
struct WindowState {
    Size2D size;
};

class Window {
    WindowState state_;

    void* window_handle_ = nullptr;
    void (*window_bind_fn_)(void* abstract_window_object_) = nullptr; // Function wrapper for window binding.

    InputHandler input_handler;

    friend runtime::FrameworkRuntimeHandler;
public:

    /**
     * @brief Retrieve window state. 
     */
    const WindowState& GetState() const;

    InputHandler *const GetInput();

    void InitializeWindowBindings(void (*window_bind_fn)(void* window_object_param), void* window_handle);

    void OnKeyInput(int key, int scancode, int action, int mods); // TODO: Standardize this call
};

}

#endif 